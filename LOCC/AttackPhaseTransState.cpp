#include "StdAfx.h"
#include "AttackPhaseTransState.h"
#include "Game.h"
#include "GraphicsManager.h"
#include "StateStack.h"
#include "BitmapFont.h"
#include <assert.h>
#include "GameManager.h"
#include "Player.h"
#include "StringTable.h"
#include "SoundManager.h"
CAttackPhaseTransState::CAttackPhaseTransState(void)
{
	m_MovingL=0;
	m_MovingR=0;
}

CAttackPhaseTransState::~CAttackPhaseTransState(void)
{

}

void CAttackPhaseTransState::Enter(void)
{
	m_MovingR=0;
	m_MovingL=CGame::GetInstance()->GetWindowWidth();
	m_fTimer = 1.5f;
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	CGameplayState::GetInstance()->SetMusicIncrease(0.0f);
	CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("swordsheathe")), false, false);
}

void CAttackPhaseTransState::Exit(void)
{

}

CAttackPhaseTransState* CAttackPhaseTransState::GetInstance(void)
{
	static CAttackPhaseTransState s_Instance;
	return &s_Instance;
}

void CAttackPhaseTransState::Render(void)
{	
	RECT swordrect= {0,0,512,64};
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("AttackSword")),
		m_MovingL,250,0.9f,2.0f,&swordrect);

	float rotate = (float(180 * (3.14159286 / 180)));
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("AttackSword")),
		m_MovingR,325,0.9f,2.0f,&swordrect,0.0,0.0,rotate);

	//PUT_SOUND_HERE("Sword Clang")
	
	if (m_fTimer<=1.0f && m_fTimer>=0.0f)
	{
		CBitmapFont bmf; ostringstream oss; 
		int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
		
		if(Playernum==0)
		{
			oss.str("");
		oss<<StringTable::GetInstance()->GetString("Player ")<< Playernum+1;
		bmf.Print(oss.str().c_str(),300,250,0.5f, D3DCOLOR_XRGB(0,0,255));
		bmf.Print(StringTable::GetInstance()->GetString
			("Attack Phase").c_str(),270,300,0.5f, D3DCOLOR_XRGB(0,0,255));
		}
		if(Playernum==1)
		{
		oss<<StringTable::GetInstance()->GetString("Player ")<< Playernum+1;
		bmf.Print(oss.str().c_str(),300,250,0.5f, D3DCOLOR_XRGB(255,0,0));
		bmf.Print(StringTable::GetInstance()->GetString
			("Attack Phase").c_str(),270,300,0.5f, D3DCOLOR_XRGB(255,0,0));
		}
	}
}

void CAttackPhaseTransState::Update(float fElapsedTime)
{
	if (m_MovingL>=250)
	m_MovingL-=20;
	if (m_MovingR<=550)
	m_MovingR+=20;
	m_fTimer-=fElapsedTime;

	if (m_fTimer<=0.0f)
	{
		CStateStack::GetInstance()->Pop();
	}
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic")),true);
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")),true);
	CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic")),true);
}
void CAttackPhaseTransState::Input(INPUT_ENUM input)
{

}
