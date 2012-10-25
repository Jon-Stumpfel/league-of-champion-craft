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
#include "SoundManager.h"
#include <ctime>
CGame* CGame::GetInstance(void)
{	
	static CGame s_Instance;

	return &s_Instance;
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance,
	int nScreenWidth, int nScreenHeight,
	bool bIsWindowed)
{
	srand( unsigned int(time(0)) );
	rand();

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
	CStateStack::GetInstance()->Push(CMainMenuState::GetInstance());
	CAIManager::GetInstance()->Initialize();
	CFloatingText::GetInstance()->Initialize();
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

	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Sword.png"), _T("AttackSword"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/HUD/Castle.png"), _T("MoveCastle"), 0UL);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman(Red).png",L"SwordsmanR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman(Blue).png",L"SwordsmanB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\skeleton(Blue).png",L"SkeletonB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\skeleton(Red).png",L"SkeletonR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\iceblock.png",L"IceBlock",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/champion(Red).png",L"ChampionR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/champion(Blue).png",L"ChampionB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary(Red).png",L"CavalryR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary(Blue).png",L"CavalryB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/castle(Red).png",L"CastleR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/castle(Blue).png",L"CastleB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer(Red).png",L"ArcherR",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer(Blue).png",L"ArcherB",D3DCOLOR_ARGB(255,255,255,255));
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\RedBlueCoin.png",L"Coin",D3DCOLOR_ARGB(255,255,255,255));
	CSoundManager::GetInstance()->LoadSound(_T("Assets/Sounds/zombiehurt2.ogg.wav"), _T("hurt"), false);

	CAbilityManager::GetInstance()->LoadAbilities();
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
	CStateStack::DeleteInstance();
	CFloatingText::DeleteInstance();
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
	//CStateStack::DeleteInstance();

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
			return true;
		}
	}

	// Working intercepting INputManager imeplenetation so that input is done here until then


	return CInputManager::GetInstance()->Input();
}
void CGame::Update(void)
{
	DWORD	dwNow =  GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) * 0.001f;

	m_dwCurrTime = dwNow;

	if (fElapsedTime > 2.0f)
		fElapsedTime = 2.0f;

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
	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 10, 5, 255, 0, 0);
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->DeviceEnd();
	CSGD_Direct3D::GetInstance()->Present();
}
void CGame::SetIsWindowed(bool win)
{
	m_bIsWindowed = win;
	CSGD_Direct3D::GetInstance()->ChangeDisplayParam(m_nWidth, m_nHeight, m_bIsWindowed);
}