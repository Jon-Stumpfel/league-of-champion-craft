#include "StdAfx.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "MessageSystem.h"
#include "InputManager.h"
#include "TileManager.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "AbilityManager.h"
#include "StateStack.h"
#include "AIManager.h"
#include "FloatingText.h"
#include "SGD Wrappers\CSGD_XAudio2.h"
#include "HUD.h"
#include "SoundManager.h"
#include "LevelSelectState.h"
#include "SocketServer.h"
#include <ctime>
#include "SpellScrollState.h"
#include "StringTable.h"
#include "PauseState.h"
CGame* CGame::GetInstance(void)
{	
	static CGame s_Instance;

	return &s_Instance;
}

int m_ngraphicsID = 0;
void CGame::Initialize(HWND hWnd, HINSTANCE hInstance,
	int nScreenWidth, int nScreenHeight,
	bool bIsWindowed)
{
	
	srand( unsigned int(time(0)) );
	rand();

	m_bDieThreadIHateYou = false;
	m_bShowFramerate = false;

	m_nWidth = nScreenWidth;
	m_nHeight = nScreenHeight;
	//m_bIsWindowed = bIsWindowed;
	m_hWnd = hWnd;

	CTileManager::GetInstance()->Init();
	CSGD_XAudio2::GetInstance()->InitXAudio2();
	CInputManager::GetInstance()->Initialize(hWnd, hInstance);
	CScriptManager::GetInstance()->Initialize();
	CMessageSystem::GetInstance()->InitMessageSystem(&CGameManager::MessageProc);
	CGraphicsManager::GetInstance()->Initialize(hWnd, hInstance, nScreenWidth, nScreenHeight, bIsWindowed);
	CAIManager::GetInstance()->Initialize();
	CFloatingText::GetInstance()->Initialize();
	CHUD::GetInstance()->Initialize();
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	long x = 0;
	x = cursorPos.x; 
	long y = 0;
	y = cursorPos.y;
	CGameplayState::GetInstance()->SetMouseOffset(Vec2D((int)x, (int)y));
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/wphighlight.png"), _T("wphighlight"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/ui.png"), _T("uioverlay"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/panelselectioncursor.png"), _T("panelselect"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/moveabilityicon.png"), _T("moveicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/meleeabilityicon.png"), _T("meleeattackicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/rangeabilityicon.png"), _T("rangeattackicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/minimaptriangle.png"), _T("minitriangle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/minimapcircle.png"), _T("minicircle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/heroportrait.png"), _T("heroportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/archerportrait.png"), _T("archerportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/swordsmanportrait.png"), _T("swordsmanportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/cavalryportrait.png"), _T("cavalryportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/skeletonportrait.png"), _T("skeletonportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/iceblockportrait.png"), _T("iceblockportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/castleportrait.png"), _T("castleportrait"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/speedicon.png"), _T("speedicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/rangeicon.png"), _T("rangeicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/damageicon.png"), _T("damageicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/tilesmovedicon.png"), _T("tilesmovedicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/shieldicon.png"), _T("shieldicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/showcard.png"), _T("showcard"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/spellpanel.png"), _T("spellpanel"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/champspellicon.png"), _T("champspellicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/fireballicon.png"), _T("fireballicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/shieldspellicon.png"), _T("shieldspellicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/healspellicon.png"), _T("healspellicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/facingarrow.png"), _T("facingarrow"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Sword.png"), _T("AttackSword"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Castle.png"), _T("MoveCastle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/spellbook.png"), _T("spellbook"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/spellscrollbackground.png"), _T("ssbackground"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/spellscrollselect.png"), _T("scrollselect"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/blankscroll.png"), _T("blankscroll"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/tooltip.png"), _T("tooltip"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/check.png"), _T("check"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/spelldesc.png"), _T("spelldesc"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/damage.png"), _T("damage"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/heal.png"), _T("healicon"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/scrollvert.png"), _T("scrollvert"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/singleplayer.png"), _T("singleplayer"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/multiplayer.png"), _T("multiplayer"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/blackpixel.png"), _T("blackpixel"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/tutorial.png"), _T("tutorial"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/vignette.png"), _T("vignette"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/vignette_night.png"), _T("vignette_night"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/vignette_snow.png"), _T("vignette_snow"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Menus/main_menu.png"), _T("main_menubg"), 0UL);
	
	
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page1.png"), _T("Page1"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page2.png"), _T("Page2"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page3.png"), _T("Page3"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page4.png"), _T("Page4"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page5.png"), _T("Page5"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Page6.png"), _T("Page6"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/page7.png"), _T("Page7"), 0UL);

	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman(Red).png",L"SwordsmanR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman(Blue).png",L"SwordsmanB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\skeleton(Blue).png",L"SkeletonB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\skeleton(Red).png",L"SkeletonR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\iceblock.png",L"IceBlock",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/newchampred.png",L"ChampionR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/newchampblue.png",L"ChampionB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary(Red).png",L"CavalryR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary(Blue).png",L"CavalryB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/castle(Red).png",L"CastleR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/castle(Blue).png",L"CastleB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer(Red).png",L"ArcherR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer(Blue).png",L"ArcherB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\RedBlueCoin.png",L"Coin",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\HUD\\skybox.png",L"skybox",D3DCOLOR_ARGB(255,255,255,255));


	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/zombiehurt2.ogg.wav"), _T("hurt"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/BowandArrow.wav"), _T("ArcherBasicAttack"),false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/TempDeath.wav"),_T("ITSDEAD"),false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/errorclip.wav"),_T("NO"),false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/Sword.wav"), _T("Sword"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/flippingpages.wav"), _T("flip"), false);
	//CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/errorclip.wav"), _T("click"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/click.wav"), _T("click"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/Footsteps.wav"), _T("Footstep"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/Gallop.wav"), _T("Gallop"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/savegame.wav"), _T("savegame"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/deletesave.wav"), _T("deletesave"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/teleport.wav"), _T("teleport"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/ice.wav"), _T("ice"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/selectionmove.wav"), _T("selectionmove"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/swordsheathe.wav"), _T("swordsheathe"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/rockfall.wav"), _T("rockfall"), false);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/MovementPhaseMusic.xwm"),_T("MovementPhaseMusic"),true);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/AttackPhaseMusic.xwm"),_T("AttackPhaseMusic"),true);
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/MainMenuMusic.xwm"),_T("MainMenuMusic"),true);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\Menus\\main_menu_bg.png"), _T("mainmenubg"),D3DXCOLOR(0,0,0,255));
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\Menus\\warrior_blue.png"), _T("warriorblue"),D3DXCOLOR(0,0,0,255));
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\Menus\\warrior_red.png"), _T("warriorred"),D3DXCOLOR(0,0,0,255));

	 CSoundManager::GetInstance()->LoadSound(_T("Assets\\Sounds\\MainMenuMusic.xwm"), _T("MainMenuMusic"), true);
	 CSoundManager::GetInstance()->LoadSound(_T("Assets\\Sounds\\AttackPhaseMusic.xwm"), _T("AttackPhaseMusic"), true);
	 CSoundManager::GetInstance()->LoadSound(_T("Assets\\Sounds\\MovementPhaseMusic.xwm"), _T("MovementPhaseMusic"), true);


	CAbilityManager::GetInstance()->LoadAbilities();
	CSpellScrollState::GetInstance()->Initialize();
	m_dwCurrTime = GetTickCount();
	TiXmlDocument doc;
	doc.LoadFile("Assets\\Menus\\Options.xml");
	TiXmlElement* pRoot = doc.RootElement();
	TiXmlElement* Option = pRoot->FirstChildElement("Option");
	while(Option != nullptr)
	{
		int temp = 0;
		Option->Attribute("Fullscreen", &temp);
		if(temp == 0)
			m_bIsWindowed	= false;	
		else
			m_bIsWindowed	= true;
		Option = Option->NextSiblingElement("Option");

	}

	CStateStack::GetInstance()->Push(CMainMenuState::GetInstance());

}

