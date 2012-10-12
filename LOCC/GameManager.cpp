#include "StdAfx.h"
#include "GameManager.h"
#include "GameplayState.h"
#include "ObjectManager.h"
#include "SpawnUnitMessage.h"
#include "TileManager.h"
#include "ScriptManager.h"
#include "MessageSystem.h"
#include "DeSpawnUnitMessage.h"
#include "AddResourceMessage.h"
#include "Tile.h"
#include "Unit.h"
#include "Hero.h"
#include "Player.h"

CGameManager* CGameManager::s_Instance = nullptr;

CGameManager::CGameManager(void)
{
	m_nNewPlayerID = 0;
	m_nPhaseCount = 0;
	m_pCurrentPlayer = nullptr;
	m_pNextPlayer = nullptr;
}


CGameManager::~CGameManager(void)
{
}

void CGameManager::NextPhase(void)
{
	m_nPhaseCount++;
	if (m_nCurrentPhase == GP_MOVE)
	{
		m_nCurrentPhase = GP_ATTACK;
	}
	else if (m_nCurrentPhase == GP_ATTACK)
	{
		CPlayer* pTemp = m_pCurrentPlayer;
		m_nCurrentPhase = GP_MOVE;
		m_pCurrentPlayer = m_pNextPlayer;
		m_pNextPlayer = pTemp;


		CGameplayState::GetInstance()->ClearSelections();
		if (GetChampion(m_pCurrentPlayer->GetPlayerID()) != nullptr)
		{
			CGameplayState::GetInstance()->SnapToPosition(GetChampion(m_pCurrentPlayer->GetPlayerID())->GetPos());
		}
		m_pCurrentPlayer->SetAP(nStartingAP);

		for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
		{
			if (m_vUnits[i]->GetPlayerID() == m_pCurrentPlayer->GetPlayerID())
			{
				m_vUnits[i]->SetTilesMoved(0);
				m_vUnits[i]->SetHasAttacked(false);
			}
		}
	}
}

// Get the player's champion unit. Searches through the unit list to find a unit that matches
// the criteria: Owned by nPlayerID and is a UT_HERO. We can assume there will only ever be 1 hero.
CUnit* CGameManager::GetChampion(int nPlayerID)
{
	for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
	{
		if (m_vUnits[i]->GetPlayerID() != nPlayerID)
			continue;
		if (m_vUnits[i]->GetType() == UT_HERO)
			return m_vUnits[i];
	}
	return nullptr;
}
CGameManager* CGameManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CGameManager();
	return s_Instance;

}


CPlayer* CGameManager::GetCurrentPlayer(void)
{
	return m_pCurrentPlayer;
}
void CGameManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->ShutDown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CGameManager::ShutDown(void)
{
	while (m_vPlayers.size() != 0)
	{
		delete m_vPlayers.back();
		m_vPlayers.pop_back();
	}

	while (m_vUnits.size() != 0)
	{
		m_vUnits.back()->Release();
		m_vUnits.pop_back();
	}
}
CPlayer* CGameManager::CreatePlayer(bool bAIControlled)
{
	CPlayer* pPlayer = new CPlayer(m_nNewPlayerID++);
	// TODO if bAIControlled add cplayer to list of AI controlled stuff
	// CAIManager::PushPlayerID(pPlayer->GetPLayerID());
	if (bAIControlled)
	{
		pPlayer->SetAI(true);
	}
	else
		pPlayer->SetAI(false);

	if (m_vPlayers.size() == 0)
	{
		m_pCurrentPlayer = pPlayer;
	}
	else
		m_pNextPlayer = pPlayer;
	m_vPlayers.push_back(pPlayer);
	return pPlayer;
}

CPlayer* CGameManager::GetPlayer(int nPlayerID)
{
	for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
	{
		if (m_vPlayers[i]->GetPlayerID() == nPlayerID)
		{
			return m_vPlayers[i];
			break;
		}

	}
	return nullptr;
}

int CGameManager::GetLevel(void)
{
	return -1;
}

void CGameManager::LoadLevel(std::string sFileName)
{
	std::ostringstream oss;
	oss << "Assets\\Scripts\\" << sFileName << ".xml";
	m_vScriptSpawns.clear();
	CScriptManager::GetInstance()->LoadScript(oss.str(), ST_LEVEL);
}

