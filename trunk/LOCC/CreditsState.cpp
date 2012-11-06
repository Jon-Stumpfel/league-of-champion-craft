#include "StdAfx.h"
#include "CreditsState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "StringTable.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "SoundManager.h"
//CCreditsState* CCreditsState::s_Instance = nullptr;

CCreditsState::CCreditsState(void)
{
}

CCreditsState::~CCreditsState(void)
{
}

void CCreditsState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_nY = 530;
}

void CCreditsState::Exit(void)
{
}

void CCreditsState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

			CStateStack::GetInstance()->Pop();
		}
	}
}

void CCreditsState::Update(float fElapsedTime)
{
	if( m_nY < 75 - 40 * 7 )
		m_nY = 530;

	m_nY -= (int)(100 * fElapsedTime);
}

void CCreditsState::Render(void)
{
	int offset = 40;
	int xPos = 180;
	CBitmapFont pBitmapFont;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 80, -10, 1.3f, 1.2f);

	pBitmapFont.Print("Press Cancel to go back", xPos + 85, 555, .4f, D3DCOLOR_ARGB(255, 255, 255, 255));

	if( m_nY > 75 && m_nY < 530 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Art: Maher Sagrillo").c_str(), xPos, m_nY, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset && m_nY < 530 - offset )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Lead Producer: John O'Leske").c_str(), xPos, m_nY + offset, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset * 2 && m_nY < 530 - offset * 2 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Sounds: Jordan Wells").c_str(), xPos, m_nY + offset * 2, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset * 3 && m_nY < 530 - offset * 3 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Tile Engine: Dalton Gbur").c_str(), xPos, m_nY + offset * 3, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset * 4 && m_nY < 530 - offset * 4 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Core Gameplay: Kyle Veilleux").c_str(), xPos, m_nY + offset * 4, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset * 5 && m_nY < 530 - offset * 5 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Particle Engine: Ryan Cartier").c_str(), xPos, m_nY + offset * 5, 0.5f, D3DXCOLOR(255,255,255,255));
	}
	
	if( m_nY > 75 - offset * 6 && m_nY < 530 - offset * 6 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Animation Engine: Jon Stumpfel").c_str(), xPos, m_nY + offset * 6, 0.5f, D3DXCOLOR(255,255,255,255));
	}

	if( m_nY > 75 - offset * 7 && m_nY < 530 - offset * 7 )
	{
		pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Assistant Producer: Robert Martinez").c_str(), xPos, m_nY + offset * 7, 0.4f, D3DXCOLOR(255,255,255,255));
	}
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