bool CGame::Main(void)
{
	// Main state loop

	if (Input() == false)
		return false;

	Update();
	Render();

	return true;
}
void CGame::Shutdown(void)
{
	TerminateThread(CSocketServer::GetInstance()->listenThread, 0);
	TerminateThread(CSocketServer::GetInstance()->workThread1, 0);
	TerminateThread(CSocketServer::GetInstance()->workThread2, 0);
	CStateStack::DeleteInstance();
	CFloatingText::DeleteInstance();
	CSocketServer::DeleteInstance();
	CSocketClient::DeleteInstance();
	CAIManager::DeleteInstance();
	CScriptManager::DeleteInstance();
	CAbilityManager::DeleteInstance();
	CInputManager::DeleteInstance();
	CGraphicsManager::DeleteInstance();
	CGameManager::DeleteInstance();
	CObjectManager::DeleteInstance();
	CMessageSystem::DeleteInstance();
	CTileManager::DeleteInstance();
	CSoundManager::DeleteInstance();
	StringTable::DeleteInstance();
}

CGame::CGame(void)
{
}

CGame::~CGame(void)
{

}

// 3 actions for each frame:
bool CGame::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	CSGD_DirectInput::GetInstance()->ReadDevices();
	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_LALT) || CSGD_DirectInput::GetInstance()->KeyDown(DIK_RALT))
	{
		if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
		{
			CSGD_Direct3D::GetInstance()->ChangeDisplayParam(m_nWidth, m_nHeight, !m_bIsWindowed);
			m_bIsWindowed = !m_bIsWindowed;
			TiXmlDocument doc;
			TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );  
			doc.LinkEndChild( decl );  

			TiXmlElement * root = new TiXmlElement( "Options" );  
			doc.LinkEndChild( root );  
			TiXmlElement* Options = new TiXmlElement("Option");
			root->LinkEndChild(Options);
			float tempS = CSGD_XAudio2::GetInstance()->SFXGetMasterVolume()*100;
			float tempM = CSGD_XAudio2::GetInstance()->MusicGetMasterVolume()*100;
			Options->SetAttribute("SoundVolume", (int)tempS);
			Options->SetAttribute("MusicVolume", (int)tempM);
			if(m_bIsWindowed == false)
				Options->SetAttribute("Fullscreen", 0);
			else
				Options->SetAttribute("Fullscreen", 1);
			if(StringTable::GetInstance()->GetIsItModern() == false)
				Options->SetAttribute("IsModern", 0);
			else
				Options->SetAttribute("IsModern", 1);
			doc.SaveFile("Assets\\Menus\\Options.xml");
			return true;
		}

		if (pDI->KeyDown(DIK_TAB))
		{
			if (CStateStack::GetInstance()->GetTop() == CGameplayState::GetInstance())
			{
				CStateStack::GetInstance()->Push(CPauseState::GetInstance());
			}
		}

		if (pDI->KeyDown(DIK_F4))
		{
			return false;
		}
	}
	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_F2))
	{
		m_bShowFramerate = !m_bShowFramerate;
	}

	// Working intercepting INputManager imeplenetation so that input is done here until then


	return CInputManager::GetInstance()->Input();
}
void CGame::Update(void)
{

	CSGD_XAudio2::GetInstance()->Update();

	DWORD	dwNow =  GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) * 0.001f;

	m_dwCurrTime = dwNow;

	if (fElapsedTime > 2.0f)
		fElapsedTime = 2.0f;

	if (m_bDieThreadIHateYou)
	{
		CStateStack::GetInstance()->Push(LevelSelectState::GetInstance());
		m_bDieThreadIHateYou = false;
	}

	CMessageSystem* pMS = CMessageSystem::GetInstance();
	pMS->ProcessMessages();
	CStateStack::GetInstance()->UpdateStack(fElapsedTime);

	static int nFrames = 0;
	static DWORD dwLast = GetTickCount();
	nFrames++;
	if (abs(double(dwNow - dwLast)) > 1000)
	{
		m_fFrameElapsed = (float)nFrames * 1000 / (float)abs(double(dwNow - dwLast));
		dwLast = GetTickCount();
		nFrames = 0;
		m_bUpdateFps = true;
	}
}
void CGame::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 255);
	CSGD_Direct3D::GetInstance()->DeviceBegin();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CStateStack::GetInstance()->RenderStack();
	static std::wostringstream woss;
	if (m_bUpdateFps)
	{
		woss.str(_T(""));
		woss << "FPS: " << (int)m_fFrameElapsed;
		m_bUpdateFps = false;
	}
	if (m_bShowFramerate)
		CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 10, 40, 255, 0, 0);
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->DeviceEnd();
	CSGD_Direct3D::GetInstance()->Present();
}
void CGame::SetIsWindowed(bool win)
{
	m_bIsWindowed = win;
	CSGD_Direct3D::GetInstance()->ChangeDisplayParam(m_nWidth, m_nHeight, m_bIsWindowed);
}