void CGameManager::LoadUnitsFromScript(void)
{
	for (decltype(m_vScriptSpawns.size()) i = 0; i < m_vScriptSpawns.size(); ++i)
	{
		ScriptedSpawn s = m_vScriptSpawns[i];
		if (GetCurrentTurn() == s.first)
		{
			CSpawnUnitMessage* pMSG = new CSpawnUnitMessage(Vec2D(s.second.sPos), s.second.nPlayerID, s.second.eType, s.second.nFacing);
			CMessageSystem::GetInstance()->SendMessageW(pMSG);
			m_vScriptSpawns.erase(m_vScriptSpawns.begin() + i);
			--i;
		}
	}

	CMessageSystem::GetInstance()->ProcessMessages();

}

void CGameManager::LoadMap(int nLevelNum)
{
	CTileManager* pTM=CTileManager::GetInstance();
	string filename= "Assets\\Tiles\\TestMap.xml";
	pTM->LoadSave(filename);
	// Attempting to load fake level 1 script
}

void CGameManager::SaveGame(int nSlot)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "");

	doc.LinkEndChild(pDec);

	TiXmlElement* pRoot = new TiXmlElement("Map");
	doc.LinkEndChild(pRoot);

	pRoot->SetAttribute("mapID", m_nCurrentLevel);
	pRoot->SetAttribute("phaseNumber", m_nPhaseCount);
	pRoot->SetAttribute("phase", m_nCurrentPhase);
	pRoot->SetAttribute("currPlayer", m_pCurrentPlayer->GetPlayerID());

	TiXmlElement* pPlayers = new TiXmlElement("Players");
	pRoot->LinkEndChild(pPlayers);
	for (int i = 0; i < 2; ++i)
	{
		TiXmlElement* pPlayer = new TiXmlElement("Player");
		pPlayers->LinkEndChild(pPlayer);
		pPlayer->SetAttribute("id", m_vPlayers[i]->GetPlayerID());
		pPlayer->SetAttribute("ai", (int)m_vPlayers[i]->GetAI());
		pPlayer->SetAttribute("AP", m_vPlayers[i]->GetAP());
		pPlayer->SetAttribute("wood", m_vPlayers[i]->GetWood());
		pPlayer->SetAttribute("metal", m_vPlayers[i]->GetMetal());

		TiXmlElement* pChampion = new TiXmlElement("Champion");
		CHero* pHero = dynamic_cast<CHero*>(GetChampion(m_vPlayers[i]->GetPlayerID()));
		pChampion->SetAttribute("posX", pHero->GetPos().nPosX);
		pChampion->SetAttribute("posY", pHero->GetPos().nPosY);
		pChampion->SetAttribute("health", pHero->GetHP());
		pChampion->SetAttribute("xp", m_vPlayers[i]->GetExp());
		pChampion->SetAttribute("facing", pHero->GetFacing());
		pChampion->SetAttribute("tilesMoved", pHero->GetTilesMoved());
		pChampion->SetAttribute("hasAttacked", (int)pHero->GetHasAttacked());
		// TODO: setup spell saving here

		pPlayer->LinkEndChild(pChampion);

		// Lets save the units!
		TiXmlElement* pUnits = new TiXmlElement("Units");
		pPlayer->LinkEndChild(pUnits);
		int nNumUnits = 0;
		for (decltype(m_vUnits.size()) j = 0; j < m_vUnits.size(); ++j)
		{
			// this is our unit, lets save it!
			if (m_vUnits[j]->GetPlayerID() == m_vPlayers[i]->GetPlayerID() && m_vUnits[j]->GetType() != UT_HERO)
			{
				TiXmlElement* pUnit = new TiXmlElement("Unit");
				CUnit* puni = m_vUnits[j];
				nNumUnits++;
				pUnit->SetAttribute("posX", puni->GetPos().nPosX);
				pUnit->SetAttribute("posY", puni->GetPos().nPosY);
				pUnit->SetAttribute("unitType", (int)puni->GetType());
				pUnit->SetAttribute("health", puni->GetHP());
				pUnit->SetAttribute("facing", puni->GetFacing());
				pUnit->SetAttribute("tilesMoved", puni->GetTilesMoved());
				pUnit->SetAttribute("hasAttacked", (int)puni->GetHasAttacked());
				pUnits->LinkEndChild(pUnit);
			}
		}
		pUnits->SetAttribute("numUnits", nNumUnits);
	}

	doc.SaveFile("Assets\\Scripts\\saveslot2.xml");
}
void CGameManager::LoadSave(int nSlot)
{
	Reset();
	std::ostringstream oss;
	oss << "Assets\\Scripts\\saveslot" << nSlot << ".xml";
	TiXmlDocument doc;
	if (doc.LoadFile(oss.str().c_str()))
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot == nullptr)
			return;

		int nMapID, nCurrPlayer, nPhaseCount, nCurrPhase;
		pRoot->QueryIntAttribute("mapID", &nMapID);
		pRoot->QueryIntAttribute("currPlayer", &nCurrPlayer);
		pRoot->QueryIntAttribute("phaseNumber", &nPhaseCount);
		pRoot->QueryIntAttribute("phase", &nCurrPhase);


		LoadMap(nMapID);
		TiXmlElement* pPlayers = pRoot->FirstChildElement("Players");
		TiXmlElement* pPlayer = pPlayers->FirstChildElement("Player");

		for (int np = 0; np < 2; ++np)
		{
			int nAIControlled;
			int nPlayerID;
			int nAP, nWood, nMetal;
			pPlayer->QueryIntAttribute("id", &nPlayerID);
			pPlayer->QueryIntAttribute("ai", &nAIControlled);
			pPlayer->QueryIntAttribute("wood", &nWood);
			pPlayer->QueryIntAttribute("AP", &nAP);
			pPlayer->QueryIntAttribute("metal", &nMetal);
			CPlayer* pplay = CreatePlayer((bool)nAIControlled);

			pplay->SetWood(nWood);
			pplay->SetAP(nAP);
			pplay->SetMetal(nMetal);


			TiXmlElement* pChampion = pPlayer->FirstChildElement("Champion");

			int nPosX, nPosY, nHealth, nXP, nFacing, nTilesMoved, nHasAttacked;
			// TODO: load in spells here from ability manager
			pChampion->QueryIntAttribute("posX", &nPosX);
			pChampion->QueryIntAttribute("posY", &nPosY);
			pChampion->QueryIntAttribute("health", &nHealth);
			pChampion->QueryIntAttribute("xp", &nXP);
			pChampion->QueryIntAttribute("facing", &nFacing);
			pChampion->QueryIntAttribute("tilesMoved", &nTilesMoved);
			pChampion->QueryIntAttribute("hasAttacked", &nHasAttacked);

			pplay->SetExp(nXP);

			CSpawnUnitMessage* pMsg = new CSpawnUnitMessage(Vec2D(nPosX, nPosY), nPlayerID, UT_HERO, nFacing, true, 
				nHealth, nTilesMoved, (bool)nHasAttacked);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);


			int nNumUnits;
			TiXmlElement* pUnits = pPlayer->FirstChildElement("Units");
			pUnits->QueryIntAttribute("numUnits", &nNumUnits);

			TiXmlElement* pUnit = pUnits->FirstChildElement("Unit");
			for (int i = 0; i < nNumUnits; ++i)
			{
				int nUnitPosX, nUnitPosY, nUnitType, nUnitHealth, nUnitFacing, nUnitTilesMoved, nUnitHasAttacked;
				pUnit->QueryIntAttribute("posX", &nUnitPosX);
				pUnit->QueryIntAttribute("posY", &nUnitPosY);
				pUnit->QueryIntAttribute("unitType", &nUnitType);
				pUnit->QueryIntAttribute("health", &nUnitHealth);
				pUnit->QueryIntAttribute("facing", &nUnitFacing);
				pUnit->QueryIntAttribute("tilesMoved", &nUnitTilesMoved);
				pUnit->QueryIntAttribute("hasAttacked", &nUnitHasAttacked);

				CSpawnUnitMessage* pUnitMsg = 
					new CSpawnUnitMessage(Vec2D(nUnitPosX, nUnitPosY), nPlayerID, (UNIT_TYPE)nUnitType, nUnitFacing, true, nUnitHealth,
						nUnitTilesMoved,(bool)nUnitHasAttacked );
				CMessageSystem::GetInstance()->SendMessageW(pUnitMsg);

				pUnit = pUnit->NextSiblingElement("Unit");
			}
			pPlayer = pPlayer->NextSiblingElement("Player");
		}


		SetCurrentPlayer(nCurrPlayer);
		if (nCurrPlayer == 0)
			SetNextPlayer(1);
		else
			SetNextPlayer(0);
		SetPhaseCount(nPhaseCount);
		SetCurrentPhase((GAME_PHASE)nCurrPhase);

	}
}

