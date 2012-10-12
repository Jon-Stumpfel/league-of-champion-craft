#include "StdAfx.h"
#include "MainMenuState.h"
#include "StateStack.h"
#include "GameplayState.h"
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
	switch (input)
	{
	case INPUT_ACCEPT:
		CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
	}
}

void CMainMenuState::Update(float fElapsedTime)
{

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
