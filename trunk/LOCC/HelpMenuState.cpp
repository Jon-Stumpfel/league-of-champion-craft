#include "StdAfx.h"
#include "HelpMenuState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "Game.h"
//CHelpMenuState* CHelpMenuState::s_Instance = nullptr;
const int MENUMAX =3;
CHelpMenuState::CHelpMenuState(void)
{
}


CHelpMenuState::~CHelpMenuState(void)
{
}
			 
void CHelpMenuState::Enter(void)
{
	m_nScrollID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/scroll (2).png"),D3DXCOLOR(255,255,255,255));
	m_nTileHelpID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/TileHelp.png"),D3DXCOLOR(255,255,255,255));
	m_nUnitHelpID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/UnitHelp.png"),D3DXCOLOR(255,255,255,255));
	m_nGameplayHelpID	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/GameplayHelp.png"),D3DXCOLOR(255,255,255,255));
	m_pBitmapfont= new CBitmapFont();
	m_nswitchscreen=1;
}

void CHelpMenuState::Exit(void)
{
	delete m_pBitmapfont;
}

void CHelpMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
			CStateStack::GetInstance()->Pop();
		}
	case INPUT_LEFT:
		{
			m_nswitchscreen--;
				if (m_nswitchscreen==0)
				{
					m_nswitchscreen=MENUMAX;
				}
		}
		break;
	case INPUT_RIGHT:
		{
			m_nswitchscreen++;
				if (m_nswitchscreen>MENUMAX)
				{
					m_nswitchscreen=1;
				}
		}
		break;
	}
}

void CHelpMenuState::Update(float fElapsedTime)
{
}

void CHelpMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0,0,0);
	CSGD_TextureManager::GetInstance()->Draw(m_nScrollID,-50,0,1.0f,0.6f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	//CSGD_TextureManager::GetInstance()->Draw(m_nTileHelpID,0,0,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	
	
	if (m_nswitchscreen==1)// it the tile help screen
	{
	CSGD_TextureManager::GetInstance()->Draw(m_nTileHelpID,0,0,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));

	string TileTitle ("Tile Information");
	int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
	m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
	TileTitle="Tile Type";
	m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));

	string tiletxt ("-Plains-");
	m_pBitmapfont->Print(tiletxt.c_str(),180,150,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Basic Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="costing 1 AP ";
	m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="move across";
	m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Trees-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,240,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Mountains-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,330,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Water-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,420,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	TileTitle="Resource Tile";
	m_pBitmapfont->Print(TileTitle.c_str(),300,120,.4f,D3DCOLOR_XRGB(255,255,255));
	
	tiletxt ="-Mill-";
	m_pBitmapfont->Print(tiletxt.c_str(),400,150,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Mine-";
	m_pBitmapfont->Print(tiletxt.c_str(),400,240,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Farm-";
	m_pBitmapfont->Print(tiletxt.c_str(),400,330,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));


	TileTitle="Tile Status";
	m_pBitmapfont->Print(TileTitle.c_str(),550,120,.4f,D3DCOLOR_XRGB(255,255,255));
	
	tiletxt ="-Frozen-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,150,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Captured-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,240,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Capturing-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,330,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Dead-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,420,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="A Basic Tile";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,170,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="costing 1 AP ";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,185,.3f,D3DCOLOR_XRGB(255,255,255));
	//tiletxt ="move across";
	//m_pBitmapfont->Print(tiletxt.c_str(),180,200,.3f,D3DCOLOR_XRGB(255,255,255));
	}
	else if ( m_nswitchscreen==2)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nUnitHelpID,0,50,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
			
		string TileTitle ("Unit Information");
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		TileTitle="-Basic Units-";
		m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));
	}
	else if ( m_nswitchscreen==3)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nGameplayHelpID,0,0,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
			
		string TileTitle ("Gameplay Information");
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-200;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		TileTitle="-Phases-";
		m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));
	}
}

CHelpMenuState* CHelpMenuState::GetInstance()
{
	static CHelpMenuState s_Instance;
	return &s_Instance;
}
