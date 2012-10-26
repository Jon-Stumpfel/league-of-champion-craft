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
#include "Player.h"

CCoinToss::CCoinToss(void)
{

}

CCoinToss::~CCoinToss(void)
{

}

void CCoinToss::Enter(void)
{
	m_UAnonsense= new UnitAnimation();
	m_UAnonsense->animationType=AT_ATTACK_N;
	m_UAnonsense->unitType=UT_CASTLE;
	m_UAnonsense->fCurrentTime=0.0f;
	m_nCoinArc=CGame::GetInstance()->GetWindowHeight()+20;
	m_nChosenplayer=0;
	m_nPeak = rand()%200;
	m_fTimer =2.0f;
	m_fSecondTimer = 2.0f;
	m_bGoDown=false;
	m_bStop=false;
}

void CCoinToss::Exit(void)
{
	delete m_UAnonsense;
}

CCoinToss* CCoinToss::GetInstance(void)
{
	static CCoinToss s_CoinTossInstance;
	return &s_CoinTossInstance;
}

void CCoinToss::Render(void)
{	
	Vec2D temparchor = CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX= CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetRect().left-temparchor.nPosX;
	tempoffset.nPosY= CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetRect().top-temparchor.nPosY;
	RECT temprect = CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetRect();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Coin"),
		CGame::GetInstance()->GetWindowWidth()/2 - tempoffset.nPosX, m_nCoinArc - tempoffset.nPosY,
		2.0f, 2.0f, &CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetRect(),0,
		0,0,D3DCOLOR_XRGB(255,255,255));

	if (m_fSecondTimer<1.0f)
	{
		if(m_nChosenplayer == 6)
		{
			CBitmapFont bmf; ostringstream oss; 
			int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
			oss<<"Player "<< ++Playernum<<" wins";
			bmf.Print(oss.str().c_str(),280,300,.5f, D3DCOLOR_XRGB(0,0,255));
		}
		if(m_nChosenplayer == 7)
		{
			CBitmapFont bmf; ostringstream oss; 
			int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
			oss<<"Player "<< ++Playernum<<" wins";
			bmf.Print(oss.str().c_str(),280,300,.5f, D3DCOLOR_XRGB(255,0,0));
		}
	}
}

void CCoinToss::Update(float fElapsedTime)
{	
	if (m_nCoinArc<=m_nPeak)
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
	if(!m_bStop)
	{
		CAnimationManager::GetInstance()->Update(fElapsedTime);
	}
	if (m_bStop)
	{
		if(m_nChosenplayer == 0)
		{
			if(CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 0 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 1 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 2 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 3 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 4 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 6 ||
				CAnimationManager::GetInstance()->GetFrame(*m_UAnonsense)->GetFrame() == 7)
			{
				m_nChosenplayer = 7;
			}
			else
			{
				m_nChosenplayer = 6;
			}

		}
		if(m_nChosenplayer == 6)
		{
			CAnimationManager::GetInstance()->SetCoinFrame(13);

		}
		if(m_nChosenplayer == 7)
		{
			CAnimationManager::GetInstance()->SetCoinFrame(5);
			
		}
		m_fSecondTimer -= fElapsedTime;
		if(m_fSecondTimer <= 1.0f && m_fSecondTimer <= 1.5f)
		{
			if (m_nChosenplayer==6)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(0);
				CGameManager::GetInstance()->SetNextPlayer(1);
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
			CGameplayState::GetInstance()->SnapToPosition(CGameManager::GetInstance()->GetChampion(CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())->GetPos());
			}
			if (m_nChosenplayer==7)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(1);
				CGameManager::GetInstance()->SetNextPlayer(0); 
				CAIManager::GetInstance()->BeginMovement();
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
				CGameplayState::GetInstance()->SnapToPosition(CGameManager::GetInstance()->GetChampion(1)->GetPos());

			}
			if (m_fSecondTimer<=0.0f)
			{
				//CStateStack::GetInstance()->Push(CMovetPhaseTransState::GetInstance());
				CStateStack::GetInstance()->Pop();
			}
		}
	}
}
void CCoinToss::Input(INPUT_ENUM input)
{

}
