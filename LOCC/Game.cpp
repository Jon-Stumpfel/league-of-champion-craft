#include "StdAfx.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "MessageSystem.h"

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

	CSGD_DirectInput::GetInstance()->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE);

	CMessageSystem::GetInstance()->InitMessageSystem(&CGameManager::MessageProc);
	CGraphicsManager::GetInstance()->Initialize(hWnd, hInstance, nScreenWidth, nScreenHeight, bIsWindowed);
	CStateStack::GetInstance()->Push(CGameplayState::GetInstance());
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	float x = 0;
	x = cursorPos.x; 
	float y = 0;
	y = cursorPos.y;
	CGameplayState::GetInstance()->SetMouseOffset(Vec2D((int)x, (int)y));
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
	CGraphicsManager::DeleteInstance();
	CGameManager::DeleteInstance();
	CObjectManager::DeleteInstance();
	CStateStack::DeleteInstance();
	CMessageSystem::DeleteInstance();
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
	return true;
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