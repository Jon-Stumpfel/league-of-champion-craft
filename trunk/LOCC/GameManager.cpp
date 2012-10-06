#include "StdAfx.h"
#include "GameManager.h"
#include "Player.h"

CGameManager* CGameManager::s_Instance = nullptr;

CGameManager::CGameManager(void)
{
	m_nNewPlayerID = 0;
}


CGameManager::~CGameManager(void)
{
}

CGameManager* CGameManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CGameManager();
	return s_Instance;

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
}
CPlayer* CGameManager::CreatePlayer(bool bAIControlled)
{
	CPlayer* pPlayer = new CPlayer(m_nNewPlayerID++);
	// TODO if bAIControlled add cplayer to list of AI controlled stuff
	// CAIManager::PushPlayerID(pPlayer->GetPLayerID());

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

void CGameManager::MoveUnit(CUnit* u, int nDirection)
{
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

void CGameManager::Reset(void)
{
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