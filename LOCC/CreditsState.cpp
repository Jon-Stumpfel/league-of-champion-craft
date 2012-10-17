#include "StdAfx.h"
#include "CreditsState.h"
#include "StateStack.h"
#include "MainMenuState.h"
//CCreditsState* CCreditsState::s_Instance = nullptr;

CCreditsState::CCreditsState(void)
{
}

CCreditsState::~CCreditsState(void)
{
}

void CCreditsState::Enter(void)
{

}

void CCreditsState::Exit(void)
{

}

void CCreditsState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_ACCEPT:
		{
			CStateStack::GetInstance()->Pop();
		}
	}
}

void CCreditsState::Update(float fElapsedTime)
{

}

void CCreditsState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(200, 50, 50);
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
