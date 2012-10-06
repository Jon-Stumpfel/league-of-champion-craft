#include "StdAfx.h"
#include "MainMenuState.h"
#include "StateStack.h"
//CMainMenuState* CMainMenuState::s_Instance = nullptr;

CMainMenuState::CMainMenuState(void)
{
}


CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{

}

void CMainMenuState::Exit(void)
{

}

void CMainMenuState::Input(INPUT_ENUM input)
{

}

void CMainMenuState::Update(float fElapsedTime)
{
	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CStateStack::GetInstance()->Pop();
	}
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(255, 0, 0);
}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState s_Instance;
	return &s_Instance;
}
