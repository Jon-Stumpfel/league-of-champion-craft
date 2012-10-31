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
			m_nVerticalChoice++;
			if (m_nVerticalChoice > 3)
				m_nVerticalChoice = 0;
		}
		break;
	case INPUT_UP:
		{
			m_nVerticalChoice--;
			if (m_nVerticalChoice < 0)
				m_nVerticalChoice = 3;
		}
		break;
	case INPUT_ACCEPT:
		{
			switch (m_nVerticalChoice)
			{
			case 0:
				CStateStack::GetInstance()->Pop();
				break;
			case 1:
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				break;
			case 2:
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				break;
			case 3:
				{
					// shutdown the socket
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

	//CSGD_Direct3D::GetInstance()->DrawTextW(_T("Exit to Menu"), 350, 270, 255, 255, 255);
	m_pBitmapFont.Print(StringTable::GetInstance()->GetString("Exit to Menu")
		.c_str(), 350, 270, 0.4f, D3DCOLOR_XRGB(255, 255, 255));

	CGraphicsManager::GetInstance()->DrawArrow(330, 190 + m_nVerticalChoice * 30, 255, 255, 255);
}
