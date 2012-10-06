#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"
#include "Unit.h"
#include "Player.h"
//CGameplayState* CGameplayState::s_Instance = nullptr;

CGameplayState::CGameplayState(void)
{
}

CGameplayState::~CGameplayState(void)
{
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState s_Instance;
	return &s_Instance;
	//if( s_Instance == nullptr )
	//	s_Instance = new CGameplayState();

	//return s_Instance;
}

void CGameplayState::Enter(void)
{
	// test stuff

	CSpawnUnitMessage* pMsg = new CSpawnUnitMessage(Vec2D(10, 10), 0, UT_SWORDSMAN);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

//	OutputDebugString(_T("CREATING ARCHER\n"));
//	CGameObject* pArcher = CObjectManager::GetInstance()->CreateObject(UT_ARCHER);
//	OutputDebugString(_T("CREATING SWORDSMAN\n"));
//	CGameObject* pSwordsman = CObjectManager::GetInstance()->CreateObject(UT_SWORDSMAN);
//
//	OutputDebugString(_T("CREATING HERO\n"));
//	CGameObject* pHero = CObjectManager::GetInstance()->CreateObject(UT_HERO);
//
//	OutputDebugString(_T("CREATING ICEBLOCK\n"));
//	CGameObject* pIceblock = CObjectManager::GetInstance()->CreateObject(UT_ICEBLOCK);
//
//	OutputDebugString(_T("CREATING SKELETON\n"));
//	CGameObject* pSkeleton = CObjectManager::GetInstance()->CreateObject(UT_SKELETON);
//
//	OutputDebugString(_T("CREATING CAVALRY\n"));
//	CGameObject* pCavalry = CObjectManager::GetInstance()->CreateObject(UT_CAVALRY);
////	CObjectManager::GetInstance()->RemoveObject(pArcher);
//	OutputDebugString(_T("CREATING NEW ARCHER\n"));
//	CGameObject* pNewArcher = CObjectManager::GetInstance()->CreateObject(UT_ARCHER);
//
//
//	CGameObject* pCastle = CObjectManager::GetInstance()->CreateObject(UT_CASTLE);
//
//
//
//	CPlayer* pPlayer = CGameManager::GetInstance()->CreatePlayer(false);
//
//	CGameManager* pGM  = CGameManager::GetInstance();
//
//
//	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\Animations\\footman.png"), _T("swordsman"), DWORD(0000));

	//CObjectManager::DeleteInstance();
}

void CGameplayState::Exit(void)
{
}

void CGameplayState::Input(INPUT_ENUM input)
{
}

void CGameplayState::Update(float fElapsedTime)
{
	CObjectManager* pOM = CObjectManager::GetInstance();

}

void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(255, 0, 255);

	CObjectManager::GetInstance()->RenderAllObjects();
}