#include "StdAfx.h"
#include "GameModeState.h"
#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "StateStack.h"
#include "BitmapFont.h"
#include "LevelSelectState.h"
#include "SoundManager.h"

CGameModeState::CGameModeState(void)
{
}


CGameModeState::~CGameModeState(void)
{
}

CGameModeState* CGameModeState::GetInstance()
{
	static CGameModeState s_Instance;
	return &s_Instance;
}

void CGameModeState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_nSelected = 0;
}

void CGameModeState::Exit(void)
{

}

void CGameModeState::Input(INPUT_ENUM input)
{
	switch( input )
	{
	case INPUT_LEFT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_nSelected == 0 )
				m_nSelected = 1;
			else
				m_nSelected = 0;
		}
		break;

	case INPUT_RIGHT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_nSelected == 0 )
				m_nSelected = 1;
			else
				m_nSelected = 0;
		}
		break;

	case INPUT_ACCEPT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Sword")), false, false);
			LevelSelectState::GetInstance()->SetType(m_nSelected);
			CStateStack::GetInstance()->Push(LevelSelectState::GetInstance());
		}
		break;

	case INPUT_CANCEL:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Sword")), false, false);
			CStateStack::GetInstance()->Pop();
		}
		break;
	}
}

void CGameModeState::Update(float fElapsedTime)
{

}

void CGameModeState::Render(void)
{
	CBitmapFont pBitmapFont;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 80, -10, 1.3f, 1.2f);

	pBitmapFont.Print("Multi Player", 180, 150, 0.6f, m_nSelected == 0 ? D3DCOLOR_ARGB(255,  204, 153, 51) : D3DCOLOR_ARGB(255, 255, 255, 255));
	pBitmapFont.Print("Single Player", 440, 150, 0.6f, m_nSelected == 1 ? D3DCOLOR_ARGB(255,  204, 153, 51) : D3DCOLOR_ARGB(255, 255, 255, 255));

	if( m_nSelected == 0 )
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("multiplayer")), 290, 275, 1.0f, 1.0f);
	else
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("singleplayer")), 290, 275, 1.0f, 1.0f);

}
