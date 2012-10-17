#include "StdAfx.h"
#include "HelpMenuState.h"
#include "StateStack.h"
#include "MainMenuState.h"
//CHelpMenuState* CHelpMenuState::s_Instance = nullptr;

CHelpMenuState::CHelpMenuState(void)
{
}


CHelpMenuState::~CHelpMenuState(void)
{
}
			 
void CHelpMenuState::Enter(void)
{

}

void CHelpMenuState::Exit(void)
{

}

void CHelpMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_ACCEPT:
		{
			CStateStack::GetInstance()->Switch(CMainMenuState::GetInstance());
		}
	}
}

void CHelpMenuState::Update(float fElapsedTime)
{

}

void CHelpMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(50, 200, 50);
}

CHelpMenuState* CHelpMenuState::GetInstance()
{
	static CHelpMenuState s_Instance;
	return &s_Instance;
}
