#include "StdAfx.h"
#include "GameManager.h"

CGameManager* CGameManager::s_Instance = nullptr;

CGameManager::CGameManager(void)
{
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

}

CPlayer* CGameManager::CreatePlayer(bool bAIControlled)
{
	return nullptr;
}
CPlayer* CGameManager::GetPlayer(int nPlayerID)
{
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