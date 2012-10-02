#include "StdAfx.h"
#include "AIManager.h"

CAIManager* CAIManager::s_Instance = nullptr;

CAIManager* CAIManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CAIManager();
	return s_Instance;
}
void CAIManager::DeleteInstance(void)
{
}

void CAIManager::RemoveObject(CUnit* obj)
{
}
void CAIManager::RemoveAllObjects(void)
{
}
void CAIManager::UpdateAI(float fElapsedTime)
{
}
void CAIManager::AddObject(CUnit* obj)
{
}


CAIManager::CAIManager(void)
{
}
CAIManager::~CAIManager(void)
{
}
