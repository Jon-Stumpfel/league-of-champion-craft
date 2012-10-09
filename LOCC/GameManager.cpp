#include "StdAfx.h"
#include "GameManager.h"
#include "GameplayState.h"
#include "ObjectManager.h"
#include "SpawnUnitMessage.h"
#include "DeSpawnUnitMessage.h"
#include "AddResourceMessage.h"

#include "Player.h"

CGameManager* CGameManager::s_Instance = nullptr;

CGameManager::CGameManager(void)
{
	m_nNewPlayerID = 0;
}


CGameManager::~CGameManager(void)
{
}

void CGameManager::NextPhase(void)
{

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
	if (m_vPlayers.size() == 0)
	{
		m_pCurrentPlayer = pPlayer;
	}
	m_vPlayers.push_back(pPlayer);
	return nullptr;
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

}

void CGameManager::LoadLevel(int nLevelNum)
{
}

void CGameManager::LoadSave(int nSlot)
{
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

void CGameManager::Reset(void)
{
	for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
	{
		CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(m_vUnits[i]);
	}
	m_vUnits.clear();

	for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
	{
		delete m_vPlayers[i];
	}
	m_vPlayers.clear();
}
void CGameManager::NewGame(void)
{
}
void CGameManager::Update(float fElapsedTime)
{

}
void CGameManager::SetNextPlayer(int nPlayerID)
{

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
			pUnit->SetPlayerID(pSMSG->GetPlayerID());
		}
		break;
	case MSG_DESPAWNUNIT:
		{
			CDespawnUnitMessage* pSMSG = dynamic_cast<CDespawnUnitMessage*>(pMsg);
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

