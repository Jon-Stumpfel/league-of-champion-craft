#include "StdAfx.h"
#include "ScriptManager.h"
#include "GameManager.h"
#include "Ability.h"
#include "Tile.h"
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
			int x = 0;
		}
	}
}

void CScriptManager::ExecuteTile( CAbility* pAbility, CTile* pTile )
{

}

void CScriptManager::ExecuteUnit( CAbility* pAbility, CUnit* pUnit )
{

}

void CScriptManager::Initialize( void )
{

}

void CScriptManager::Shutdown( void )
{

}
