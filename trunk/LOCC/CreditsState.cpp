#include "StdAfx.h"
#include "CreditsState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "StringTable.h"
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
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Credits:").c_str(),290,103,1.0f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Art: Maher Sagrillo").c_str(),304,153,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Lead Producer: Jon").c_str(),300,168,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Sounds: Jordan Wells").c_str(),295,183,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Tile Engine: Dalton Gbur").c_str(),283,198,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Core Gameplay: Kyle Veilleux").c_str(),260,213,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Particle Engine: Ryan Cartier").c_str(),259,228,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Animation Engine: Jon Stumpfel").c_str(),247,243,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Assistant Producer: Robert Martinez").c_str(),216,258,0.3f,D3DXCOLOR(255,255,255,255));
	m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Minor units also provided by Blizzard Entertainment").c_str(),145,274,0.3f,D3DXCOLOR(255,255,255,255));
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
