#include "StdAfx.h"
#include "AbilityManager.h"

CAbilityManager* CAbilityManager::s_Instance = nullptr;

CAbilityManager::CAbilityManager(void)
{
}


CAbilityManager::~CAbilityManager(void)
{
}

CAbilityManager* CAbilityManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CAbilityManager();
	return s_Instance;
}
void CAbilityManager::DeleteInstance(void)
{
}


bool CAbilityManager::UseAbility(CAbility* pToUse, CTile* pTargetTile)
{
}

void CAbilityManager::Execute(CAbility* pToUse)
{
}
void CAbilityManager::Execute(CAbility* pToUse, CUnit* pTargetUnit)
{
}
void CAbilityManager::Execute(CAbility* pToUse, CTile* pTile)
{
}

void CAbilityManager::Initialize(void)
{
}
void CAbilityManager::Shutdown(void)
{
}