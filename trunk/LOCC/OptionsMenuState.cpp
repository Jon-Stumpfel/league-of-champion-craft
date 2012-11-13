#include "StdAfx.h"
#include "OptionsMenuState.h"
#include "StateStack.h"
#include "StringTable.h"
#include "AbilityManager.h"
#include "SoundManager.h"
#include "GraphicsManager.h"
COptionsMenuState::COptionsMenuState(void)
{
}
COptionsMenuState::~COptionsMenuState(void)
{
}
void COptionsMenuState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_pBitmapFont = new CBitmapFont();
	pTM = CSGD_TextureManager::GetInstance();
	jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\options_menu.png"), D3DXCOLOR(255,255,255,255));



	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-002
	// Reference Bug # BB-003
	// Reference Bug # BB-005
	// BUG FIX START
	/////////////////////////////////////////////////////////////////

	// Just updated this to use appdata saving path instead of standard relative
	// to resolve issues with administrator rights to save files

	wchar_t path[MAX_PATH];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_APPDATA, 0, SHGFP_TYPE_CURRENT, path);

	std::wstring pathtowrite(path, path+ wcslen(path));
	
	pathtowrite += L"\\LeagueOfChampionCraft";
	CreateDirectory(pathtowrite.c_str(), 0);

	std::wostringstream woss;
	woss << "\\Options.xml";
	pathtowrite += woss.str();
	std::string stringpath(pathtowrite.begin(), pathtowrite.end());

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  
	// Reference # BB-002
	// Reference # BB-003
	// Reference # BB-005

	/////////////////////////////////////////////////////////////////


	TiXmlDocument doc;
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
		soundvolume = musicvolume = 100;;
		windowed = true;
		IsModern = true;
	}
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume*0.01f));
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume*0.01f));
	
}
void COptionsMenuState::Exit(void)
{
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );  
	doc.LinkEndChild( decl );  

	TiXmlElement * root = new TiXmlElement( "Options" );  
	doc.LinkEndChild( root );  
	TiXmlElement* Options = new TiXmlElement("Option");
	root->LinkEndChild(Options);
	Options->SetAttribute("SoundVolume", soundvolume);
	Options->SetAttribute("MusicVolume", musicvolume);
	if(windowed == false)
		Options->SetAttribute("Fullscreen", 0);
	else
		Options->SetAttribute("Fullscreen", 1);
	if(IsModern == false)
		Options->SetAttribute("IsModern", 0);
	else
		Options->SetAttribute("IsModern", 1);

	wchar_t path[MAX_PATH];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_APPDATA, 0, SHGFP_TYPE_CURRENT, path);

	std::wstring pathtowrite(path, path+ wcslen(path));
	
	pathtowrite += L"\\LeagueOfChampionCraft";
	CreateDirectory(pathtowrite.c_str(), 0);

	std::wostringstream woss;
	woss << "\\Options.xml";
	pathtowrite += woss.str();
	std::string stringpath(pathtowrite.begin(), pathtowrite.end());

	doc.SaveFile(stringpath.c_str());
	int temp = NUMSPELLS;
	for(int i = 0; i < temp; i++)
	{
		if( CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i)) != nullptr )
			CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString(CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->GetDescription(), true));
	}
}
void COptionsMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			CStateStack::GetInstance()->Pop();
		}
		break;
	case INPUT_DOWN:
		{
			if(selected != 4)
				selected++;
			else
				selected = 0;
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_UP:
		{
			if(selected !=0)
				selected--;
			else
				selected = 4;
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_LEFT:
		{
			if(selected == 0 && soundvolume > 0)
			{
				soundvolume-=5;
				float temp = soundvolume*0.01f;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(temp);
			}
			else if(selected == 1 && musicvolume > 0)
			{
				musicvolume-=5;
				float temp = musicvolume*0.01f;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(temp);
			}
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_RIGHT:
		{
			if(selected == 0 && soundvolume < 100)
			{
				soundvolume+=5;
				float temp = soundvolume*0.01f;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(temp);
			}
			else if(selected == 1 && musicvolume < 100)
			{
				musicvolume+=5;
				float temp = musicvolume*0.01f;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(temp);
			}
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_ACCEPT:
		{
			if(selected == 2)
			{
				if(windowed == false)
					windowed = true;
				else
					windowed = false;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				CGame::GetInstance()->SetIsWindowed(windowed);
			}
			else if(selected == 3)
			{
				if(IsModern == false)
					IsModern = true;
				else
					IsModern = false;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				StringTable::GetInstance()->SetLanguage(IsModern);
			}
			else if(selected == 4)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				CStateStack::GetInstance()->Pop();
			}
			break;
		}
	}
}
void COptionsMenuState::Update(float fElapsedTime)
{
}
void COptionsMenuState::Render(void)
{
	RECT* toprect = new RECT();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 105, 15, 1.2f, 1.1f);

	toprect->bottom = 77;
	toprect->top = 56;
	toprect->left = 152;
	toprect->right = 402;
	pTM->Draw(jcs_nImageID,275 + 20,170 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,275 + 20,270 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 89;
	toprect->bottom = 108;
	toprect->left = 184;
	toprect->right = 188;
	pTM->Draw(jcs_nImageID,303+int(1.86f*soundvolume) + 20,170 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,303+int(1.86f*musicvolume) + 20,270 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 345;
	toprect->left = 254;
	toprect->bottom = 386;
	toprect->right = 295;
	pTM->Draw(jcs_nImageID,480 + 20,305 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,480 + 20,360 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	if(windowed == false)
	{
		toprect->top = 336;
		toprect->left = 324;
		toprect->bottom = 385;
		toprect->right = 377;
		pTM->Draw(jcs_nImageID,480 + 20,305 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	}
	else
	{

	}
	if(IsModern)
	{
		toprect->top = 336;
		toprect->left = 324;
		toprect->bottom = 385;
		toprect->right = 377;
		pTM->Draw(jcs_nImageID,480 + 20,360 + 25,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	}
	else
	{

	}
	delete toprect;
	toprect = nullptr;
	if(selected == 0)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275 + 20,110 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275 + 20,110 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275 + 20,110 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275 + 20,110 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 1)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278 + 20,210 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278 + 20,210 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278 + 20,210 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278 + 20,210 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 2)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),278 + 20,310 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),298 + 20,310 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),278 + 20,310 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),298 + 20,310 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 3)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),178 + 20,365 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),198 + 20,365 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),178 + 20,365 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),198 + 20,365 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 4)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350 + 20,440 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350 + 20,440 + 25,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350 + 20,440 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350 + 20,440 + 25,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
}
COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}