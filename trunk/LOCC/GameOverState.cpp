#include "StdAfx.h"
#include "GameOverState.h"
#include "StringTable.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "GraphicsManager.h"
#include "Player.h"
#include "Hero.h"
//CGameOverState* CGameOverState::s_Instance = nullptr;

CGameOverState::CGameOverState(void)
{
}


CGameOverState::~CGameOverState(void)
{
}

void CGameOverState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_nPage = 0;
}

void CGameOverState::Exit(void)
{

}

void CGameOverState::Input(INPUT_ENUM input)
{
	switch(input)
	{
	case INPUT_CANCEL:
		{
			CStateStack::GetInstance()->Switch(CMainMenuState::GetInstance());
		}
		break;

	case INPUT_LEFT:
		{
			if( m_nPage == 0 )
				m_nPage = 4;
			else
				m_nPage--;
		}
		break;

	case INPUT_RIGHT:
		{
			if( m_nPage == 4 )
				m_nPage = 0;
			else
				m_nPage++;
		}
		break;
	}
}

void CGameOverState::Update(float fElapsedTime)
{
	
}

void CGameOverState::Render(void)
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();

	ostringstream temp;
	if(AI)
	{
		temp << StringTable::GetInstance()->GetString("Defeated");
		//PUT_SOUND_HERE("AIwins")
	}
	else
	{
		temp << StringTable::GetInstance()->GetString("Player ") << " "<< Player<<StringTable::GetInstance()->GetString("  Wins!");
		//PUT_SOUND_HERE("GenericWin")
	}

	pTM->Draw(pGM->GetID(_T("scrollvert")), 20, -20, 1.5f, 1.2f);

	tempfont.Print(temp.str().c_str(),275,85,.6f,D3DXCOLOR(255,255,255,255));

	if( m_nPage == 0 )
		tempfont.Print("Created", 325, 160, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
	else if( m_nPage == 1 )
		tempfont.Print("Damage", 325, 160, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
	else if( m_nPage == 2 )
		tempfont.Print("Killed", 350, 160, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
	else if( m_nPage == 3 )
		tempfont.Print("Champion", 310, 160, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
		tempfont.Print("Player", 325, 160, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));

	tempfont.Print("Player 1", 190, 220, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
	tempfont.Print("Player 2", 465, 220, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));

	ostringstream oss;
	int p1Archer = 0, p2Archer = 0, p1Calv = 0, p2Calv = 0, p1Sword = 0, p2Sword = 0;
	// player 1
	CPlayer* player = CGameManager::GetInstance()->GetPlayer(0);
	if( m_nPage == 0 )
	{
		p1Archer = player->GetStats()->nArcherCreated;
		p1Calv = player->GetStats()->nCalvaryCreated;
		p1Sword = player->GetStats()->nSwordsmanCreated;
	}
	else if( m_nPage == 1 )
	{
		p1Archer = player->GetStats()->nArcherDamageDone;
		p1Calv = player->GetStats()->nCalvaryDamageDone;
		p1Sword = player->GetStats()->nSwordsmanDamageDone;
	}
	else if( m_nPage == 2 )
	{
		p1Archer = player->GetStats()->nArcherKilled;
		p1Calv = player->GetStats()->nCavalryKilled;
		p1Sword = player->GetStats()->nSwordsmanKilled;
	}
	// player 2
	CPlayer* player2 = CGameManager::GetInstance()->GetPlayer(1);
	if( m_nPage == 0 )
	{
		p2Archer = player2->GetStats()->nArcherCreated;
		p2Calv = player2->GetStats()->nCalvaryCreated;
		p2Sword = player2->GetStats()->nSwordsmanCreated;
	}
	else if( m_nPage == 1 )
	{
		p2Archer = player2->GetStats()->nArcherDamageDone;
		p2Calv = player2->GetStats()->nCalvaryDamageDone;
		p2Sword = player2->GetStats()->nSwordsmanDamageDone;
	}
	else if( m_nPage == 2 )
	{
		p2Archer = player2->GetStats()->nArcherKilled;
		p2Calv = player2->GetStats()->nCavalryKilled;
		p2Sword = player2->GetStats()->nSwordsmanKilled;
	}

	if( m_nPage < 3 )
	{
		// player 1
		// archer
		oss << p1Archer;
		tempfont.Print(oss.str().c_str(),245,285,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");
		// swordsman
		oss << p1Sword;
		tempfont.Print(oss.str().c_str(),245,345,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");
		// cavalry
		oss << p1Calv;
		tempfont.Print(oss.str().c_str(),245,405,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");

		// player 2
		// archer
		oss << p2Archer;
		tempfont.Print(oss.str().c_str(),525,285,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");
		// swordsman
		oss << p2Sword;
		tempfont.Print(oss.str().c_str(),525,345,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");
		// cavalry
		oss << p2Calv;
		tempfont.Print(oss.str().c_str(),525,405,.6f,D3DXCOLOR(255,255,255,255));
		oss.str("");

		pTM->Draw(pGM->GetID(_T("archerportrait")), 375, 275, .8f, .8f);
		pTM->Draw(pGM->GetID(_T("swordsmanportrait")), 375, 335, .8f, .8f);
		pTM->Draw(pGM->GetID(_T("cavalryportrait")), 375, 395, .8f, .8f);
	}
	else if( m_nPage == 3 )
	{
		oss << "AP";
		tempfont.Print(oss.str().c_str(), 380, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");

		pTM->Draw(pGM->GetID(_T("damage")), 375, 325, .8f, .8f);
		pTM->Draw(pGM->GetID(_T("healicon")), 375, 400, .8f, .8f);
		// player 1
		// ap
		oss << player->GetStats()->nPlayerAPSpent;
		tempfont.Print(oss.str().c_str(), 245, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// damage
		oss << player->GetStats()->nChampionDamageDone;
		tempfont.Print(oss.str().c_str(), 245, 340, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// healing
		oss << player->GetStats()->nChampionHealingDone;
		tempfont.Print(oss.str().c_str(), 245, 410, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// player 2
		// ap
		oss << player2->GetStats()->nPlayerAPSpent;
		tempfont.Print(oss.str().c_str(), 525, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// damage
		oss << player2->GetStats()->nChampionDamageDone;
		tempfont.Print(oss.str().c_str(), 525, 340, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// healing
		oss << player2->GetStats()->nChampionHealingDone;
		tempfont.Print(oss.str().c_str(), 525, 410, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
	}
	else
	{
		oss << StringTable::GetInstance()->GetString("  Wood ");
		tempfont.Print(oss.str().c_str(), 350, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");

		oss << StringTable::GetInstance()->GetString("  Metal ");
		tempfont.Print(oss.str().c_str(), 350, 325, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");

		oss << "EXP";
		tempfont.Print(oss.str().c_str(), 360, 385, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");

		// player2
		// wood
		oss << player2->GetStats()->nPlayerWoodEarned;
		tempfont.Print(oss.str().c_str(), 525, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// metal
		oss << player2->GetStats()->nPlayerMetalEarned;
		tempfont.Print(oss.str().c_str(), 525, 325, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// exp
		oss << player2->GetStats()->nPlayerEXPEarned;
		tempfont.Print(oss.str().c_str(), 525, 385, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");

		// player1
		// wood
		oss << player->GetStats()->nPlayerWoodEarned;
		tempfont.Print(oss.str().c_str(), 245, 275, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// metal
		oss << player->GetStats()->nPlayerMetalEarned;
		tempfont.Print(oss.str().c_str(), 245, 325, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
		// exp
		oss << player->GetStats()->nPlayerEXPEarned;
		tempfont.Print(oss.str().c_str(), 245, 385, .6f, D3DCOLOR_ARGB(255, 255, 255, 255));
		oss.str("");
	}
	
}

CGameOverState* CGameOverState::GetInstance()
{
	static CGameOverState s_Instance;
	return &s_Instance;
}