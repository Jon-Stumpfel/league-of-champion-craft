#include "StdAfx.h"
#include "TutorialTextState.h"
#include "StateStack.h"
#include "GraphicsManager.h"


CTutorialTextState::CTutorialTextState(void)
{
	m_nNextText=0;
}


CTutorialTextState::~CTutorialTextState(void)
{
}

CTutorialTextState* CTutorialTextState::GetInstance()
{
	static CTutorialTextState s_Instance;
	return &s_Instance;
}

void CTutorialTextState::Enter()
{
	
}

void CTutorialTextState::Exit()
{
	++m_nNextText;
}

void CTutorialTextState::Input(INPUT_ENUM input)
{
	if( input== INPUT_ACCEPT)
		CStateStack::GetInstance()->Pop();
}

void CTutorialTextState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 80, -10, 1.3f, 1.2f);
	if (m_nNextText==0)
		m_cFont.Print("WELCOME TO LEAGUE OF CHAMPION CRAFT",150,150,.3f,D3DCOLOR_XRGB(255,255,255),200);
	if (m_nNextText==1)
		m_cFont.Print("This is page two",150,150,.3f,D3DCOLOR_XRGB(255,255,255),200);

		
}

void CTutorialTextState::Update(float fElapsedTime)
{

}