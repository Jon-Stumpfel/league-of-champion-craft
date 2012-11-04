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
	m_pBitmapfont->Print(tiletxt.c_str(),180,170,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="costing 1 AP ";
	m_pBitmapfont->Print(tiletxt.c_str(),180,180,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="to move across";
	m_pBitmapfont->Print(tiletxt.c_str(),180,190,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Forest-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,240,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Tile giving";
	m_pBitmapfont->Print(tiletxt.c_str(),180,260,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="a dodge chance";
	m_pBitmapfont->Print(tiletxt.c_str(),180,270,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="costing 2 AP ";
	m_pBitmapfont->Print(tiletxt.c_str(),180,280,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="to move across";
	m_pBitmapfont->Print(tiletxt.c_str(),180,290,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Mountains-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,330,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Tile giving";
	m_pBitmapfont->Print(tiletxt.c_str(),180,350,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Archer a range";
	m_pBitmapfont->Print(tiletxt.c_str(),180,360,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Adavantage ";
	m_pBitmapfont->Print(tiletxt.c_str(),180,370,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="costing 3 AP ";
	m_pBitmapfont->Print(tiletxt.c_str(),180,385,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="to move across";
	m_pBitmapfont->Print(tiletxt.c_str(),180,395,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Water-";
	m_pBitmapfont->Print(tiletxt.c_str(),180,420,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Impassiable Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),180,440,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="that can't be";
	m_pBitmapfont->Print(tiletxt.c_str(),180,450,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="moved across";
	m_pBitmapfont->Print(tiletxt.c_str(),180,460,.25f,D3DCOLOR_XRGB(255,255,255));

	TileTitle="Resource Tile";
	m_pBitmapfont->Print(TileTitle.c_str(),300,120,.4f,D3DCOLOR_XRGB(255,255,255));
	
	tiletxt ="-Mill-";
	m_pBitmapfont->Print(tiletxt.c_str(),400,150,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Forest Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),400,160,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="that adds 10 ";
	m_pBitmapfont->Print(tiletxt.c_str(),400,170,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="wood to its ";
	m_pBitmapfont->Print(tiletxt.c_str(),400,180,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="owner's resource";
	m_pBitmapfont->Print(tiletxt.c_str(),400,190,.25f,D3DCOLOR_XRGB(255,255,255));


	tiletxt ="-Mine-";						 
	m_pBitmapfont->Print(tiletxt.c_str(),400,240,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Mountian Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),400,260,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="that adds 10 ";
	m_pBitmapfont->Print(tiletxt.c_str(),400,270,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Metal to its ";
	m_pBitmapfont->Print(tiletxt.c_str(),400,280,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="owner's resource";
	m_pBitmapfont->Print(tiletxt.c_str(),400,290,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Farm-";						
	m_pBitmapfont->Print(tiletxt.c_str(),400,330,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="A Plains Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),400,350,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="that adds 6 ";
	m_pBitmapfont->Print(tiletxt.c_str(),400,360,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="to its owner's";
	m_pBitmapfont->Print(tiletxt.c_str(),400,370,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Population Cap";
	m_pBitmapfont->Print(tiletxt.c_str(),400,380,.25f,D3DCOLOR_XRGB(255,255,255));

	TileTitle="Tile Status";				 
	m_pBitmapfont->Print(TileTitle.c_str(),550,120,.4f,D3DCOLOR_XRGB(255,255,255));
	
	tiletxt ="-Frozen-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,150,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Frozen Tile";
	m_pBitmapfont->Print(tiletxt.c_str(),630,170,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Increase AP cost";
	m_pBitmapfont->Print(tiletxt.c_str(),630,185,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="to move by 1";
	m_pBitmapfont->Print(tiletxt.c_str(),630,200,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Captured-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,240,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="When Tile is ";
	m_pBitmapfont->Print(tiletxt.c_str(),630,260,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Captured it adds ";		
	m_pBitmapfont->Print(tiletxt.c_str(),630,270,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="the benefit to";			
	m_pBitmapfont->Print(tiletxt.c_str(),630,280,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="it's onwer";				
	m_pBitmapfont->Print(tiletxt.c_str(),630,290,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Capturing-";
	m_pBitmapfont->Print(tiletxt.c_str(),630,330,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="When Unit moves";
	m_pBitmapfont->Print(tiletxt.c_str(),630,350,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="onto a resource ";
	m_pBitmapfont->Print(tiletxt.c_str(),630,360,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="tile, they will";
	m_pBitmapfont->Print(tiletxt.c_str(),630,370,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Capture it if they";	
	m_pBitmapfont->Print(tiletxt.c_str(),630,380,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="are not killed or ";	
	m_pBitmapfont->Print(tiletxt.c_str(),630,390,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="move off it";	
	m_pBitmapfont->Print(tiletxt.c_str(),630,400,.25f,D3DCOLOR_XRGB(255,255,255));

	tiletxt ="-Dead-";						 
	m_pBitmapfont->Print(tiletxt.c_str(),630,420,.3f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="Shows a fallen ";
	m_pBitmapfont->Print(tiletxt.c_str(),630,440,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="unit that can";					 
	m_pBitmapfont->Print(tiletxt.c_str(),630,450,.25f,D3DCOLOR_XRGB(255,255,255));
	tiletxt ="be Reanimated";						  
	m_pBitmapfont->Print(tiletxt.c_str(),630,460,.25f,D3DCOLOR_XRGB(255,255,255));
	}
	else if ( m_nswitchscreen==2)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nUnitHelpID,0,50,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
			
		string TileTitle ("Unit Information");
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		TileTitle="-Basic Units-";
		m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));

		string tiletxt ("-Champion-");
		m_pBitmapfont->Print(tiletxt.c_str(),125,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Commanding Unit, If he dies, ";
		m_pBitmapfont->Print(tiletxt.c_str(),260,180,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="the game is over";
		m_pBitmapfont->Print(tiletxt.c_str(),260,195,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Special ability: Spell Tree";
		m_pBitmapfont->Print(tiletxt.c_str(),265,210,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Unit has access to ";
		m_pBitmapfont->Print(tiletxt.c_str(),265,225,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="customizible Spell trees";
		m_pBitmapfont->Print(tiletxt.c_str(),265,240,.25f,D3DCOLOR_XRGB(255,255,255));

		tiletxt ="-Calavry-";
		m_pBitmapfont->Print(tiletxt.c_str(),125,270,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Advanced melee Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),260,285,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Special ability: Charge";
		m_pBitmapfont->Print(tiletxt.c_str(),265,300,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Charges forward damging  ";
		m_pBitmapfont->Print(tiletxt.c_str(),265,315,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="units in one cardial Direction ";
		m_pBitmapfont->Print(tiletxt.c_str(),265,330,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="-LAST CHARGED MUST BE OPEN";
		m_pBitmapfont->Print(tiletxt.c_str(),265,345,.24f,D3DCOLOR_XRGB(255,255,255));

		tiletxt ="-Archer-";
		m_pBitmapfont->Print(tiletxt.c_str(),125,370,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Ranged Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),260,385,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Special ability: Volley";
		m_pBitmapfont->Print(tiletxt.c_str(),265,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Fires mulitple Arrows at ";
		m_pBitmapfont->Print(tiletxt.c_str(),265,415,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="a target unit in range";
		m_pBitmapfont->Print(tiletxt.c_str(),265,430,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="-CANNOT MOVE BEFORE ATTACK";
		m_pBitmapfont->Print(tiletxt.c_str(),265,445,.24f,D3DCOLOR_XRGB(255,255,255));

		tiletxt ="-Swordsman-";
		m_pBitmapfont->Print(tiletxt.c_str(),125,460,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Melee Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),260,480,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Special ability: Stand Ground";
		m_pBitmapfont->Print(tiletxt.c_str(),265,500,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Braces for impact";
		m_pBitmapfont->Print(tiletxt.c_str(),265,515,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="reducing dmg taken next turn";
		m_pBitmapfont->Print(tiletxt.c_str(),265,530,.25f,D3DCOLOR_XRGB(255,255,255));
		
		tiletxt ="-Castle Base-";
		m_pBitmapfont->Print(tiletxt.c_str(),550,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Support Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),610,190,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Special ability: Spawn Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),610,195,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="The Base can Spawn ";
		m_pBitmapfont->Print(tiletxt.c_str(),610,210,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="other Units";
		m_pBitmapfont->Print(tiletxt.c_str(),610,225,.25f,D3DCOLOR_XRGB(255,255,255));
		
		tiletxt ="-Ice Block-";
		m_pBitmapfont->Print(tiletxt.c_str(),540,260,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Netural Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),580,285,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="It's name says it ";		
		m_pBitmapfont->Print(tiletxt.c_str(),590,300,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="all a Block That";		
		m_pBitmapfont->Print(tiletxt.c_str(),590,315,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Blocks Most Movement";	 
		m_pBitmapfont->Print(tiletxt.c_str(),590,330,.25f,D3DCOLOR_XRGB(255,255,255));

		tiletxt ="-Skeleton-";
		m_pBitmapfont->Print(tiletxt.c_str(),540,370,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Dead Melee Unit";
		m_pBitmapfont->Print(tiletxt.c_str(),570,385,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="Poor reainmated  ";		
		m_pBitmapfont->Print(tiletxt.c_str(),590,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="soul That fights";		
		m_pBitmapfont->Print(tiletxt.c_str(),590,415,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="for his summoner";	 
		m_pBitmapfont->Print(tiletxt.c_str(),590,430,.25f,D3DCOLOR_XRGB(255,255,255));
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
