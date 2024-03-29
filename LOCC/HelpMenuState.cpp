#include "StdAfx.h"
#include "HelpMenuState.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "Game.h"
#include "SoundManager.h"
#include "StringTable.h"
//CHelpMenuState* CHelpMenuState::s_Instance = nullptr;
const int MENUMAX =6;
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
	m_nArcadeHelpID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/ArcadeHelp.png"),D3DXCOLOR(0,0,0,0));
	m_nKeyBoardHelpID	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/KeyboardHelp.png"),D3DXCOLOR(255,255,255,255));
	m_nXboxHelpID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/XboxHelp.png"),D3DXCOLOR(0,0,0,0));
	m_nArrowID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Menus/Arrow.png"),D3DXCOLOR(0,0,0,0));
	m_pBitmapfont= new CBitmapFont();
	m_nswitchscreen=1;
}

void CHelpMenuState::Exit(void)
{
	delete m_pBitmapfont;
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nScrollID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nTileHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nUnitHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nGameplayHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nArcadeHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nKeyBoardHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nXboxHelpID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nArrowID);
}

void CHelpMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

			CStateStack::GetInstance()->Pop();
		}
		break;
	case INPUT_LEFT:
		{
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("flip")), false, false);
			m_nswitchscreen--;
				if (m_nswitchscreen==0)
				{
					m_nswitchscreen=MENUMAX;
				}
		}
		break;
	case INPUT_RIGHT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("flip")), false, false);
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
	CSGD_TextureManager::GetInstance()->Draw(m_nArrowID,100,50,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nArrowID,780,50,-1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));

	string TileTitle (StringTable::GetInstance()->GetString("Tile Information"));
	m_pBitmapfont->Print(StringTable::GetInstance()->GetString("Press cancel to return...").c_str(), 550, 560, 0.28f, D3DCOLOR_XRGB(255, 255, 255), 250);
	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-008
	// BUG FIX START
	/////////////////////////////////////////////////////////////////
	// I had to readjust almost every line for every screen, so I think it's easier for me to type up a summary here:
	// I repositioned a lot of strings, making the words that have overlapped or gone off-screen go to a new line or a new position.
	if (m_nswitchscreen==1)// It's the tile help screen
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nTileHelpID,0,0,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
		if(StringTable::GetInstance()->GetIsItModern())
		{
			string TileTitle (StringTable::GetInstance()->GetString("Tile Information"));
			int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
			m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
			TileTitle=StringTable::GetInstance()->GetString("Tile Type");
			m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));

			string tiletxt (StringTable::GetInstance()->GetString("-Plains-"));
			m_pBitmapfont->Print(tiletxt.c_str(),180,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Basic Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),180,170,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("costing 1 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,180,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,190,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Forest-");
			m_pBitmapfont->Print(tiletxt.c_str(),180,240,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Tile giving");
			m_pBitmapfont->Print(tiletxt.c_str(),180,260,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("a dodge chance");
			m_pBitmapfont->Print(tiletxt.c_str(),180,272,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("costing 2 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,285,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,295,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Mountains-");
			m_pBitmapfont->Print(tiletxt.c_str(),180,330,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Tile giving");
			m_pBitmapfont->Print(tiletxt.c_str(),180,350,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Archer a range");
			m_pBitmapfont->Print(tiletxt.c_str(),180,360,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Adavantage ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,370,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("costing 3 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,385,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,395,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Water-");
			m_pBitmapfont->Print(tiletxt.c_str(),180,420,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("An Impassable Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),180,440,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that can't be");
			m_pBitmapfont->Print(tiletxt.c_str(),180,450,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("moved across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,460,.25f,D3DCOLOR_XRGB(255,255,255));

			TileTitle=StringTable::GetInstance()->GetString("Resource Tile");
			m_pBitmapfont->Print(TileTitle.c_str(),300,120,.4f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Mill-");
			m_pBitmapfont->Print(tiletxt.c_str(),400,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Forest Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,160,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 10 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,170,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("wood to its ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,180,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("owner's resource");
			m_pBitmapfont->Print(tiletxt.c_str(),400,190,.25f,D3DCOLOR_XRGB(255,255,255));


			tiletxt =StringTable::GetInstance()->GetString("-Mine-");						 
			m_pBitmapfont->Print(tiletxt.c_str(),400,240,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Mountian Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,260,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 10 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,270,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Metal to its ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,280,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("owner's resource");
			m_pBitmapfont->Print(tiletxt.c_str(),400,290,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Farm-");						
			m_pBitmapfont->Print(tiletxt.c_str(),400,330,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Plains Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,350,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 6 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,360,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to its owner's");
			m_pBitmapfont->Print(tiletxt.c_str(),400,370,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Population Cap");
			m_pBitmapfont->Print(tiletxt.c_str(),400,380,.25f,D3DCOLOR_XRGB(255,255,255));

			TileTitle=StringTable::GetInstance()->GetString("Tile Status");				 
			m_pBitmapfont->Print(TileTitle.c_str(),550,120,.4f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Frozen-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Frozen Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),630,170,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Increases AP cost");
			m_pBitmapfont->Print(tiletxt.c_str(),630,185,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move by 1");
			m_pBitmapfont->Print(tiletxt.c_str(),630,200,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Captured-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,240,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("When Tile is Captured it adds the benefit to it's owner");
			m_pBitmapfont->Print(tiletxt.c_str(),630,260,.25f,D3DCOLOR_XRGB(255,255,255),150);
			
			tiletxt =StringTable::GetInstance()->GetString("-Capturing-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,330,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("When Unit moves onto a resource tile, they will Capture it if they are not killed or move off it");
			m_pBitmapfont->Print(tiletxt.c_str(),630,350,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Dead-");						 
			m_pBitmapfont->Print(tiletxt.c_str(),630,420,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Shows a fallen ");
			m_pBitmapfont->Print(tiletxt.c_str(),630,440,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("unit that can");					 
			m_pBitmapfont->Print(tiletxt.c_str(),630,450,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("be Reanimated");						  
			m_pBitmapfont->Print(tiletxt.c_str(),630,460,.25f,D3DCOLOR_XRGB(255,255,255));
		}
		else
		{
			string TileTitle (StringTable::GetInstance()->GetString("Tile Information"));
			int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
			m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
			TileTitle=StringTable::GetInstance()->GetString("Tile Type");
			if(StringTable::GetInstance()->GetIsItModern())
				m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));
			else
				m_pBitmapfont->Print(TileTitle.c_str(),100,90,.4f,D3DCOLOR_XRGB(255,255,255));
			string tiletxt (StringTable::GetInstance()->GetString("-Plains-"));
			m_pBitmapfont->Print(tiletxt.c_str(),180,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Basic Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),180,170,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("costing 1 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,190,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,200,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Forest-");
			m_pBitmapfont->Print(tiletxt.c_str(),180,229,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Tile giving");
			m_pBitmapfont->Print(tiletxt.c_str(),180,242,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("a dodge chance");
			m_pBitmapfont->Print(tiletxt.c_str(),180,266,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("costing 2 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,287,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,299,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Mountains-");
			m_pBitmapfont->Print(tiletxt.c_str(),185,327,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Tile giving");
			m_pBitmapfont->Print(tiletxt.c_str(),180,339,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("Archer a range");
			m_pBitmapfont->Print(tiletxt.c_str(),180,364,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("Adavantage ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,385,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("costing 3 AP ");
			m_pBitmapfont->Print(tiletxt.c_str(),180,395,.25f,D3DCOLOR_XRGB(255,255,255),150);
			tiletxt =StringTable::GetInstance()->GetString("to move across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,405,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Water-");
			m_pBitmapfont->Print(tiletxt.c_str(),180,428,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("An Impassable Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),180,445,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that can't be");
			m_pBitmapfont->Print(tiletxt.c_str(),180,455,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("moved across");
			m_pBitmapfont->Print(tiletxt.c_str(),180,465,.25f,D3DCOLOR_XRGB(255,255,255));

			TileTitle=StringTable::GetInstance()->GetString("Resource Tile");
			m_pBitmapfont->Print(TileTitle.c_str(),300,120,.4f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Mill-");
			m_pBitmapfont->Print(tiletxt.c_str(),400,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Forest Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,160,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 10 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,170,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("wood to its ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,180,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("owner's resource");
			m_pBitmapfont->Print(tiletxt.c_str(),400,190,.25f,D3DCOLOR_XRGB(255,255,255));


			tiletxt =StringTable::GetInstance()->GetString("-Mine-");						 
			m_pBitmapfont->Print(tiletxt.c_str(),400,240,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Mountian Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,260,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 10 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,270,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Metal to its ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,280,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("owner's resource");
			m_pBitmapfont->Print(tiletxt.c_str(),400,290,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Farm-");						
			m_pBitmapfont->Print(tiletxt.c_str(),400,330,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("A Plains Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),400,350,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("that adds 6 ");
			m_pBitmapfont->Print(tiletxt.c_str(),400,360,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to its owner's");
			m_pBitmapfont->Print(tiletxt.c_str(),400,370,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Population Cap");
			m_pBitmapfont->Print(tiletxt.c_str(),400,380,.25f,D3DCOLOR_XRGB(255,255,255));

			TileTitle=StringTable::GetInstance()->GetString("Tile Status");				 
			m_pBitmapfont->Print(TileTitle.c_str(),550,120,.4f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Frozen-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,150,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Frozen Tile");
			m_pBitmapfont->Print(tiletxt.c_str(),630,170,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Increases AP cost");
			m_pBitmapfont->Print(tiletxt.c_str(),630,185,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("to move by 1");
			m_pBitmapfont->Print(tiletxt.c_str(),630,200,.25f,D3DCOLOR_XRGB(255,255,255));

			tiletxt =StringTable::GetInstance()->GetString("-Captured-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,225,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("When Tile is Captured it adds the benefit to it's owner");
			m_pBitmapfont->Print(tiletxt.c_str(),630,245,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Capturing-");
			m_pBitmapfont->Print(tiletxt.c_str(),630,300,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("When Unit moves onto a resource tile, they will Capture it if they are not killed or move off it");
			m_pBitmapfont->Print(tiletxt.c_str(),630,315,.25f,D3DCOLOR_XRGB(255,255,255),150);

			tiletxt =StringTable::GetInstance()->GetString("-Dead-");						 
			m_pBitmapfont->Print(tiletxt.c_str(),630,420,.3f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("Shows a fallen ");
			m_pBitmapfont->Print(tiletxt.c_str(),630,440,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("unit that can");					 
			m_pBitmapfont->Print(tiletxt.c_str(),630,450,.25f,D3DCOLOR_XRGB(255,255,255));
			tiletxt =StringTable::GetInstance()->GetString("be Reanimated");						  
			m_pBitmapfont->Print(tiletxt.c_str(),630,460,.25f,D3DCOLOR_XRGB(255,255,255));
		}
	}
	else if ( m_nswitchscreen==2) // It's the Unit info help screen
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nUnitHelpID,0,50,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
			
		string TileTitle (StringTable::GetInstance()->GetString("Unit Information"));
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		TileTitle=StringTable::GetInstance()->GetString("-Basic Units-");
		m_pBitmapfont->Print(TileTitle.c_str(),100,120,.4f,D3DCOLOR_XRGB(255,255,255));

		string tiletxt (StringTable::GetInstance()->GetString("-Champion-"));
		m_pBitmapfont->Print(tiletxt.c_str(),125,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Commanding Unit. If he dies, ");
		m_pBitmapfont->Print(tiletxt.c_str(),260,170,.25f,D3DCOLOR_XRGB(255,255,255), 200);
		tiletxt =StringTable::GetInstance()->GetString("the game is over");
		m_pBitmapfont->Print(tiletxt.c_str(),260,195,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Special ability: Spell Tree");
		m_pBitmapfont->Print(tiletxt.c_str(),260,210,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Unit has access to ");
		m_pBitmapfont->Print(tiletxt.c_str(),260,225,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("customizible Spell trees");
		m_pBitmapfont->Print(tiletxt.c_str(),260,240,.25f,D3DCOLOR_XRGB(255,255,255));

		tiletxt =StringTable::GetInstance()->GetString("-Calvary-");
		m_pBitmapfont->Print(tiletxt.c_str(),125,270,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Advanced melee Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),260,285,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Special ability: Charge");
		m_pBitmapfont->Print(tiletxt.c_str(),265,300,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Charges forward, damging  ");
		m_pBitmapfont->Print(tiletxt.c_str(),265,315,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("units in one cardinal Direction ");
		m_pBitmapfont->Print(tiletxt.c_str(),265,330,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("-TILE CHARGED TO MUST BE OPEN");
		m_pBitmapfont->Print(tiletxt.c_str(),265,345,.23f,D3DCOLOR_XRGB(255,255,255));

		tiletxt =StringTable::GetInstance()->GetString("-Archer-");
		m_pBitmapfont->Print(tiletxt.c_str(),125,370,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Ranged Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),260,370,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Special ability: Volley");
		m_pBitmapfont->Print(tiletxt.c_str(),265,385,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Fires mulitple Arrows at ");
		m_pBitmapfont->Print(tiletxt.c_str(),265,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("a target unit in range");
		m_pBitmapfont->Print(tiletxt.c_str(),265,415,.25f,D3DCOLOR_XRGB(255,255,255), 200);
		tiletxt =StringTable::GetInstance()->GetString("-CANNOT MOVE BEFORE ATTACK");
		m_pBitmapfont->Print(tiletxt.c_str(),265,440,.24f,D3DCOLOR_XRGB(255,255,255), 200);

		tiletxt =StringTable::GetInstance()->GetString("-Swordsman-");
		m_pBitmapfont->Print(tiletxt.c_str(),125,460,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Melee Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),260,480,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Special ability: Stand Ground");
		m_pBitmapfont->Print(tiletxt.c_str(),265,500,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Braces for impact");
		m_pBitmapfont->Print(tiletxt.c_str(),265,515,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("reducing dmg taken next turn");
		m_pBitmapfont->Print(tiletxt.c_str(),265,530,.25f,D3DCOLOR_XRGB(255,255,255));
		
		tiletxt =StringTable::GetInstance()->GetString("-Castle Base-");
		m_pBitmapfont->Print(tiletxt.c_str(),550,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Support Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),610,170,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Special ability: Spawn Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),610,185,.25f,D3DCOLOR_XRGB(255,255,255),150);
		tiletxt =StringTable::GetInstance()->GetString("The Base can Spawn ");
		m_pBitmapfont->Print(tiletxt.c_str(),610,210,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("other Units");
		m_pBitmapfont->Print(tiletxt.c_str(),610,225,.25f,D3DCOLOR_XRGB(255,255,255));
		
		tiletxt =StringTable::GetInstance()->GetString("-Ice Block-");
		m_pBitmapfont->Print(tiletxt.c_str(),540,260,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Neutral Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),580,285,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("It's name says it ");
		m_pBitmapfont->Print(tiletxt.c_str(),590,300,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("all a Block that");
		m_pBitmapfont->Print(tiletxt.c_str(),590,315,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("blocks most movement");
		m_pBitmapfont->Print(tiletxt.c_str(),590,330,.25f,D3DCOLOR_XRGB(255,255,255));

		tiletxt =StringTable::GetInstance()->GetString("-Skeleton-");
		m_pBitmapfont->Print(tiletxt.c_str(),540,370,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Dead Melee Unit");
		m_pBitmapfont->Print(tiletxt.c_str(),570,385,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Poor reainmated  ");
		m_pBitmapfont->Print(tiletxt.c_str(),590,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("soul that fights");
		m_pBitmapfont->Print(tiletxt.c_str(),590,415,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("for his summoner");
		m_pBitmapfont->Print(tiletxt.c_str(),590,430,.25f,D3DCOLOR_XRGB(255,255,255));
	}
	else if ( m_nswitchscreen==3) // It's the Gamplay help screen				 
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nGameplayHelpID,0,0,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
			
		string TileTitle (StringTable::GetInstance()->GetString("Gameplay Information"));
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-250;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		TileTitle=StringTable::GetInstance()->GetString("-Phases-");
		m_pBitmapfont->Print(TileTitle.c_str(),120,120,.4f,D3DCOLOR_XRGB(255,255,255));

		string tiletxt (StringTable::GetInstance()->GetString("-Movement-"));
		m_pBitmapfont->Print(tiletxt.c_str(),125,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("During movement, players move");
		m_pBitmapfont->Print(tiletxt.c_str(),200,170,.25f,D3DCOLOR_XRGB(255,255,255),250);
		tiletxt =StringTable::GetInstance()->GetString("their champions and other units, ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,190,.25f,D3DCOLOR_XRGB(255,255,255),250);
		tiletxt =StringTable::GetInstance()->GetString("as well as cast any champion ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,210,.25f,D3DCOLOR_XRGB(255,255,255),250);
		tiletxt =StringTable::GetInstance()->GetString("spells that can be cast during ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,235,.25f,D3DCOLOR_XRGB(255,255,255),250);
		tiletxt =StringTable::GetInstance()->GetString("the movement phase ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,260,.25f,D3DCOLOR_XRGB(255,255,255),250);

		tiletxt =StringTable::GetInstance()->GetString("-Attack-");
		m_pBitmapfont->Print(tiletxt.c_str(),125,340,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("During the attack phase, ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,360,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Champions and other units "); 
		m_pBitmapfont->Print(tiletxt.c_str(),200,380,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("can do basic attacks");
		m_pBitmapfont->Print(tiletxt.c_str(),200,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("within range, or perform ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,420,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("their special Abilities ");
		m_pBitmapfont->Print(tiletxt.c_str(),200,440,.25f,D3DCOLOR_XRGB(255,255,255));

		tiletxt =StringTable::GetInstance()->GetString("-Action Points-");
		m_pBitmapfont->Print(tiletxt.c_str(),500,150,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Action Point, or AP,");
		m_pBitmapfont->Print(tiletxt.c_str(),550,170,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("is your central focus");
		m_pBitmapfont->Print(tiletxt.c_str(),550,190,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("for how to move and ");
		m_pBitmapfont->Print(tiletxt.c_str(),550,210,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("what to attack. ");
		m_pBitmapfont->Print(tiletxt.c_str(),550,230,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Every action costs AP");
		m_pBitmapfont->Print(tiletxt.c_str(),550,250,.25f,D3DCOLOR_XRGB(255,255,255));

		
		tiletxt =StringTable::GetInstance()->GetString("-Losing/Winning the Game-");
		m_pBitmapfont->Print(tiletxt.c_str(),470,340,.3f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Player can Win or");		   
		m_pBitmapfont->Print(tiletxt.c_str(),610,360,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("lose the game by");		   
		m_pBitmapfont->Print(tiletxt.c_str(),610,377,.25f,D3DCOLOR_XRGB(255,255,255),150);
		tiletxt =StringTable::GetInstance()->GetString("Defeating the ");	   
		m_pBitmapfont->Print(tiletxt.c_str(),610,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("enemy Champion or ");			   
		m_pBitmapfont->Print(tiletxt.c_str(),610,420,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Destroying the"); 
		m_pBitmapfont->Print(tiletxt.c_str(),610,440,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("enemy base ");
		m_pBitmapfont->Print(tiletxt.c_str(),610,460,.3f,D3DCOLOR_XRGB(255,255,255));
	}
	else if (m_nswitchscreen==4) // It's the Xbox Controller help screen 
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nXboxHelpID,200,70,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
		
		string TileTitle (StringTable::GetInstance()->GetString("Xbox Controls"));
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));
		
		string tiletxt (StringTable::GetInstance()->GetString("Accept"));
		m_pBitmapfont->Print(tiletxt.c_str(),620,360,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cancel/Deselect");
		m_pBitmapfont->Print(tiletxt.c_str(),620,305,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("End Phase/Turn");
		m_pBitmapfont->Print(tiletxt.c_str(),360,430,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Pause Menu");
		m_pBitmapfont->Print(tiletxt.c_str(),200,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Champions Only:");
		m_pBitmapfont->Print(tiletxt.c_str(),580,230,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Get/Change spell");
		m_pBitmapfont->Print(tiletxt.c_str(),580,245,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move Cursor");
		m_pBitmapfont->Print(tiletxt.c_str(),170,300,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move camera ");
		m_pBitmapfont->Print(tiletxt.c_str(),520,440,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cycle through Units ");
		m_pBitmapfont->Print(tiletxt.c_str(),350,200,.25f,D3DCOLOR_XRGB(255,255,255));

	}

	else if (m_nswitchscreen==5) // It's the Arcade help screen 
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nArcadeHelpID,200,70,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
		string TileTitle (StringTable::GetInstance()->GetString("Arcade Controls"));
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-150;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));

		string tiletxt (StringTable::GetInstance()->GetString("Accept"));
		m_pBitmapfont->Print(tiletxt.c_str(),195,360,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cancel/Deselect");
		m_pBitmapfont->Print(tiletxt.c_str(),300,190,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("End Phase/Turn");
		m_pBitmapfont->Print(tiletxt.c_str(),170,420,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Pause Menu");
		m_pBitmapfont->Print(tiletxt.c_str(),200,220,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Champions Only: Get/Change spell");
		m_pBitmapfont->Print(tiletxt.c_str(),390,220,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move Cursor");
		m_pBitmapfont->Print(tiletxt.c_str(),170,275,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move camera ");
		m_pBitmapfont->Print(tiletxt.c_str(),400,430,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cycle through Units ");
		m_pBitmapfont->Print(tiletxt.c_str(),250,465,.25f,D3DCOLOR_XRGB(255,255,255));
	}
	
	else if (m_nswitchscreen==6) // It's the keyboard help screen 
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nKeyBoardHelpID,200,70,1.0f,1.0f,0,0,0,0,D3DXCOLOR(255,255,255,255));
		string TileTitle (StringTable::GetInstance()->GetString("Keyboard Controls"));
		int widthstart=CGame::GetInstance()->GetWindowWidth()/2-200;
		m_pBitmapfont->Print(TileTitle.c_str(),widthstart,50,.9f,D3DCOLOR_XRGB(255,255,255));

		string tiletxt (StringTable::GetInstance()->GetString("Accept"));
		m_pBitmapfont->Print(tiletxt.c_str(),500,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cancel/Deselect");
		m_pBitmapfont->Print(tiletxt.c_str(),150,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("End Phase/Turn");
		m_pBitmapfont->Print(tiletxt.c_str(),410,230,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Pause Menu");
		m_pBitmapfont->Print(tiletxt.c_str(),145,260,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Champions Only:");
		m_pBitmapfont->Print(tiletxt.c_str(),330,400,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Get/Change spell");
		m_pBitmapfont->Print(tiletxt.c_str(),330,415,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move Cursor");
		m_pBitmapfont->Print(tiletxt.c_str(),590,405,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt ="WASD:";
		m_pBitmapfont->Print(tiletxt.c_str(),145,330,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Move camera ");
		m_pBitmapfont->Print(tiletxt.c_str(),145,345,.25f,D3DCOLOR_XRGB(255,255,255));
		tiletxt =StringTable::GetInstance()->GetString("Cycle through Units ");
		m_pBitmapfont->Print(tiletxt.c_str(),300,210,.25f,D3DCOLOR_XRGB(255,255,255));

	}
	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-008
	/////////////////////////////////////////////////////////////////
}

CHelpMenuState* CHelpMenuState::GetInstance()
{
	static CHelpMenuState s_Instance;
	return &s_Instance;
}
