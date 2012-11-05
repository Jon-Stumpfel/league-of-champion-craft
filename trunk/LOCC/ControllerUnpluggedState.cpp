#include "StdAfx.h"
#include "ControllerUnpluggedState.h"
#include "StateStack.h"
#include "GraphicsManager.h"
#include "BitmapFont.h"
CControllerUnpluggedState::CControllerUnpluggedState(void)
{
}


CControllerUnpluggedState::~CControllerUnpluggedState(void)
{
}


CControllerUnpluggedState* CControllerUnpluggedState::GetInstance()
{
	static CControllerUnpluggedState s_Instance;
	return &s_Instance;
}	

void CControllerUnpluggedState::Enter(void)
{
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\Menus\\360controller.png"), _T("360pad"), D3DCOLOR_XRGB(255, 0, 255));
}
void CControllerUnpluggedState::Exit(void)
{
	CGraphicsManager::GetInstance()->RemoveImage(_T("360pad"));
}
void CControllerUnpluggedState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
			CStateStack::GetInstance()->Pop();

		}
		break;

	}
}
void CControllerUnpluggedState::Update(float fElapsedTime)
{
}
void CControllerUnpluggedState::Render(void)
{

	CBitmapFont bitmapFont;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("360pad")),
		188, 46, 1.0f, 1.0f);
	//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("blackpixel")),
	//	30, 326, 735.0f, 120.0f);

	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 850, 315, 0.3f, 1.7f,
		(RECT*)0, 0.0f, 0.0f, 90 * 3.1415928/180);


	bitmapFont.Print("Controller Unplugged", 40, 336, 1.2f, D3DCOLOR_XRGB(255, 255, 255));
	std::ostringstream oss;
	oss << "Please connected controller " << m_nJoyToPlug;
	bitmapFont.Print(oss.str().c_str(), 60, 400, 0.8f, D3DCOLOR_XRGB(255, 255, 255));
}
