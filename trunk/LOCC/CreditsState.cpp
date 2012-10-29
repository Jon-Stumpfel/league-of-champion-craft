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
	Scroll = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\scroll.png"), D3DXCOLOR(255,255,255,255));
	m_pBitmapFont = new CBitmapFont();
}

void CCreditsState::Exit(void)
{
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
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
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);
	RECT* toprect = new RECT();
	toprect->bottom = 392;
	toprect->top = 198;
	toprect->left = 15;
	toprect->right = 537;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,25,100,1.44f,2.3f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 113;
	toprect->top = 0;
	toprect->left = 0;
	toprect->right = 555;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,0,0,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 584;
	toprect->top = 472;
	toprect->left = 2;
	toprect->right = 557;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,0,487,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 77;
	toprect->top = 56;
	toprect->left = 152;
	toprect->right = 402;
	delete toprect;
	toprect = nullptr;
	const char* temp = "Credits:";
	m_pBitmapFont->Print(temp,290,103,1.0f,D3DXCOLOR(255,255,255,255));
	temp = "Art: Maher Sagrillo";
	m_pBitmapFont->Print(temp,304,153,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Lead Producer: Jon";
	m_pBitmapFont->Print(temp,300,168,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Sounds: Jordan Wells";
	m_pBitmapFont->Print(temp,295,183,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Tile Engine: Dalton Gbur";
	m_pBitmapFont->Print(temp,283,198,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Core Gameplay: Kyle Veilleux";
	m_pBitmapFont->Print(temp,260,213,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Particle Engine: Ryan Cartier";
	m_pBitmapFont->Print(temp,259,228,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Animation Engine: Jon Stumpfel";
	m_pBitmapFont->Print(temp,247,243,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Assistant Producer: Robert Martinez";
	m_pBitmapFont->Print(temp,216,258,0.3f,D3DXCOLOR(255,255,255,255));
	temp = "Minor units also provided by Blizzard Entertainment";
	m_pBitmapFont->Print(temp,145,274,0.3f,D3DXCOLOR(255,255,255,255));
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