void CGameManager::AddUnit(CUnit* pUnit)
{
	m_vUnits.push_back(pUnit);
	pUnit->AddRef();
}
void CGameManager::RemoveUnit(CUnit* pUnit)
{
	std::vector<CUnit*>::iterator iter = m_vUnits.begin();

	while (iter != m_vUnits.end())
	{
		if ((*iter) == pUnit)
		{
			m_vUnits.erase(iter);
			pUnit->Release();
			break;
		}
		else
			++iter;
	}

}

// Reset the game and load whatever needs to be loaded
void CGameManager::Reset(void)
{
	for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
	{
		CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(m_vUnits[i]);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	//m_vUnits.clear();

	for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
	{
		delete m_vPlayers[i];
	}
	m_vPlayers.clear();
	m_nNewPlayerID = 0;
	m_vScriptSpawns.clear();

	CMessageSystem::GetInstance()->ProcessMessages();
	CTileManager::GetInstance()->ShutDown();

}
void CGameManager::NewGame(void)
{

	Reset();
	LoadLevel(string("level1"));
	LoadMap(1);

	m_nPhaseCount = 0;
	// Player 1 and his units
	m_nNewPlayerID = 0;
	CreatePlayer(false); // player 1
	CreatePlayer(false);

	LoadUnitsFromScript();



	m_nCurrentPhase = GP_MOVE;
}

int CGameManager::GetCurrentTurn(void)
{
	int nTurn = m_nPhaseCount / 4;

	return nTurn +1;
}
void CGameManager::Update(float fElapsedTime)
{
	LoadUnitsFromScript();

	int x = m_vUnits.size();

}
void CGameManager::SetNextPlayer(int nPlayerID)
{
	m_pNextPlayer = m_vPlayers[nPlayerID];
}

CUnit* CGameManager::FindUnit(int posX, int posY)
{
	std::vector<CUnit*>::iterator iter = m_vUnits.begin();

	while (iter != m_vUnits.end())
	{
		if ((*iter)->GetPos() == Vec2D(posX, posY))
		{
			return (*iter);
			break;
		}
		++iter;
	}
	return nullptr;
}
CUnit* CGameManager::FindUnit(Vec2D pos)
{
	return FindUnit(pos.nPosX, pos.nPosY);
}

// This is the MessageSystem MessageProc. Message handling is done here
void CGameManager::MessageProc(IMessage* pMsg)
{
	CGameManager* pThis = CGameManager::GetInstance();

	// MESSAGE HANDLING
	switch (pMsg->GetMessageID())
	{
	case MSG_SPAWNUNIT:
		{
			CSpawnUnitMessage* pSMSG = dynamic_cast<CSpawnUnitMessage*>(pMsg);
			CUnit* pUnit = (CUnit*)CObjectManager::GetInstance()->CreateObject(pSMSG->GetUnitType());
			pUnit->SetPos(pSMSG->GetPos());
			pUnit->SetFacing(pSMSG->GetFacing());
			pUnit->SetPlayerID(pSMSG->GetPlayerID());
			if (pSMSG->GetLoaded())
			{
				pUnit->SetHP(pSMSG->GetHealth());
				pUnit->SetTilesMoved(pSMSG->GetTilesMoved());
				pUnit->SetHasAttacked(pSMSG->GetHasAttacked());
			}
		}
		break;
	case MSG_DESPAWNUNIT:
		{
			CDespawnUnitMessage* pSMSG = dynamic_cast<CDespawnUnitMessage*>(pMsg);
			if (CGameplayState::GetInstance()->GetSelectedUnit() == pSMSG->GetUnit())
			{
				CGameplayState::GetInstance()->ClearSelections();
			}
			CTile* tile = CTileManager::GetInstance()->GetTile(pSMSG->GetUnit()->GetPos().nPosX, pSMSG->GetUnit()->GetPos().nPosY);
			int x = 9;
			tile->SetIfOccupied(false);
			CObjectManager::GetInstance()->RemoveObject(pSMSG->GetUnit());

		}
		break;
	case MSG_ADDRESOURCE:
		{
			CAddResourceMessage* pSMSG = dynamic_cast<CAddResourceMessage*>(pMsg);
			CPlayer* pPlayer = pThis->GetPlayer(pSMSG->GetPlayerID());

			switch (pSMSG->GetTileType())
			{
			case TT_FARM:
				{
					pPlayer->SetMaxPopCap(pPlayer->GetMaxPopCap() + POP_PER_FARM);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			case TT_MINE:
				{
					pPlayer->SetMetal(pPlayer->GetMetal() + METAL_PER_MINE);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			case TT_MILL:
				{
					pPlayer->SetWood(pPlayer->GetWood() + WOOD_PER_MILL);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

