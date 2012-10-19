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
	soundvolume = 100;
	musicvolume = 100;
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	m_pBitmapFont = new CBitmapFont();
	pTM = CSGD_TextureManager::GetInstance();
	jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\options_menu.png"), D3DXCOLOR(255,255,255,255));
	Scroll = pTM->LoadTexture(_T("Assets\\Menus\\scroll.png"));
}

void COptionsMenuState::Exit(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
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
			if(selected != 2)
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
				selected = 2;
			break;
		}
	case INPUT_LEFT:
		{
			if(selected == 0 && soundvolume != 0)
				soundvolume--;
			else if(selected == 1 && musicvolume != 0)
				musicvolume--;
			break;
		}
	case INPUT_RIGHT:
		{
			if(selected == 0 && soundvolume != 100)
				soundvolume++;
			else if(selected == 1 && musicvolume != 100)
				musicvolume++;
			break;
		}
	case INPUT_ACCEPT:
		{
			if(selected == 2)
				CStateStack::GetInstance()->Pop();
			break;
		}
	}
}

void COptionsMenuState::Update(float fElapsedTime)
{

}

void COptionsMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(255,255,255);
	RECT* toprect = new RECT();
	toprect->bottom = 392;
	toprect->top = 198;
	toprect->left = 15;
	toprect->right = 537;
	pTM->Draw(Scroll,15,112,1.44f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 113;
	toprect->top = 0;
	toprect->left = 0;
	toprect->right = 555;
	pTM->Draw(Scroll,0,0,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	delete toprect;
	toprect = nullptr;
	ostringstream oss;
	oss<<"Sound Volume";
	if(selected == 0)
	{
		m_pBitmapFont->Print(oss.str().c_str(),230, 150,0.6f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(oss.str().c_str(),230, 150,0.6f,D3DXCOLOR(255,255,255,255));
	}
	ostringstream moss;
	moss<<"Music Volume";
	if(selected == 1)
	{
		m_pBitmapFont->Print(moss.str().c_str(),330, 200,1.0f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(moss.str().c_str(),330, 200,1.0f,D3DXCOLOR(255,255,255,255));
	}
	ostringstream boss;
	boss<<"Exit";
	if(selected == 2)
	{
		m_pBitmapFont->Print(boss.str().c_str(),345, 250,1.0f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(boss.str().c_str(),345, 250,1.0f,D3DXCOLOR(255,255,255,255));
	}
}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}