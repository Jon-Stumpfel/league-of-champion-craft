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
#include "StringTable.h"
#include "MovetPhaseTransState.h"
#include "TutorialTextState.h"
#include "SoundManager.h"
#include "XAudio2.h"
CCoinToss::CCoinToss(void)
{

}

CCoinToss::~CCoinToss(void)
{

}

void CCoinToss::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_UAnonsense= new UnitAnimation();
	int k = rand() % 10000;
	for(int i = 0; i < k; i++)
		m_nChosenplayer=rand()%101+1;
	if(m_nChosenplayer < 50)
		m_nChosenplayer = 0;
	else
		m_nChosenplayer = 1;
	m_bCoinFlipPlayed = false;
	m_bCoinHitPlayed = false;
	m_UAnonsense->animationType=AT_ATTACK_N;
	m_UAnonsense->unitType=UT_CASTLE;
	m_UAnonsense->fCurrentTime=1.0f;
	m_nCoinArc=CGame::GetInstance()->GetWindowHeight()+20;
	m_nPeak = rand()%(100-50)+50;
	m_fSecondTimer = 2.0f;
	m_bGoDown=false;
	m_bStop=false;
	CAnimationManager::GetInstance()->SetAnimBool(UT_CASTLE,(int)AT_ATTACK_N,true);
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
		if(m_nChosenplayer == 0)
		{
			CBitmapFont bmf; ostringstream oss;
			int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
			oss<<StringTable::GetInstance()->GetString("Player ")
				<< ++Playernum<<StringTable::GetInstance()->
				GetString(" wins the coin toss");
			bmf.Print(oss.str().c_str(),280,300,.5f, D3DCOLOR_XRGB(0,0,255));
		}
		if(m_nChosenplayer == 1)
		{
			CBitmapFont bmf; ostringstream oss; 
			int Playernum = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
			oss<<StringTable::GetInstance()->GetString("Player ")
				<< ++Playernum<<StringTable::GetInstance()->
				GetString(" wins the coin toss");
			bmf.Print(oss.str().c_str(),280,300,.5f, D3DCOLOR_XRGB(255,0,0));
		}
	}
}

void CCoinToss::Update(float fElapsedTime)
{	
		//if (!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("CoinFlip"))))
		//	CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("CoinFlip")), false);

	if (m_nCoinArc<=m_nPeak)
		m_bGoDown=true;
	if(!m_bCoinFlipPlayed)
	{
		CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("CoinFlip")));
		m_bCoinFlipPlayed = true;
	}
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
		//if (!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("CoinFlip"))))
		//	CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("CoinFlip")));
		//
		//if (!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("CoinHit"))))
		//	CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("CoinHit")));

		if(m_nChosenplayer == 1)
		{
			CAnimationManager::GetInstance()->SetCoinFrame(13);
		}
		if(m_nChosenplayer == 0)
		{
			CAnimationManager::GetInstance()->SetCoinFrame(5);
		}
		if(!m_bCoinHitPlayed)
		{
			CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("CoinFlip")));
			CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("CoinHit")));
			m_bCoinHitPlayed = true;
		}
		m_fTimer -= fElapsedTime;
		m_fSecondTimer -= fElapsedTime;
		if(m_fSecondTimer <= 1.0f)
		{
			if (m_nChosenplayer==0)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(0);
				CGameManager::GetInstance()->SetNextPlayer(1);
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
				CGameplayState::GetInstance()->SnapToPosition(CGameManager::GetInstance()->GetChampion(CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())->GetPos(), true);
				CAnimationManager::GetInstance()->SetAnimBool(UT_CASTLE,(int)AT_ATTACK_N,true);
			}
			if (m_nChosenplayer==1)
			{
				CGameManager::GetInstance()->SetCurrentPlayer(1);
				CGameManager::GetInstance()->SetNextPlayer(0); 
				CAIManager::GetInstance()->BeginMovement();
				CGameManager::GetInstance()->SetCurrentPhase(GP_MOVE);
				CGameplayState::GetInstance()->SnapToPosition(CGameManager::GetInstance()->GetChampion(1)->GetPos(), true);
				CAnimationManager::GetInstance()->SetAnimBool(UT_CASTLE,(int)AT_ATTACK_N,false);
			}
			if (m_fSecondTimer<=0.0f)
			{
				CStateStack::GetInstance()->Pop();
				CStateStack::GetInstance()->Push(CMovetPhaseTransState::GetInstance());
				
				if(CGameManager::GetInstance()->GetTutorial()==true)
				{
					CTutorialTextState::GetInstance()->SetTexttoShow(TTU_MOVEMENT);
					CStateStack::GetInstance()->Push(CTutorialTextState::GetInstance());

					CTutorialTextState::GetInstance()->SetTexttoShow(TTU_INTRO);
					CStateStack::GetInstance()->Push(CTutorialTextState::GetInstance());
				}
			}
		}
	}
}
void CCoinToss::Input(INPUT_ENUM input)
{

}
