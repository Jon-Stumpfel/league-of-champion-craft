#include "StdAfx.h"
#include "ScriptManager.h"
#include "GameManager.h"
#include "Ability.h"
#include "Tile.h"
#include "Unit.h"
#include "TileManager.h"
#include "SGD Wrappers\tinyxml.h"
#include "AbilityManager.h"
#include "ParticleManager.h"

CScriptManager* CScriptManager::s_Instance = nullptr;


Vec2Df TranslateToPixelF(Vec2D gamePosition)
{
	int x = (nFakeTileWidth / 2 * gamePosition.nPosX) - (nFakeTileHeight / 2 * gamePosition.nPosY) + nFakeTileWidth / 2;
	int y = (nFakeTileWidth / 2 * gamePosition.nPosX) + (nFakeTileHeight  / 2 * gamePosition.nPosY) + nFakeTileHeight / 2;

	return Vec2Df((float)x, (float)y);
}


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

		std::vector< Vec2D > TilePos = CAbilityManager::GetInstance()->GetProperFacing(pCaster->GetFacing(), pAbility, pTile);
		for( unsigned int i = 0; i < TilePos.size(); i++ )
		{
			Vec2Df tmp = TranslateToPixelF(TilePos[i]);
			CParticleManager::GetInstance()->LoadParticles(TEST, tmp);
		}

		lua_getglobal(L, "OnUse");

		lua_newtable(L);
		CGameManager* pGM = CGameManager::GetInstance();
		vector< CUnit* > affected;
		int nCount = 0;
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
			lua_settable(L, -3);
			lua_pushstring(L, "shielded");
			lua_pushnumber(L, tmp->GetShielded());
			lua_settable(L, -3);

			lua_pushnumber(L, nCount+1);
			nCount++;
			lua_insert(L, -2);
			lua_settable(L, -3);
		}

		lua_setglobal(L, "tUnitData");

		luaL_dofile(L, pAbility->GetLua().c_str());
		lua_getglobal(L, "OnUse");
		
		lua_call(L, 0, 0);

		lua_getglobal(L, "tUnitData");
		lua_pushnil(L);
	
		vector<std::pair<std::string, int>> tData;
	//	std::pair<std::string, int> tmp;

		tData.clear();

		while(lua_next(L, -2) != 0) 
		{
			if( lua_istable(L, -1) )
			{
				lua_pushnil(L);
				while( lua_next(L, -2) )
				{
					if(lua_isnumber(L, -1))
					{
						std::pair<std::string, int> tmp;
						tmp.first = lua_tostring(L, -2);
						tmp.second = (int)lua_tonumber(L, -1);
						tData.push_back(tmp);
					}
					lua_pop(L, 1);
				}
			}
			else
			{
				if(lua_isnumber(L, -1))
				{
					std::pair<std::string, int> tmp;
					tmp.first = lua_tostring(L, -2);
					tmp.second = (int)lua_tonumber(L, -1);
					tData.push_back(tmp);
				}	
			}
			lua_pop(L, 1);
		}

		/*try
		{
			lua_close(L);
		}
		catch (int e)
		{
			int x = 9;
		}*/

		//lua_close(L);

		int x = 0;
		int y = 0;

		for( unsigned int i = 0; i < affected.size(); i++ )
		{
			x = 0;
			y = 0;
			for( unsigned int l = 0 + i*5; l < 5 + 5*i; l++ )
			{
				if( tData[l].first == "health" )
					affected[i]->SetHP(tData[l].second);

				if( tData[l].first == "posX" )
					x = tData[l].second;

				if( tData[l].first == "posY" )
					y = tData[l].second;

				if( tData[l].first == "speed" )
					affected[i]->SetSpeed(tData[l].second);

				if( tData[l].first == "shielded" )
					affected[i]->SetShielded(tData[l].second);
			}
			affected[i]->SetPos(x,y);
		}
}

void CScriptManager::Initialize( void )
{
		L = lua_open();
		luaL_openlibs(L);
}

void CScriptManager::Shutdown( void )
{
	lua_close(L);
}
