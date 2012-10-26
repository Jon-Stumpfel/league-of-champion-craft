#include "StdAfx.h"
#include "MovetPhaseTransState.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "StateStack.h"
#include "BitmapFont.h"
#include <assert.h>
#include "GameManager.h"
#include "Player.h"

CMovetPhaseTransState::CMovetPhaseTransState(void)
{
	m_MovingUp=0;
}

CMovetPhaseTransState::~CMovetPhaseTransState(void)
{

}

void CMovetPhaseTransState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_MovingUp=CGame::GetInstance()->GetWindowHeight();
	m_fTimer = 1.5f;
}

void CMovetPhaseTransState::Exit(void)
{
}

CMovetPhaseTransState* CMovetPhaseTransState::GetInstance(void)
{
	static CMovetPhaseTransState s_Instance;
	return &s_Instance;
}

void CMovetPhaseTransState::Render(void)
{	
	RECT swordrect= {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("MoveCastle")),0,m_MovingUp,1.6f,1.5f,&swordrect);
	
	if (m_fTimer<=1.0f && m_fTimer>=0.0f)
	{
		CBitmapFont bmf; ostringstream oss; 
		int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
		
		oss<<"Player "<< ++Playernum<<" Movement Phase";
		bmf.Print(oss.str().c_str(),200,450,.5f, D3DCOLOR_XRGB(0,255,0));
	}
}

void CMovetPhaseTransState::Update(float fElapsedTime)
{
	if (m_MovingUp>=250)
		m_MovingUp-=20;

	m_fTimer-=fElapsedTime;

	if (m_fTimer<=0.0f)
	{
		CStateStack::GetInstance()->Pop();
	}
}
void CMovetPhaseTransState::Input(INPUT_ENUM input)
{

}

