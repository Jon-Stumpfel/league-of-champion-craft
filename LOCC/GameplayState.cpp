#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Unit.h"
CGameplayState* CGameplayState::s_Instance = nullptr;

CGameplayState::CGameplayState(void)
{
}

CGameplayState::~CGameplayState(void)
{
}

CGameplayState* CGameplayState::GetInstance(void)
{
	if( s_Instance == nullptr )
		s_Instance = new CGameplayState();

	return s_Instance;
}

void CGameplayState::Enter(void)
{
	// test stuff
	OutputDebugString(_T("CREATING ARCHER\n"));
	CGameObject* pArcher = CObjectManager::GetInstance()->CreateObject(ARCHER);
	OutputDebugString(_T("CREATING SWORDSMAN\n"));
	CGameObject* pSwordsman = CObjectManager::GetInstance()->CreateObject(SWORDSMAN);

	OutputDebugString(_T("CREATING HERO\n"));
	CGameObject* pHero = CObjectManager::GetInstance()->CreateObject(HERO);

	OutputDebugString(_T("CREATING ICEBLOCK\n"));
	CGameObject* pIceblock = CObjectManager::GetInstance()->CreateObject(ICEBLOCK);

	OutputDebugString(_T("CREATING SKELETON\n"));
	CGameObject* pSkeleton = CObjectManager::GetInstance()->CreateObject(SKELETON);

	OutputDebugString(_T("CREATING CAVALRY\n"));
	CGameObject* pCavalry = CObjectManager::GetInstance()->CreateObject(CAVALRY);

	CObjectManager::GetInstance()->RemoveObject(pArcher);
	OutputDebugString(_T("CREATING NEW ARCHER\n"));
	CGameObject* pNewArcher = CObjectManager::GetInstance()->CreateObject(ARCHER);

	CObjectManager* pOM = CObjectManager::GetInstance();

	CObjectManager::DeleteInstance();
}

void CGameplayState::Exit(void)
{
}

void CGameplayState::Input(INPUT_ENUM input)
{
}

void CGameplayState::Update(float fElapsedTime)
{
}

void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(255, 0, 255);

}