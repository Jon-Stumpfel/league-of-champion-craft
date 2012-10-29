#include "StdAfx.h"
#include "MainMenuState.h"
#include "StateStack.h"
#include "GameplayState.h"
#include "GameManager.h"
#include "SaveSlotState.h"
#include "OptionsMenuState.h"
#include "CreditsState.h"
#include "HelpMenuState.h"
#include "MultiplayerState.h"
#include "SocketServer.h"

//CMainMenuState* CMainMenuState::s_Instance = nullptr;

CMainMenuState::CMainMenuState(void)
{
	
}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	selected = 0;
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	swordid = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\main_menu_bg.png"),D3DXCOLOR(0,0,0,255));
	blueguyid = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\warrior_blue.png"),D3DXCOLOR(0,0,0,255));
	redguyid = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\warrior_red.png"),D3DXCOLOR(0,0,0,255));
	m_pBitmapFont = new CBitmapFont();
	CInputManager::GetInstance()->SetInMenu(true);
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	m_pBitmapFont = new CBitmapFont();
	int soundvolume = 0;
	int musicvolume = 0;
	bool windowed = false;
	bool IsModern = true;
	TiXmlDocument doc;
	doc.LoadFile("Assets\\Menus\\Options.xml");
	TiXmlElement* pRoot = doc.RootElement();
	TiXmlElement* Option = pRoot->FirstChildElement("Option");
	while(Option != nullptr)
	{
		Option->Attribute("SoundVolume", &soundvolume);
		Option->Attribute("MusicVolume", &musicvolume);
		int temp = 0;
		Option->Attribute("Fullscreen", &temp);
		if(temp == 0)
			windowed = false;
		else
			windowed = true;
		temp = 0;
		Option->Attribute("IsModern", &temp);
		if(temp == 0)
			IsModern = false;
		else
			IsModern = true;
		Option = Option->NextSiblingElement("Option");
	}
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume/100));
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume/100));
	CGame::GetInstance()->SetIsWindowed(windowed);
	StringTable::GetInstance()->SetLanguage(IsModern);
}

void CMainMenuState::Exit(void)
{
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	CInputManager::GetInstance()->SetInMenu(false);
}

void CMainMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_ACCEPT:
		{
			if(selected == 0)
			{
				CStateStack::GetInstance()->Push(LevelSelectState::GetInstance());
			}
			else if(selected == 1)
			{
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 2)
			{
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 3)
			{
				CStateStack::GetInstance()->Push(CCreditsState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 4)
			{
				CStateStack::GetInstance()->Push(CHelpMenuState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else
			{
				CInputManager::GetInstance()->SetRunning(false);
				CStateStack::GetInstance()->Pop();
			}
			break;
		}
	case INPUT_UP:
		{
			if(selected != 0)
				selected--;
			else
				selected = 5;
			break;
		}
	case INPUT_DOWN:
		{
			if(selected != 5)
				selected++;
			else
				selected = 0;
			break;
		}
	}
}

void CMainMenuState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if (pDI->KeyPressed(DIK_G))
	{
		CSocketClient::GetInstance()->Initialize();
	}
	else if (pDI->KeyPressed(DIK_H))
	{
		CSocketClient::GetInstance()->Shutdown();
	}
	else if (pDI->KeyPressed(DIK_M))
	{
		CStateStack::GetInstance()->Push(CMultiplayerState::GetInstance());
	}
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);

	CSGD_TextureManager::GetInstance()->Draw(blueguyid,0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(redguyid,290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(swordid,15,-5,0.7f,0.7f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	if(selected == 0)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
			("Start").c_str(),360,200,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
			("Start").c_str(),360,200,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 1)
	{
		const char* Load = "Load";
		m_pBitmapFont->Print(Load,364,250,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		const char* Load = "Load";
		m_pBitmapFont->Print(Load,364,250,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 2)
	{
		const char* Options = "Options";
		m_pBitmapFont->Print(Options,343,300,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		const char* Options = "Options";
		m_pBitmapFont->Print(Options,343,300,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 3)
	{
		const char* Credits = "Credits";
		m_pBitmapFont->Print(Credits,348,350,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		const char* Credits = "Credits";
		m_pBitmapFont->Print(Credits,348,350,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 4)
	{
		const char* Help = "Help";
		m_pBitmapFont->Print(Help,365,400,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		const char* Help = "Help";
		m_pBitmapFont->Print(Help,365,400,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 5)
	{
		const char* Exit = "Exit";
		m_pBitmapFont->Print(Exit,364,450,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		const char* Exit = "Exit";
		m_pBitmapFont->Print(Exit,364,450,0.7f,D3DXCOLOR(255,255,255,255));
	}

}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState s_Instance;
	return &s_Instance;
}
