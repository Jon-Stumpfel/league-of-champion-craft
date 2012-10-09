#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"
#include "AddResourceMessage.h"
#include "DeSpawnUnitMessage.h"
#include "Unit.h"
#include "ParticleManager.h"
#include "Player.h"
#include "TileManager.h"
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

	CSpawnUnitMessage* pMsg = new CSpawnUnitMessage(Vec2D(1, 1), 0, UT_SWORDSMAN);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(2, 1), 0, UT_ARCHER);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(3, 1), 0, UT_HERO);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(4, 1), 0, UT_CAVALRY);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(5, 1), 0, UT_CASTLE);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(6, 1), 0, UT_SKELETON);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(7, 1), 0, UT_ICEBLOCK);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	CGameManager::GetInstance()->CreatePlayer(false);


	CGameManager::GetInstance()->CreatePlayer(false); // player 2
	pMsg = new CSpawnUnitMessage(Vec2D(3, 7), 1, UT_HERO);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	CGameManager* pGM = CGameManager::GetInstance();
	CParticleManager* pPM = CParticleManager::GetInstance();

	Vec2Df test;
	test.fVecX = 400;
	test.fVecY = 300;

	pPM->LoadParticles( TEST, test );

	test.fVecX = 100;
	test.fVecY = 100;
	pPM->LoadParticles( TESTSECOND,	test );

	CTileManager* pTM=CTileManager::GetInstance();

	string filename= "Assets\\Tiles\\TestMap.xml";

	pTM->LoadSave(filename);


	SetRect(&rCamRect, 0, 0, 
		CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth, CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight);

	// INITIALIZATION SETUP
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_CameraPos = Vec2D(0, 0);
	m_SelectionPos = Vec2D(0, 0);
}

