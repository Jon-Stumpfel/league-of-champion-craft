#include "StdAfx.h"
#include "PauseState.h"
#include "SaveSlotState.h"
#include "OptionsMenuState.h"
#include "MainMenuState.h"
#include "GraphicsManager.h"
#include "StateStack.h"
#include "SocketServer.h"
#include "BitmapFont.h"
#include "Player.h"
#include "StringTable.h"
#include "SoundManager.h"
#include "HelpMenuState.h"

CPauseState::CPauseState(void)
{
}

CPauseState::~CPauseState(void)
{
}

CPauseState* CPauseState::GetInstance()
{
	static CPauseState s_Instance;
	return &s_Instance;
}

void CPauseState::Enter(void)
{
	m_nVerticalChoice = 0;
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic"))))
	{
		CSoundManager::GetInstance()->Stop(CSoundManager::GetInstance()->
			GetID(_T("AttackPhaseMusic")));
		CSoundManager::GetInstance()->Stop(CSoundManager::GetInstance()->
			GetID(_T("MovementPhaseMusic")));
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->
			GetID(_T("MainMenuMusic")),true,true);
	}
}
void CPauseState::Exit(void)
{
}
void CPauseState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_DOWN:
		{
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			m_nVerticalChoice++;
			if (m_nVerticalChoice > 4)
				m_nVerticalChoice = 0;
		}
		break;
	case INPUT_UP:
		{
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			m_nVerticalChoice--;
			if (m_nVerticalChoice < 0)
				m_nVerticalChoice = 4;
		}
		break;
	case INPUT_ACCEPT:
		{
			switch (m_nVerticalChoice)
			{
			case 0:
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				CStateStack::GetInstance()->Pop();
				break;
			case 1:
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				break;
			case 2:
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				break;

			case 3:
				{
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					CStateStack::GetInstance()->Push(CHelpMenuState::GetInstance());
				}
				break;

			case 4:
				{
					// shutdown the socket
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					bool m_bQuit = true;
					if (CGameManager::GetInstance()->GetNetworkGame())
					{
						if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() != CSocketClient::GetInstance()->m_nNetworkPlayerID)
						{
							m_bQuit = false;
						}
						CSocketServer::GetInstance()->Shutdown();
						CSocketClient::GetInstance()->Shutdown();

					}
					if (m_bQuit)
					{
						CTileManager::GetInstance()->ShutDown();
						CSocketServer::GetInstance()->Shutdown();
						CSocketClient::GetInstance()->Shutdown();

						CStateStack::GetInstance()->Switch(CMainMenuState::GetInstance());


					}
					else
						CStateStack::GetInstance()->Pop();

				}
				break;
			}
		}
		break;
	case INPUT_CANCEL:
		{
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			CStateStack::GetInstance()->Pop();
			break;
		}
	}
}
void CPauseState::Update(float fElapsedTime)
{
}
void CPauseState::Render(void)
{
/////////////////////////////////////////////////////////////////
// BUG FIX
// Reference Bug # BB-042
// BUG FIX START
/////////////////////////////////////////////////////////////////
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 290, 100, 0.65f, .5f, (RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));
/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-042
/////////////////////////////////////////////////////////////////
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	// lol rainbow text just for the time being
	std::ostringstream woss;
	woss << StringTable::GetInstance()->GetString("GAME PAUSED");
	static int r = 255, g = 0,b = 255;
	static int redAmt = 1, greenAmt = 1;
	r -= redAmt;
	g += greenAmt;
	//b -= 1;

	if (r < 1 || r > 254)
		redAmt *= -1;
	if (g < 1 || g > 254)
		greenAmt *= -1;
	if (b < 0)
		b = 255;

	//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 335, 150, r, g,b);
	CBitmapFont m_pBitmapFont;
	m_pBitmapFont.Print(woss.str().c_str(), 335, 150, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	//CSGD_Direct3D::GetInstance()->DrawTextW(_T("Resume Game"), 350, 180, 255, 255, 255);
	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Resume Game")
		.c_str(), 350, 180, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	//CSGD_Direct3D::GetInstance()->DrawTextW(_T("Options"), 350, 210, 255, 255, 255);
	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Options")
		.c_str(), 350, 210, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	//CSGD_Direct3D::GetInstance()->DrawTextW(_T("Save/Load"), 350, 240, 255, 255, 255);
	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Save/Load")
		.c_str(), 350, 240, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Help")
		.c_str(), 350, 270, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	//CSGD_Direct3D::GetInstance()->DrawTextW(_T("Exit to Menu"), 350, 270, 255, 255, 255);
	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Exit to Menu")
		.c_str(), 350, 300, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	CGraphicsManager::GetInstance()->DrawArrow(330, 190 + m_nVerticalChoice * 30, 0, 0, 0);
	CGraphicsManager::GetInstance()->DrawArrow(328, 188 + m_nVerticalChoice * 30, 255, 255, 255);

}
