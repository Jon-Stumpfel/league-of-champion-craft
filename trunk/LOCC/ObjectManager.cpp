#include "StdAfx.h"
#include "ObjectManager.h"
#include "Castle.h"
#include "Archer.h"
#include "Swordsman.h"
#include "Hero.h"
#include "Iceblock.h"
#include "Skeleton.h"
#include "Hero.h"
#include "Cavalry.h"

CObjectManager* CObjectManager::s_Instance = nullptr;


CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
}

// Object Factory! Take in type, return a new version of whatever you make. This returns
// CGAmeObject so make sure to cast it to archer or unit or whatever you want if you want to work on it
CGameObject* CObjectManager::CreateObject(UNIT_TYPE type)
{
	CGameObject* pNewObject = nullptr;
	switch (type)
	{
	case CASTLE:
		pNewObject = new CCastle();
		break;
	case ARCHER:
		pNewObject = new CArcher();
		break;
	case CAVALRY:
		pNewObject = new CCavalry();
		break;
	case HERO:
		pNewObject = new CHero();
		break;
	case ICEBLOCK:
		pNewObject = new CIceblock();
		break;
	case SWORDSMAN:
		pNewObject = new CSwordsman();
		break;
	case SKELETON:
		pNewObject = new CSkeleton();
		break;
	default:
		assert( pNewObject != nullptr && "CObjectManager::CreateObject did not receive a valid input");
		break;
	}
	AddObject(pNewObject);
	return pNewObject;
}

// Add an object to the list of things to be handled
void CObjectManager::AddObject( CGameObject* pObject )
{
	assert(pObject != nullptr && "CObjectManager::AddObject - pObject is null!");
	m_pObjectList.push_back(pObject);

	pObject->AddRef();
}

// Remove an object! 
void CObjectManager::RemoveObject( CGameObject* pObject )
{
	assert(pObject != nullptr && "CObjectManager::RemoveObject - pObject is null!");

	OListIterator iter = m_pObjectList.begin();

	while (iter != m_pObjectList.end())
	{
		if ((*iter) == pObject)
		{
			m_pObjectList.erase(iter);

			pObject->Release();
			break;
		}
		else
			++iter;
	}
}

// Call the ->Update() on errythang
void CObjectManager::UpdateAllObjects(float fElapsedTime)
{
	for (OListIterator iter = m_pObjectList.begin(); iter != m_pObjectList.end(); ++iter)
		(*iter)->Update(fElapsedTime);

}

// Remove everything from the list. END OF LINE
void CObjectManager::RemoveAllObjects( void )
{
	for (OListIterator iter = m_pObjectList.begin(); iter != m_pObjectList.end(); ++iter)
		(*iter)->Release();
	m_pObjectList.clear();
}

// Call render on everything.
void CObjectManager::RenderAllObjects(void)
{
	for (OListIterator iter = m_pObjectList.begin(); iter != m_pObjectList.end(); ++iter)
		(*iter)->Render();
}

CObjectManager* CObjectManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CObjectManager();

	return s_Instance;
}

void CObjectManager::DeleteInstance( void )
{
	if (s_Instance != nullptr)
	{
		s_Instance->RemoveAllObjects();
		delete s_Instance;

	}

	s_Instance = nullptr;
}