int CGameplayState::GetCamOffsetX(void)
{
	return rCamRect.left * nFakeTileWidth;
}
int CGameplayState::GetCamOffsetY(void)
{
	return rCamRect.top * nFakeTileHeight;
}
void CGameplayState::Exit(void)
{
}
void CGameplayState::SnapToUnit(CUnit* pUnit)
{
	int nSelX = pUnit->GetPos().nPosX - m_SelectionPos.nPosX;
	int nSelY = pUnit->GetPos().nPosY - m_SelectionPos.nPosY;
	int nWindowTileWidth = CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth;
	int nWindowTileHeight = CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight;
	int nDesiredCamX = pUnit->GetPos().nPosX - (nWindowTileWidth / 2);
	int nDesiredCamY = pUnit->GetPos().nPosY - (nWindowTileHeight / 2);
	int camX = nDesiredCamX - m_CameraPos.nPosX;
	int camY = nDesiredCamY - m_CameraPos.nPosY;
	MoveCursor(nSelX, nSelY, false);
	MoveCamera(camX, camY);
}
void CGameplayState::MoveCursor(int dX, int dY, bool lock)
{
	m_SelectionPos.nPosX += dX;
	m_SelectionPos.nPosY += dY;

	// This locks camera to cursor position
	if (lock == true)
	{
		if (m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth) < m_SelectionPos.nPosX)
		{
			int n = m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth);
			int nDistance = m_SelectionPos.nPosX - n;
			MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosX > m_SelectionPos.nPosX)
		{
			int n = m_CameraPos.nPosX;
			int nDistance = m_SelectionPos.nPosX - n;
			MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosY + (CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight) < m_SelectionPos.nPosY)
		{
			int n = m_CameraPos.nPosY + (CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight);
			int nDistance = m_SelectionPos.nPosY - n;
			MoveCamera(0, nDistance);
		}
		if (m_CameraPos.nPosY > m_SelectionPos.nPosY)
		{
			int n = m_CameraPos.nPosY;
			int nDistance = m_SelectionPos.nPosY - n;
			MoveCamera(0, nDistance);
		}
	}

}
void CGameplayState::MoveCamera(int dX, int dY)
{
	OffsetRect(&rCamRect, dX, dY);
	m_CameraPos.nPosX += dX;
	m_CameraPos.nPosY += dY;
}
void CGameplayState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_UP:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving))
			{
				// do nothing, up arrow does nothing with a unit selected
			}
			else
			{
				MoveCursor(0, -1);
			}
		}
		break;
	case INPUT_LEFT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (ShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell--;
				//	if (m_nSelectedChampSpell < 0)
				//		m_nSelectedChampSpell = 3;
				//}
				//else
				//{
				//	// Champion ability is not pulled up, so just move the cursor on the main panel
				//	m_nSelectedAbility--;
				//	if (m_nSelectedAbility < 0)
				//		m_nSelectedAbility = 2;
				//}
			}
			else
				MoveCursor(-1, 0);
		}
		break;
	case INPUT_RIGHT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (m_bShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell++;
				//	if (m_nSelectedChampSpell > 3)
				//		m_nSelectedChampSpell = 0;
				//}
				//else
				//{
				//	// Champion ability is not pulled up, so just move the cursor on the main panel
				//	m_nSelectedAbility++;
				//	if (m_nSelectedAbility > 2)
				//		m_nSelectedAbility = 0;
				//}
			}
			else
				MoveCursor(1, 0);
		}
		break;
	case INPUT_DOWN:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected
			{
				// do nothing! Up arrow does nada;
			}
			else
				MoveCursor(0, 1);
		}
		break;
	case INPUT_ACCEPT:
		{
			if (m_pSelectedUnit == nullptr)
			{
				m_pSelectedUnit = CGameManager::GetInstance()->FindUnit(m_SelectionPos);
			}
			else
			{
				if (m_bIsMoving)
				{
					MoveToTile(m_SelectionPos);
				}
				else
					m_bIsMoving = true;
			}
		}
		break;
	case INPUT_CANCEL:
		{
			m_pSelectedUnit = nullptr;
			m_bIsMoving = false;
		}
		break;
	case INPUT_CAM_UP:
		MoveCamera(0, -1);
		break;
	case INPUT_CAM_DOWN:
		MoveCamera(0, 1);
		break;
	case INPUT_CAM_LEFT:
		MoveCamera(-1, 0);
		break;
	case INPUT_CAM_RIGHT:
		MoveCamera(1, 0);
		break;
	default:
		break;
	}
}
void CGameplayState::MoveToTile(Vec2D nTilePosition)
{
	m_pSelectedUnit->SetPos(nTilePosition);
	m_bIsMoving = false;
}
void CGameplayState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if (pDI->KeyPressed(DIK_W))
	{
		Input(INPUT_CAM_UP);
	}
	else if (pDI->KeyPressed(DIK_S))
	{
		Input(INPUT_CAM_DOWN);
	}
	else if (pDI->KeyPressed(DIK_A))
	{
		Input(INPUT_CAM_LEFT);
	}
	else if (pDI->KeyPressed(DIK_D))
	{
		Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementX() < -nMouseSensitivity)
	{
		Input(INPUT_CAM_LEFT);
	}
	else if (pDI->MouseMovementX() > nMouseSensitivity)
	{
		Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementY() < -nMouseSensitivity)
	{
		Input(INPUT_CAM_UP);
	}
	else if (pDI->MouseMovementY() > nMouseSensitivity)
	{
		Input(INPUT_CAM_DOWN);
	}

	if (pDI->KeyPressed(DIK_UP))
		Input(INPUT_UP);
	else if (pDI->KeyPressed(DIK_LEFT))
		Input(INPUT_LEFT);
	else if (pDI->KeyPressed(DIK_RIGHT))
		Input(INPUT_RIGHT);
	else if (pDI->KeyPressed(DIK_DOWN))
		Input(INPUT_DOWN);
	else if (pDI->KeyPressed(DIK_RETURN))
		Input(INPUT_ACCEPT);
	else if (pDI->KeyPressed(DIK_Z))
		Input(INPUT_CANCEL);
	else if (pDI->KeyPressed(DIK_T)) // DEBUG DELETE SELECTED UNIT
	{
		if (m_pSelectedUnit)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(m_pSelectedUnit);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);

			Input(INPUT_CANCEL);
		}
	}
	else if (pDI->KeyPressed(DIK_R))
	{
		CAddResourceMessage* pMsg = new CAddResourceMessage(TT_MINE, 0);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	else if (pDI->KeyPressed(DIK_Y))
	{
		SnapToUnit(CGameManager::GetInstance()->GetChampion(0));
	}
	else if (pDI->KeyPressed(DIK_U))
	{
		SnapToUnit(CGameManager::GetInstance()->GetChampion(1));
	}
	else if (pDI->KeyPressed(DIK_I))
	{
		CGameManager* pGM = CGameManager::GetInstance();
		int x = 9;
	}
	// Testing Particle Rendering
	CParticleManager::GetInstance()->Update(fElapsedTime);
}

void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);
	CTileManager::GetInstance()->Render();
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	CObjectManager::GetInstance()->RenderAllObjects();

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();


	//Render the map

	// Testing particle rendering
	CParticleManager::GetInstance()->Render();

	// DEBUG STUFF
	CPlayer* pDebugPlayer = CGameManager::GetInstance()->GetPlayer(0);
	std::wostringstream oss;
	oss << "Player: " << pDebugPlayer->GetPlayerID() << ", AP: " << pDebugPlayer->GetAP() << ", POP: "
		<< pDebugPlayer->GetPopCap() << ", WOOD: " << pDebugPlayer->GetWood() << ", METAL: " << pDebugPlayer->GetMetal() << '\n';
	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 0, 255, 255, 255);

	oss.str(_T(""));
	oss << "Selected Unit: ";
	if (m_pSelectedUnit != nullptr)
	{
		oss << m_pSelectedUnit->GetType() << ", X: " << m_pSelectedUnit->GetPos().nPosX << ", Y: " << 
			m_pSelectedUnit->GetPos().nPosY << ", HP: " << m_pSelectedUnit->GetHP();
	}
	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 350, 255, 255, 255);


	// selection cursor
	RECT selectRect = { m_SelectionPos.nPosX * nFakeTileWidth - GetCamOffsetX(), m_SelectionPos.nPosY * nFakeTileHeight - GetCamOffsetY(),  
		nFakeTileWidth, nFakeTileHeight};
	if (m_bIsMoving)
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 0, 255, 0);
	else
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 255, 255, 255);

}
