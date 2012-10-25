#include "StdAfx.h"
#include "AttackPhaseTransState.h"
#include "Game.h"
#include "StateStack.h"
#include "BitmapFont.h"
#include "GameManager.h"
#include "CoinToss.h"
#include "AnimationManager.h"
#include "GameplayState.h"
#include "AIManager.h"

CCoinToss::CCoinToss(void)
{

}

CCoinToss::~CCoinToss(void)
{
	delete m_UAnonsense;
}

void CCoinToss::Enter(void)
{
	m_UAnonsense= new UnitAnimation();
	m_UAnonsense->animationType=AT_ATTACK_N;
	m_UAnonsense->unitType=UT_CASTLE;
	m_UAnonsense->fCurrentTime=0.0f;

	m_nCoinArc=CGame::GetInstance()->GetWindowHeight()+20;
	srand(unsigned int(time(0)));
	m_nChosenplayer=0;
	//m_nChosenplayer=7;//rand()%1+6;
	//m_UAnonsense->animationType=AT_ATTACK_N;
	m_fTimer =2.0f;
	m_fSecondTimer = 1.0f;
	m_bGoDown=false;
	m_bStop=false;
}

void CCoinToss::Exit(void)
{

}

CCoinToss* CCoinToss::GetInstance(void)
{
	static CCoinToss s_Instance;
	return &s_Instance;
}

void CCoinToss::Render(void)
{	
	Vec2D temparchor = CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense).GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX= CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense).GetRect().left-temparchor.nPosX;
	tempoffset.nPosY= CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense).GetRect().top-temparchor.nPosY;
	RECT temprect = CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense).GetRect();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Coin"),
		CGame::GetInstance()->GetWindowWidth()/2 - tempoffset.nPosX, m_nCoinArc - tempoffset.nPosY,
		1.0f,1.0f, &CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense).GetRect(),0,
		0,0,D3DCOLOR_XRGB(255,255,255));	
}

void CCoinToss::Update(float fElapsedTime)
{	
	if (m_nCoinArc<=60)
		m_bGoDown=true;

	if (!m_bGoDown)
		m_nCoinArc-=20;
	else
	{
		if (m_nCoinArc>=300)
		m_bStop=true;

		if (!m_bStop)
			m_nCoinArc+=20;
	}
	if(m_fTimer > 0.0f)
	{
		m_fTimer-=fElapsedTime;
		CAnimationManager::GetInstance()->Update(fElapsedTime);
	}
	if (m_fTimer<=0.0f)
	{
		if(m_nChosenplayer == 0)
		{
			m_nChosenplayer = rand()%1+6;
		}
		else if(m_nChosenplayer == 6)
		{
			CAnimationManager::GetInstance()->SetCoinFrame(13);
		}
		else
		{
			CAnimationManager::GetInstance()->SetCoinFrame(5);
		}
		m_fSecondTimer -= fElapsedTime;
		if(m_fSecondTimer <= 0.0f)
		{
			if (m_nChosenplayer==6)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(0);
				CGameManager::GetInstance()->SetNextPlayer(1);
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
			}
			if (m_nChosenplayer==7)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(1);
				CGameManager::GetInstance()->SetNextPlayer(0); 
				CAIManager::GetInstance()->BeginMovement();
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
			}
			CStateStack::GetInstance()->Pop();
		}
	}
}
void CCoinToss::Input(INPUT_ENUM input)
{

}
