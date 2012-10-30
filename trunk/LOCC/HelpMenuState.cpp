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
	temp = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/HelpScreen.png"),D3DXCOLOR(255,255,255,255));
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
			CStateStack::GetInstance()->Pop();
		}
	}
}

void CHelpMenuState::Update(float fElapsedTime)
{
}

void CHelpMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(255, 255, 255);
	CSGD_TextureManager::GetInstance()->Draw(temp,0,0,1.55f,1.18f,0,0,0,0,D3DXCOLOR(255,255,255,255));
}

CHelpMenuState* CHelpMenuState::GetInstance()
{
	static CHelpMenuState s_Instance;
	return &s_Instance;
}
