#include "StdAfx.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "MessageSystem.h"
#include "InputManager.h"
#include "TileManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"

#include "StateStack.h"

CGame* CGame::GetInstance(void)
{	
	static CGame s_Instance;

	return &s_Instance;
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance,
	int nScreenWidth, int nScreenHeight,
	bool bIsWindowed)
{
	m_nWidth = nScreenWidth;
	m_nHeight = nScreenHeight;
	m_bIsWindowed = bIsWindowed;
	m_hWnd = hWnd;

	CInputManager::GetInstance()->Initialize(hWnd, hInstance);

	CMessageSystem::GetInstance()->InitMessageSystem(&CGameManager::MessageProc);
	CGraphicsManager::GetInstance()->Initialize(hWnd, hInstance, nScreenWidth, nScreenHeight, bIsWindowed);
	CStateStack::GetInstance()->Push(CGameplayState::GetInstance());
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	long x = 0;
	x = cursorPos.x; 
	long y = 0;
	y = cursorPos.y;
	CGameplayState::GetInstance()->SetMouseOffset(Vec2D((int)x, (int)y));
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\wphighlight.png"), _T("wphighlight"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\ui.png"), _T("uioverlay"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\panelselectioncursor.png"), _T("panelselect"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\moveabilityicon.png"), _T("moveicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\meleeabilityicon.png"), _T("meleeattackicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\rangeabilityicon.png"), _T("rangeattackicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\minimaptriangle.png"), _T("minitriangle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\minimapcircle.png"), _T("minicircle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\heroportrait.png"), _T("heroportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\archerportrait.png"), _T("archerportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\swordsmanportrait.png"), _T("swordsmanportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\cavalryportrait.png"), _T("cavalryportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\skeletonportrait.png"), _T("skeletonportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\iceblockportrait.png"), _T("iceblockportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\castleportrait.png"), _T("castleportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\speedicon.png"), _T("speedicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\rangeicon.png"), _T("rangeicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\damageicon.png"), _T("damageicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\tilesmovedicon.png"), _T("tilesmovedicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\shieldicon.png"), _T("shieldicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\showcard.png"), _T("showcard"), 0UL);

	m_dwCurrTime = GetTickCount();
}

bool CGame::Main(void)
{
	// Main state loop

	if (Input() == false)
		return false;

	Update();
	Render();

	return true;
}
void CGame::Shutdown(void)
{
	CScriptManager::DeleteInstance();
	CInputManager::DeleteInstance();
	CGraphicsManager::DeleteInstance();
	CGameManager::DeleteInstance();
	CObjectManager::DeleteInstance();
	CStateStack::DeleteInstance();
	CMessageSystem::DeleteInstance();
	CTileManager::DeleteInstance();
}

CGame::CGame(void)
{
}

CGame::~CGame(void)
{

}

// 3 actions for each frame:
bool CGame::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	CSGD_DirectInput::GetInstance()->ReadDevices();
	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_LALT) || CSGD_DirectInput::GetInstance()->KeyDown(DIK_RALT))
	{
		if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
		{
			CSGD_Direct3D::GetInstance()->ChangeDisplayParam(m_nWidth, m_nHeight, !m_bIsWindowed);
			m_bIsWindowed = !m_bIsWindowed;
			return true;
		}
	}

	
	// Working intercepting INputManager imeplenetation so that input is done here until then


	return CInputManager::GetInstance()->Input();
}
void CGame::Update(void)
{


	DWORD	dwNow =  GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) * 0.001f;

	m_dwCurrTime = dwNow;

	if (fElapsedTime > 2.0f)
		fElapsedTime = 2.0f;

	CMessageSystem* pMS = CMessageSystem::GetInstance();
	pMS->ProcessMessages();
	CStateStack::GetInstance()->UpdateStack(fElapsedTime);
}
void CGame::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 255);
	CSGD_Direct3D::GetInstance()->DeviceBegin();
	CSGD_Direct3D::GetInstance()->SpriteBegin();
	CStateStack::GetInstance()->RenderStack();
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->DeviceEnd();
	CSGD_Direct3D::GetInstance()->Present();
}