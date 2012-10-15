#include "StdAfx.h"
#include "ScriptManager.h"
#include "GameManager.h"
#include "Ability.h"
#include "Tile.h"
#include "Unit.h"
#include "TileManager.h"
#include "SGD Wrappers\tinyxml.h"

CScriptManager* CScriptManager::s_Instance = nullptr;

CScriptManager::CScriptManager(void)
{
}

CScriptManager::~CScriptManager(void)
{
}

CScriptManager* CScriptManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CScriptManager;

	return s_Instance;
}

void CScriptManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CScriptManager::LoadScript( std::string szFilename, SCRIPT_TYPE eScript )
{
	if (eScript == ST_LEVEL)
	{
		// Load!
		TiXmlDocument doc;
		if (doc.LoadFile(szFilename.c_str()) == true)
		{
			TiXmlElement* pRoot = doc.RootElement();

			if (pRoot == nullptr)
				return;

			TiXmlElement* pSpawns = pRoot->FirstChildElement("UnitSpawns");
			int nNumSpawns;
			pSpawns->QueryIntAttribute("numSpawns", &nNumSpawns);
			TiXmlElement* pSpawn = pSpawns->FirstChildElement("UnitSpawn");

			for (int i = 0; i < nNumSpawns; ++i)
			{
				ScriptedSpawn s;
				ScriptSpawnData scriptData;

				int nType;
				pSpawn->QueryIntAttribute("unitType", &nType);
				scriptData.eType = (UNIT_TYPE)nType;
				int nFacing;
				pSpawn->QueryIntAttribute("facing", &nFacing);
				scriptData.nFacing = nFacing;
				int posX;
				int posY;
				pSpawn->QueryIntAttribute("posX", &posX);
				pSpawn->QueryIntAttribute("posY", &posY);
				scriptData.sPos.nPosX = posX;
				scriptData.sPos.nPosY = posY;
				int nPlayerID;
				pSpawn->QueryIntAttribute("playerID", &nPlayerID);
				scriptData.nPlayerID = nPlayerID;
				pSpawn->QueryIntAttribute("TurnToSpawn", &s.first);
				s.second = scriptData;
				CGameManager::GetInstance()->AddScriptSpawn(s);

				pSpawn = pSpawn->NextSiblingElement();
			}
		}
	}
}

void CScriptManager::Execute( CAbility* pAbility, CTile* pTile, CUnit* pCaster )
{
	// Finds the facing for the specified unit
	int face = pCaster->GetFacing();
	std::vector< Vec2D > pattern = pAbility->GetPattern();
	std::vector< Vec2D > TilePos;

	if( face == 0 ) // S
	{
		for( unsigned int i = 0; i < pattern.size(); i++ )
		{
			pattern[i].nPosY = -pattern[i].nPosY;
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX + pTile->GetPosition().nPosX;
			tmp.nPosY = pattern[i].nPosY + pTile->GetPosition().nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 1 ) // N
	{
		for( unsigned int i = 0; i < pattern.size(); i++ )
		{
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX + pTile->GetPosition().nPosX;
			tmp.nPosY = pattern[i].nPosY + pTile->GetPosition().nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 2 ) // E
	{
		for( unsigned int i = 0; i < pattern.size(); i++ )
		{
			int x = pattern[i].nPosX;
			pattern[i].nPosX = -pattern[i].nPosY;
			pattern[i].nPosY = x;
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX + pTile->GetPosition().nPosX;
			tmp.nPosY = pattern[i].nPosY + pTile->GetPosition().nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 3 ) // W
	{
		for( unsigned int i = 0; i < pattern.size(); i++ )
		{
			int x = pattern[i].nPosX;
			pattern[i].nPosX = pattern[i].nPosY;
			pattern[i].nPosY = -x;
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX + pTile->GetPosition().nPosX;
			tmp.nPosY = pattern[i].nPosY + pTile->GetPosition().nPosY;
			TilePos.push_back(tmp);
		}
	}

	lua_State* L;
	L = lua_open();
	luaL_openlibs(L);

	lua_getglobal(L, "OnUse");

	lua_newtable(L);
	CGameManager* pGM = CGameManager::GetInstance();
	vector< CUnit* > affected;
	for( unsigned int i = 0; i < TilePos.size(); i++ )
	{
		CUnit* tmp = pGM->FindUnit(TilePos[i].nPosX, TilePos[i].nPosY);
		
		if( tmp == nullptr )
			continue;
		affected.push_back( tmp );

		lua_newtable(L);
		lua_pushstring(L, "posX");
		lua_pushnumber(L, tmp->GetPos().nPosX);
		lua_settable(L, -3);
		lua_pushstring(L, "posY");
		lua_pushnumber(L, tmp->GetPos().nPosY);
		lua_settable(L, -3);
		lua_pushstring(L, "health");
		lua_pushnumber(L, tmp->GetHP());
		lua_settable(L, -3);
		lua_pushstring(L, "speed");
		lua_pushnumber(L, tmp->GetSpeed());

		lua_pushnumber(L, i+1);
		lua_insert(L, -2);
		lua_settable(L, -4);
	}

	lua_setglobal(L, "tUnitData");

	luaL_dofile(L, pAbility->GetLua().c_str());
	lua_getglobal(L, "OnUse");

	lua_call(L, 0, 1);

	lua_getglobal(L, "tUnitData");
	lua_pushnil(L);
	
	std::vector< std::pair<std::string, int> > tData;

	while(lua_next(L, -2)) 
	{
		std::pair<std::string, int> tmp;
		if( lua_isstring(L, -1) )
		{
			tmp.first = (string)lua_tostring(L, -1);
		}
		if(lua_isnumber(L, -1))
		{
			tmp.second = (int)lua_tonumber(L, -1);
		}
		tData.push_back(tmp);
		lua_pop(L, 1);
	}

	int count = 0;
	for( unsigned int i = 0; i < tData.size(); i++ )
	{
		if( tData[i].first == "health" )
		{
			affected[count]->SetHP(tData[i].second);
			count++;
		}
	}

	lua_close(L);
}

void CScriptManager::Initialize( void )
{

}

void CScriptManager::Shutdown( void )
{

}
