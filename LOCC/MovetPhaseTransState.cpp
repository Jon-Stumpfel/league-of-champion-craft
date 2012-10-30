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
	if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CStateStack::GetInstance
		()->GetMoM()))
	{
		CSGD_XAudio2::GetInstance()->MusicStopSong(CStateStack::GetInstance
		()->GetMeM());
		CSGD_XAudio2::GetInstance()->MusicStopSong(CStateStack::GetInstance
		()->GetAM());
		CSGD_XAudio2::GetInstance()->MusicPlaySong(CStateStack::GetInstance
		()->GetMoM(),true);
	}
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
		
		if (Playernum==0)
		{
		oss<<"Player "<< Playernum+1<<" Movement Phase";
		bmf.Print(oss.str().c_str(),200,450,.5f, D3DCOLOR_XRGB(0,0,255));
		}
		if (Playernum==1)
		{
		oss<<"Player "<< Playernum+1<<" Movement Phase";
		bmf.Print(oss.str().c_str(),200,450,.5f, D3DCOLOR_XRGB(255,0,0));
		}
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
	//PUT_SOUND_HERE("Rock Crumble")
}
void CMovetPhaseTransState::Input(INPUT_ENUM input)
{

}

