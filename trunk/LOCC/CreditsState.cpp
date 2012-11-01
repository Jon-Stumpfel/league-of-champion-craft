#include "StdAfx.h"
#include "CreditsState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "StringTable.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
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
	m_nY = 123;
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
			CStateStack::GetInstance()->Pop();
		}
	}
}

void CCreditsState::Update(float fElapsedTime)
{

}

void CCreditsState::Render(void)
{
	int offset = 40;
	int xPos = 180;
	CBitmapFont pBitmapFont;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 80, -10, 1.3f, 1.2f);

	/*pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Credits:").c_str(), 290, 103, 1.0f, D3DXCOLOR(255,255,255,255));*/

	
	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Art: Maher Sagrillo").c_str(), xPos, m_nY, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Lead Producer: John O'Leske").c_str(), xPos, m_nY + offset, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Sounds: Jordan Wells").c_str(), xPos, m_nY + offset * 2, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Tile Engine: Dalton Gbur").c_str(), xPos, m_nY + offset * 3, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Core Gameplay: Kyle Veilleux").c_str(), xPos, m_nY + offset * 4, 0.5f, D3DXCOLOR(255,255,255,255));
	
	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Particle Engine: Ryan Cartier").c_str(), xPos, m_nY + offset * 5, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Animation Engine: Jon Stumpfel").c_str(), xPos, m_nY + offset * 6, 0.5f, D3DXCOLOR(255,255,255,255));

	pBitmapFont.Print(StringTable::GetInstance()->GetString
		("Assistant Producer: Robert Martinez").c_str(), xPos, m_nY + offset * 7, 0.4f, D3DXCOLOR(255,255,255,255));
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
