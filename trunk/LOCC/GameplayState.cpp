#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"
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

	CParticleManager* pPM = CParticleManager::GetInstance();

	Vec2D test;
	test.nPosX = 400;
	test.nPosY = 300;

	pPM->LoadParticles( TEST, test );

	CTileManager* pTM=CTileManager::GetInstance();

	string filename= "Assets\\Tiles\\TestMap.xml";

	pTM->LoadSave(filename);


	// INITIALIZATION SETUP
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_CameraPos = Vec2D(0, 0);
	m_SelectionPos = Vec2D(0, 0);
}

void CGameplayState::Exit(void)
{
}
void CGameplayState::MoveCursor(int dX, int dY)
{
	m_SelectionPos.nPosX += dX;
	m_SelectionPos.nPosY += dY;
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
	std::wostringstream woss;
	woss << "Time Elapsed: " << fElapsedTime << "\n";
	OutputDebugString(woss.str().c_str());
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
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
	else if (pDI->KeyPressed(DIK_D)) // DEBUG DELETE SELECTED UNIT
	{
		if (m_pSelectedUnit)
		{
		CObjectManager::GetInstance()->RemoveObject(m_pSelectedUnit);
			Input(INPUT_CANCEL);
		}
	}

	// Testing Particle Rendering
	CParticleManager::GetInstance()->Update(fElapsedTime);
}

void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(1, 1, 1);
	CObjectManager::GetInstance()->RenderAllObjects();

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	
	//Render the map
	CTileManager::GetInstance()->Render();

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
	RECT selectRect = { m_SelectionPos.nPosX * nFakeTileWidth, m_SelectionPos.nPosY * nFakeTileHeight, 
		nFakeTileWidth, nFakeTileHeight};
	if (m_bIsMoving)
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 0, 255, 0);
	else
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 255, 255, 255);

}
