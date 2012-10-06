#include "StdAfx.h"
#include "Game.h"
#include "GameplayState.h"
#include "GraphicsManager.h"
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


	CGraphicsManager::GetInstance()->Initialize(hWnd, hInstance, nScreenWidth, nScreenHeight, bIsWindowed);


	currentState = CGameplayState::GetInstance();
	// Fake initialize of gameplay state just to get something running. 
	currentState->Enter();
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
	return true;
}
void CGame::Update(void)
{
	DWORD	dwNow = GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) * 0.001f;

	m_dwCurrTime = dwNow;

	if (fElapsedTime > 2)
		fElapsedTime = 2;

	currentState->Update(fElapsedTime);
}
void CGame::Render(void)
{
	currentState->Render();
}