#include "StdAfx.h"
#include "MultiplayerState.h"
#include "StateStack.h"
#include "SocketServer.h"
#include "BitmapFont.h"
#include "LevelSelectState.h"
CMultiplayerState::CMultiplayerState(void)
{
}


CMultiplayerState::~CMultiplayerState(void)
{

}
void CMultiplayerState::Enter(void)
{
	m_nMenuChoice = 0;
	byte1 = 127;
	byte2 = 0;
	byte3 = 0;
	byte4 = 1;
	m_bInputIPaddress = false;
	m_nIPBracketLeft = 0;
	m_bNetworkSetup = true;
	m_bWaitingForHost = false;
	m_bWaitingForPlayer = false;
}
void CMultiplayerState::Exit(void)
{
	m_bNetworkSetup = false;
}
void CMultiplayerState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_UP:
		{
			if (m_bInputIPaddress)
			{
				switch (m_nIPBracketLeft)
				{
				case 0:
					byte1++;
					break;
				case 1:
					byte2++;
					break;
				case 2:
					byte3++;
					break;
				case 3:
					byte4++;
					break;
				}
			}
			else
			{
			m_nMenuChoice--;

			if (m_nMenuChoice < 0)
				m_nMenuChoice = 1;
			}
		}
		break;
	case INPUT_DOWN:
		{
			if (m_bInputIPaddress)
			{
				switch (m_nIPBracketLeft)
				{
				case 0:
					byte1--;
					break;
				case 1:
					byte2--;
					break;
				case 2:
					byte3--;
					break;
				case 3:
					byte4--;
					break;
				}
			}
			else
			{
			m_nMenuChoice++;

				if (m_nMenuChoice > 1)
				m_nMenuChoice = 0;
			}
		}
		break;
	case INPUT_LEFT:
		{
			if (m_bInputIPaddress)
			{
				m_nIPBracketLeft--;
				if (m_nIPBracketLeft < 0)
					m_nIPBracketLeft = 3;
			}
		}
		break;
	case INPUT_RIGHT:
		{
			if (m_bInputIPaddress)
			{
				m_nIPBracketLeft++;
				if (m_nIPBracketLeft > 3)
					m_nIPBracketLeft = 0;
			}

		}
		break;
	case INPUT_ACCEPT:
		{
			if (m_bInputIPaddress == true)
			{
				m_bWaitingForHost = CSocketClient::GetInstance()->Initialize(byte1, byte2, byte3, byte4);
			}
			else if (m_nMenuChoice == 0)
			{
				CSocketServer::GetInstance()->Initialize();
				CSocketClient::GetInstance()->Initialize();
				m_bWaitingForPlayer = true;
			}
			else if (m_nMenuChoice == 1)
			{
				m_bInputIPaddress = true;
			}


		}
		break;
	case INPUT_CANCEL:
		{
			if (m_bInputIPaddress)
				m_bInputIPaddress=false;
			else
			CStateStack::GetInstance()->Pop();
		}
		break;
	}
}
void CMultiplayerState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	static float fDown, fUp = 0.0f;
	if (m_bInputIPaddress)
	{
		if (pDI->KeyDown(DIK_DOWN))
		{
			if (fDown < 1.0f)
			{
				fDown+= fElapsedTime;
			}
			else if (fDown > 1.0f)
			{
				Input(INPUT_DOWN);
			}

		}
		else if (pDI->KeyDown(DIK_UP))
		{
			if (fUp < 1.0f)
			{
				fUp += fElapsedTime;
			}
			else if (fUp > 1.0f)
			{
			Input(INPUT_UP);
			}
		}
		if (pDI->KeyUp(DIK_DOWN))
		{
			fDown = 0.0f;
		}
		else if (pDI->KeyUp(DIK_UP))
		{
			fUp = 0.0f;
		}
	}
}

void CMultiplayerState::PlayerConnected(void)
{
	m_bNetworkSetup = true;
	CGame::GetInstance()->SetDieThread(true);
}
void CMultiplayerState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);
	CBitmapFont mBitmapFont;

	std::ostringstream oss;
	if (m_bWaitingForHost)
	{
		oss << "Waiting for host to select map...\n";
		D3DCOLOR col = D3DCOLOR_XRGB(255, 255, 255);
		mBitmapFont.Print(oss.str().c_str(), 100, 90, 0.5f, col);


	}
	else if (m_bWaitingForPlayer)
	{
		oss << "Waiting for player to connect...\n";
		D3DCOLOR col = D3DCOLOR_XRGB(255, 255, 255);
		mBitmapFont.Print(oss.str().c_str(), 100, 90, 0.7f, col);
	}
	else
	{

		oss << "Host Network Game";
		D3DCOLOR col = D3DCOLOR_XRGB(255, 255, 255);
		if (m_nMenuChoice == 0)
			col = D3DCOLOR_XRGB(255, 255, 0);
		else
			col = D3DCOLOR_XRGB(255, 255, 255);
		mBitmapFont.Print(oss.str().c_str(), 160, 90, 0.8f, col);

		oss.str("");
		oss << "Join Network Game";
		if (m_nMenuChoice == 1)
			col = D3DCOLOR_XRGB(255, 255, 0);
		else
			col = D3DCOLOR_XRGB(255, 255, 255);
		mBitmapFont.Print(oss.str().c_str(), 185, 160, 0.7f, col);

		if (m_bInputIPaddress)
		{
			oss.str("");
			oss << (int)byte1;
			if (m_nIPBracketLeft == 0)
				col = D3DCOLOR_XRGB(255, 255, 0);
			else
				col = D3DCOLOR_XRGB(255, 255, 255);
			mBitmapFont.Print(oss.str().c_str(), 205, 240, 0.6f, col);

			oss.str("");
			oss << (int)byte2;
			if (m_nIPBracketLeft == 1)
				col = D3DCOLOR_XRGB(255, 255, 0);
			else
				col = D3DCOLOR_XRGB(255, 255, 255);
			mBitmapFont.Print(oss.str().c_str(), 305, 240, 0.6f, col);

			oss.str("");
			oss << (int)byte3;
			if (m_nIPBracketLeft == 2)
				col = D3DCOLOR_XRGB(255, 255, 0);
			else
				col = D3DCOLOR_XRGB(255, 255, 255);
			mBitmapFont.Print(oss.str().c_str(), 405, 240, 0.6f, col);

			oss.str("");
			oss << (int)byte4;
			if (m_nIPBracketLeft == 3)
				col = D3DCOLOR_XRGB(255, 255, 0);
			else
				col = D3DCOLOR_XRGB(255, 255, 255);
			mBitmapFont.Print(oss.str().c_str(), 505, 240, 0.6f, col);
		}
	}
}

CMultiplayerState* CMultiplayerState::GetInstance()
{
	static CMultiplayerState s_Instance;
	return &s_Instance;
}
