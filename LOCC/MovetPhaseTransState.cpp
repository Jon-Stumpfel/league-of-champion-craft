#include "StdAfx.h"
#include "MovetPhaseTransState.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "StateStack.h"
#include "BitmapFont.h"
#include <assert.h>
#include "GameManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "GameplayState.h"
#include "StringTable.h"

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
	CGameplayState::GetInstance()->SetMusicIncrease(0.0f);
	CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("rockfall")), false, false);
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
	RECT swordrect= {0,0,1024,1024};
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("MoveCastle")),0,m_MovingUp,1.0f,1.0f,&swordrect);
	
	if (m_fTimer<=1.0f && m_fTimer>=0.0f)
	{
		CBitmapFont bmf; ostringstream oss; 
		int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
		
		if (Playernum==0)
		{
/////////////////////////////////////////////////////////////////
// BUG FIX
// Reference Bug # BB-043
// BUG FIX START
/////////////////////////////////////////////////////////////////
		oss<<"Player "<< Playernum+1<<StringTable::GetInstance()->GetString(" Movement Phase").c_str();
		bmf.Print(oss.str().c_str(),200,450,.5f, D3DCOLOR_XRGB(0,0,255),400);
		}
		if (Playernum==1)
		{
		oss<<"Player "<< Playernum+1<<StringTable::GetInstance()->GetString(" Movement Phase").c_str();
		bmf.Print(oss.str().c_str(),200,450,.5f, D3DCOLOR_XRGB(255,0,0),400);
/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-043
/////////////////////////////////////////////////////////////////
		}
	}
}

void CMovetPhaseTransState::Update(float fElapsedTime)
{
	if (m_MovingUp>=150)
		m_MovingUp-=20;
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic")),true);
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")),true);
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic")),true);
	m_fTimer-=fElapsedTime;

	if (m_fTimer<=0.0f)
	{
		CStateStack::GetInstance()->Pop();
	}
	//PUT_SOUND_HERE("Rock Crumble")
}
void CMovetPhaseTransState::Input(INPUT_ENUM input)
{

}

