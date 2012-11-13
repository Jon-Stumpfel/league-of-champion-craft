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
#include "StringTable.h"
#include "SoundManager.h"
#include "GameModeState.h"
#include "AbilityManager.h"
//CMainMenuState* CMainMenuState::s_Instance = nullptr;

CMainMenuState::CMainMenuState(void)
{

}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	int* myInt = new int();


	selected = 0;
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	swordid = CGraphicsManager::GetInstance()->GetID(_T("mainmenubg"));
	blueguyid = CGraphicsManager::GetInstance()->GetID(_T("warriorblue"));
	redguyid = CGraphicsManager::GetInstance()->GetID(_T("warriorred"));
	//m_pBitmapFont = new CBitmapFont();
	CInputManager::GetInstance()->SetInMenu(true);
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	m_pBitmapFont = new CBitmapFont();
	int soundvolume = 0;
	int musicvolume = 0;
	bool windowed = CGame::GetInstance()->GetIsWindowed();
	bool IsModern = StringTable::GetInstance()->GetIsItModern();
	TiXmlDocument doc;

	wchar_t path[MAX_PATH];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_APPDATA, 0, SHGFP_TYPE_CURRENT, path);

	std::wstring pathtowrite(path, path+ wcslen(path));
	
	pathtowrite += L"\\LeagueOfChampionCraft";
	CreateDirectory(pathtowrite.c_str(), 0);

	std::wostringstream woss;
	woss << "\\Options.xml";
	pathtowrite += woss.str();
	std::string stringpath(pathtowrite.begin(), pathtowrite.end());




	if (doc.LoadFile(stringpath.c_str()))
	{
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
	}
	else
	{
		soundvolume = musicvolume = 100;
		windowed = true;
		IsModern = true;

	}
#ifdef ARCADE_BUILD
	windowed = false;
#endif
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume*0.01f));
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume*0.01f));
	CGame::GetInstance()->SetIsWindowed(windowed);
	StringTable::GetInstance()->SetLanguage(IsModern);
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
	int temp = NUMSPELLS;
	for(int i = 0; i < temp; i++)
	{
		if( CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i)) != nullptr )
			CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString(CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->GetDescription(), true));
	}
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
				CStateStack::GetInstance()->Push(CGameModeState::GetInstance());
			}
			else if(selected == 1)
			{
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 2)
			{
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(false);
			}
			else if(selected == 3)
			{
				CStateStack::GetInstance()->Push(CCreditsState::GetInstance());
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
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_UP:
		{
			if(selected != 0)
				selected--;
			else
				selected = 5;

		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_DOWN:
		{
			if(selected != 5)
				selected++;
			else
				selected = 0;

			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	}
}

void CMainMenuState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	//if (pDI->KeyPressed(DIK_M) && pDI->KeyDown(DIK_LCONTROL) && pDI->KeyDown(DIK_LSHIFT))
	//{
	//	CStateStack::GetInstance()->Push(CMultiplayerState::GetInstance());
	//}
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);

	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("main_menubg")), 0, 0, 1.0f, 1.0f);
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 300, 140, 0.47f, 0.76f);
	//CSGD_TextureManager::GetInstance()->Draw(blueguyid,0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	//CSGD_TextureManager::GetInstance()->Draw(redguyid,290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	//CSGD_TextureManager::GetInstance()->Draw(swordid,15,-5,0.7f,0.7f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	if(selected == 0)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Start").c_str(),360,200,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Start").c_str(),335,200,0.7f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Start").c_str(),360,200,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Start").c_str(),335,200,0.7f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 1)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Load").c_str(),369,250,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Load").c_str(),335,250,0.7f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Load").c_str(),369,250,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Load").c_str(),335,250,0.7f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 2)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Options").c_str(),343,300,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Options").c_str(),346,300,0.7f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Options").c_str(),343,300,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Options").c_str(),346,300,0.7f,D3DXCOLOR(255,255,255,255));
		}
	}
	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-021
	// BUG FIX START
	/////////////////////////////////////////////////////////////////
	if(selected == 3)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Credits").c_str(),348,350,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Credits").c_str(),325,350,0.6f,D3DXCOLOR(150,150,0,255)); // Readjusted scale and position here...
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Credits").c_str(),348,350,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Credits").c_str(),325,350,0.6f,D3DXCOLOR(255,255,255,255)); // ...and here.
		}
	}
	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-021
	/////////////////////////////////////////////////////////////////
	if(selected == 4)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Help").c_str(),375,400,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Help").c_str(),385,400,0.7f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Help").c_str(),375,400,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Help").c_str(),385,400,0.7f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 5)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Exit").c_str(),375,450,0.7f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Exit").c_str(),340,450,0.7f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Exit").c_str(),375,450,0.7f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Exit").c_str(),340,450,0.7f,D3DXCOLOR(255,255,255,255));
		}
	}

}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState s_Instance;
	return &s_Instance;
}
