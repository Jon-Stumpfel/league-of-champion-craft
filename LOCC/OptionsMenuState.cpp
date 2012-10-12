#include "StdAfx.h"
#include "OptionsMenuState.h"
#include "StateStack.h"
//COptionsMenuState* COptionsMenuState::s_Instance = nullptr;

COptionsMenuState::COptionsMenuState(void)
{
}


COptionsMenuState::~COptionsMenuState(void)
{
}


void COptionsMenuState::Enter(void)
{

}

void COptionsMenuState::Exit(void)
{

}

void COptionsMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		CStateStack::GetInstance()->Pop();
		break;
	}
}

void COptionsMenuState::Update(float fElapsedTime)
{

}

void COptionsMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(100, 200, 100);
}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}