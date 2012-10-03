#include "StdAfx.h"
#include "ObjectManager.h"

CObjectManager* CObjectManager::s_Instance = nullptr;


CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
}

void CObjectManager::AddObject( CUnit* pUnit )
{

}

void CObjectManager::RemoveObject( CUnit* pUnit )
{

}

void CObjectManager::RemoveAllObjects( void )
{

}

CObjectManager* CObjectManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CObjectManager();

	return s_Instance;
}

void CObjectManager::DeleteInstance( void )
{

}