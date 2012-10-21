#include "StdAfx.h"
#include "GameOverState.h"

//CGameOverState* CGameOverState::s_Instance = nullptr;

CGameOverState::CGameOverState(void)
{
}


CGameOverState::~CGameOverState(void)
{
}

void CGameOverState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(true);
}

void CGameOverState::Exit(void)
{

}

void CGameOverState::Input(INPUT_ENUM input)
{
	switch(input)
	{
	case INPUT_ACCEPT:
		{
			CStateStack::GetInstance()->Pop();
			CStateStack::GetInstance()->Pop();
			CStateStack::GetInstance()->Push(CMainMenuState::GetInstance());
		}
	}
}

void CGameOverState::Update(float fElapsedTime)
{
	
}

void CGameOverState::Render(void)
{
	ostringstream temp;
	temp<<"Player  "<<Player<<"  Wins!";
	tempfont.Print(temp.str().c_str(),200,50,1.0f,D3DXCOLOR(255,255,255,255));
}

CGameOverState* CGameOverState::GetInstance()
{
	static CGameOverState s_Instance;
	return &s_Instance;
}