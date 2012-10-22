#include "StdAfx.h"
#include "OptionsMenuState.h"
#include "StateStack.h"

//COptionsMenuState* COptionsMenuState::s_Instance = nullptr;

COptionsMenuState::COptionsMenuState(void)
{
}


COptionsMenuState::~COptionsMenuState(void)
{
}

void COptionsMenuState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	m_pBitmapFont = new CBitmapFont();
	pTM = CSGD_TextureManager::GetInstance();
	jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\options_menu.png"), D3DXCOLOR(255,255,255,255));
	Scroll = pTM->LoadTexture(_T("Assets\\Menus\\scroll.png"), D3DXCOLOR(255,255,255,255));
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
		Option = Option->NextSiblingElement("Option");
	}
}

void COptionsMenuState::Exit(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
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
	doc.SaveFile("Assets\\Menus\\Options.xml");
}

void COptionsMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
		CStateStack::GetInstance()->Pop();
		}
		break;
	case INPUT_DOWN:
		{
			if(selected != 3)
				selected++;
			else
				selected = 0;
			break;
		}
	case INPUT_UP:
		{
			if(selected !=0)
				selected--;
			else
				selected = 3;
			break;
		}
	case INPUT_LEFT:
		{
			if(selected == 0 && soundvolume != 0)
			{
				soundvolume-=5;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume/100));
			}
			else if(selected == 1 && musicvolume != 0)
			{
				musicvolume-=5;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume/100));
			}
			break;
		}
	case INPUT_RIGHT:
		{
			if(selected == 0 && soundvolume != 100)
			{
				soundvolume+=5;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume/100));
			}
			else if(selected == 1 && musicvolume != 100)
			{
				musicvolume+=5;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume/100));
			}
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
				CGame::GetInstance()->SetIsWindowed(windowed);
			}
			else if(selected == 3)
				CStateStack::GetInstance()->Pop();
			break;
		}
	}
}

void COptionsMenuState::Update(float fElapsedTime)
{
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume/100));
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume/100));
}

void COptionsMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(100,200,100);
	RECT* toprect = new RECT();
	toprect->bottom = 392;
	toprect->top = 198;
	toprect->left = 15;
	toprect->right = 537;
	pTM->Draw(Scroll,25,100,1.44f,2.3f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 113;
	toprect->top = 0;
	toprect->left = 0;
	toprect->right = 555;
	pTM->Draw(Scroll,0,0,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 584;
	toprect->top = 472;
	toprect->left = 2;
	toprect->right = 557;
	pTM->Draw(Scroll,0,487,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 77;
	toprect->top = 56;
	toprect->left = 152;
	toprect->right = 402;
	pTM->Draw(jcs_nImageID,275,170,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,275,270,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 89;
	toprect->bottom = 108;
	toprect->left = 184;
	toprect->right = 188;
	pTM->Draw(jcs_nImageID,303+int(1.86f*soundvolume),170,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,303+int(1.86f*musicvolume),270,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 345;
	toprect->left = 254;
	toprect->bottom = 386;
	toprect->right = 295;
	pTM->Draw(jcs_nImageID,370,360,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	if(windowed == false)
	{
		toprect->top = 336;
		toprect->left = 324;
		toprect->bottom = 385;
		toprect->right = 377;
	}
	pTM->Draw(jcs_nImageID,370,360,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	delete toprect;
	toprect = nullptr;
	ostringstream oss;
	oss<<"Sound Volume";
	if(selected == 0)
		m_pBitmapFont->Print(oss.str().c_str(),275,110,0.6f,D3DXCOLOR(150,150,0,255));
	else
		m_pBitmapFont->Print(oss.str().c_str(),275,110,0.6f,D3DXCOLOR(255,255,255,255));
	ostringstream moss;
	moss<<"Music Volume";
	if(selected == 1)
		m_pBitmapFont->Print(moss.str().c_str(),278,210,0.6f,D3DXCOLOR(150,150,0,255));
	else
		m_pBitmapFont->Print(moss.str().c_str(),278,210,0.6f,D3DXCOLOR(255,255,255,255));
	ostringstream sauce;
	sauce<<"Fullscreen";
	if(selected == 2)
		m_pBitmapFont->Print(sauce.str().c_str(),295,310,0.6f,D3DXCOLOR(150,150,0,255));
	else
		m_pBitmapFont->Print(sauce.str().c_str(),295,310,0.6f,D3DXCOLOR(255,255,255,255));
	ostringstream boss;
	boss<<"Back";
	if(selected == 3)
		m_pBitmapFont->Print(boss.str().c_str(),350,440,0.6f,D3DXCOLOR(150,150,0,255));
	else
		m_pBitmapFont->Print(boss.str().c_str(),350,440,0.6f,D3DXCOLOR(255,255,255,255));
}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}