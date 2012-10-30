#include "StdAfx.h"
#include "SpellScrollState.h"
#include "StateStack.h"
#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "AbilityManager.h"
#include "BitmapFont.h"
#include "GameplayState.h"
#include "Hero.h"
#include "GameManager.h"
#include "Player.h"
//CSpellScrollState* CSpellScrollState::s_Instance = nullptr;

CSpellScrollState::CSpellScrollState(void)
{
}


CSpellScrollState::~CSpellScrollState(void)
{
}


void CSpellScrollState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_nSelected = 0;
	m_nSelectedAbility = 0;
	m_bTreeSelect = true;
	m_pCustomer = dynamic_cast<CHero*>(CGameplayState::GetInstance()->GetSelectedUnit());
	m_nSwap = CGameplayState::GetInstance()->GetSelectedSpell();
	m_nExp = CGameManager::GetInstance()->GetCurrentPlayer()->GetExp();
}

void CSpellScrollState::Exit(void)
{

}

void CSpellScrollState::Input(INPUT_ENUM input)
{
	switch( input )
	{
	case INPUT_UP:
		{
			if( m_bTreeSelect )
			{
				if( m_nSelected == 0 )
					m_nSelected = 2;
				else
					m_nSelected--;
			}
			else
			{
				if( m_nSelectedAbility < 6 )
				{
					if( m_nSelectedAbility == 0 )
						m_nSelectedAbility = 5;
					else
						m_nSelectedAbility--;
				}
				else
				{
					if( m_nSelectedAbility == 6 )
						m_nSelectedAbility = 9;
					else
						m_nSelectedAbility--;
				}
			}
		}
		break;

	case INPUT_DOWN:
		{
			if( m_bTreeSelect )
			{
				if( m_nSelected == 2 )
					m_nSelected = 0;
				else
					m_nSelected++;
			}
			else
			{
				if( m_nSelectedAbility < 6 )
				{
					if( m_nSelectedAbility == 5 )
						m_nSelectedAbility = 0;
					else
						m_nSelectedAbility++;
				}
				else
				{
					if( m_nSelectedAbility == 9 )
						m_nSelectedAbility = 6;
					else
						m_nSelectedAbility++;
				}
			}
		}
		break;

	case INPUT_RIGHT:
		{
			if( m_nSelectedAbility < 6 )
				m_nSelectedAbility = 6;
			else
				m_nSelectedAbility = 0;
		}
		break;

	case INPUT_LEFT:
		{
			if( m_nSelectedAbility < 6 )
				m_nSelectedAbility = 6;
			else
				m_nSelectedAbility = 0;
		}
		break;

	case INPUT_ACCEPT:
		{
			if( m_bTreeSelect )
				flipping = true;
			else
			{
				bool bought = false;

				if( m_nSelected == 0 )
					bought = m_pCustomer->IfBought(m_vElemental[m_nSelectedAbility]);
				else if( m_nSelected == 1 )
					bought = m_pCustomer->IfBought(m_vPhysical[m_nSelectedAbility]);
				else
					bought = m_pCustomer->IfBought(m_vSupport[m_nSelectedAbility]);

				if( bought == false )
				{
					if( m_nSelectedAbility < 3 )
					{
						if( m_nExp < 100 )
						{
							//PUT_SOUND_HERE("EHHHHHH")
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 100);
					
					}
					else if( m_nSelectedAbility < 6 )
					{
						if( m_nExp < 200 )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 200);
					}
					else if( m_nSelectedAbility < 9 )
					{
						if( m_nExp < 300 )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 300);
					}
					else
					{
						if( m_nExp < 400 )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 400);
					}
				}
				else
				{
					if( m_nSelected == 0 )
					{
						if( m_pCustomer->SearchSpells(m_vElemental[m_nSelectedAbility]) )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}
					}
					else if( m_nSelected == 1 )
					{
						if( m_pCustomer->SearchSpells(m_vPhysical[m_nSelectedAbility]) )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}
					}
					else
					{
						if( m_pCustomer->SearchSpells(m_vSupport[m_nSelectedAbility]) )
						{
							//PUT_SOUND_HERE("EHHHHHHH")
							return;
						}
					}
				}

				if( m_nSelected == 0 )
				{
					m_pCustomer->SwapSpell(m_vElemental[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vElemental[m_nSelectedAbility]);
					m_pCustomer->SetCooldown(m_nSwap, m_vElemental[m_nSelectedAbility]->GetCoolDown());
				}
				else if( m_nSelected == 1 )
				{
					m_pCustomer->SwapSpell(m_vPhysical[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vPhysical[m_nSelectedAbility]);
					m_pCustomer->SetCooldown(m_nSwap, m_vPhysical[m_nSelectedAbility]->GetCoolDown());
				}
				else
				{
					m_pCustomer->SwapSpell(m_vSupport[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vSupport[m_nSelectedAbility]);
					m_pCustomer->SetCooldown(m_nSwap, m_vSupport[m_nSelectedAbility]->GetCoolDown());
				}

				CStateStack::GetInstance()->Pop();
			}
		}
		break;

	case INPUT_CANCEL:
		{
			if( m_bTreeSelect == false )
			{
				flipping = true;
				m_nSelectedAbility = 0;
			}
			else
				CStateStack::GetInstance()->Pop();
		}
		break;
	}
}

void CSpellScrollState::Update(float fElapsedTime)
{
	if ( flipping )
	{
		static float time = 0;

		if( time >= .04f )
		{
			time = 0;
			page++;
			if( page == 7 )
			{
				page = 1;
				flipping = false;
				m_bTreeSelect = !m_bTreeSelect;
			}
		}

		time += fElapsedTime;
	}
}

void CSpellScrollState::Render(void)
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	CBitmapFont* pBF = new CBitmapFont();

	pTM->Draw(pGM->GetID(_T("ssbackground")), 0, 0);

	if( flipping == true )
	{
		if( page == 1 )
			pTM->Draw(pGM->GetID(_T("Page1")), 175, -30, .5f, .5f);
		else if( page == 2 )
			pTM->Draw(pGM->GetID(_T("Page2")), 175, -30, .5f, .5f);
		else if( page == 3 )
			pTM->Draw(pGM->GetID(_T("Page3")), 175, -30, .5f, .5f);
		else if( page == 4 )
			pTM->Draw(pGM->GetID(_T("Page4")), 175, -30, .5f, .5f);
		else if( page == 5 )
			pTM->Draw(pGM->GetID(_T("Page5")), 175, -30, .5f, .5f);
		else if( page == 6 )
			pTM->Draw(pGM->GetID(_T("Page6")), 175, -30, .5f, .5f);
		else if( page == 7 )
			pTM->Draw(pGM->GetID(_T("Page7")), 175, -30, .5f, .5f);
	}
	else
	{
		pTM->Draw(pGM->GetID(_T("Page1")), 175, -30, .5f, .5f);


		if( m_bTreeSelect == false )
		{
			pTM->Draw(pGM->GetID(_T("spelldesc")), 195, 475, .9f, .9f);
			CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
		
			CAbility* selected;
			if( m_nSelected == 0 )
				selected = m_vElemental[m_nSelectedAbility];
			else if( m_nSelected == 1 )
				selected = m_vPhysical[m_nSelectedAbility];
			else
				selected = m_vSupport[m_nSelectedAbility];


			if( selected->GetIfAttack() )
			pTM->Draw(pGM->GetID(_T("check")), 240, 485, .5f, .5f);

			ostringstream tt;
			tt  << selected->GetApCost();
			pBF->Print(tt.str().c_str(), 299, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");

			if( selected->GetPhase() == GP_MOVE )
				tt << "Move";
			else
				tt << "Attack";

			pBF->Print(tt.str().c_str(), 278, 525, .2f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");

			tt << selected->GetRange();
			pBF->Print(tt.str().c_str(), 373, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetCoolDown();
			pBF->Print(tt.str().c_str(), 373, 523, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetDamage();
			pBF->Print(tt.str().c_str(), 373, 555, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));	

			tt.str("");
			tt << selected->GetName();
			pBF->Print(tt.str().c_str(), 210, 556, .2f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetDescription();
			pBF->Print(tt.str().c_str(), 427, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255), 170);

		}

		ostringstream xp;
		xp << "Exp: " << m_nExp;
		pBF->Print(xp.str().c_str(), 10, 20, .5f, D3DCOLOR_ARGB(255, 255, 255, 255));

		if( m_bTreeSelect )
		{
			ostringstream oss;
			oss << "Ye Olde Table of Contents";
			pBF->Print(oss.str().c_str(), 440, 50, .6f, D3DCOLOR_ARGB(255, 255, 255, 255), 240);	
			oss.str("");
			oss << "Elemental";
			pBF->Print(oss.str().c_str(), 450, 200 - 60, .7f, m_nSelected == 0 ? D3DCOLOR_ARGB(255, 255, 0, 255) :  D3DCOLOR_ARGB(255, 255, 255, 255));
			oss.str("");
			oss << "Physical";
			pBF->Print(oss.str().c_str(), 450, 275 - 60, .7f, m_nSelected == 1 ? D3DCOLOR_ARGB(255, 255, 0, 0) :  D3DCOLOR_ARGB(255, 255, 255, 255));
			oss.str("");
			oss << "Support";
			pBF->Print(oss.str().c_str(), 450, 350 - 60, .7f, m_nSelected == 2 ? D3DCOLOR_ARGB(255, 0, 255, 0) :  D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			std::vector< CAbility* > vSelected;
			if( m_nSelected == 0 )
				vSelected = m_vElemental;
			else if( m_nSelected == 1 )
				vSelected = m_vPhysical;
			else
				vSelected = m_vSupport;
			
			bool bought = false;
			for( unsigned int i = 0; i < vSelected.size(); i++ )
			{

				if( m_nSelected == 0 )
					bought = m_pCustomer->IfBought(m_vElemental[i]);
				else if( m_nSelected == 1 )
					bought = m_pCustomer->IfBought(m_vPhysical[i]);
				else
					bought = m_pCustomer->IfBought(m_vSupport[i]);

				if( i < 6 )
				{
					if( bought == false )
					{
						if( i < 3 )
						{
							if( m_nSelected == 0 )
								pBF->Print("Cost: 100", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
							else if( m_nSelected == 1 )	    
								pBF->Print("Cost: 100", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
							else						   
								pBF->Print("Cost: 100", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
						}
						else if( i < 6 )
						{
							if( m_nSelected == 0 )
								pBF->Print("Cost: 200", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
							else if( m_nSelected == 1 )
								pBF->Print("Cost: 200", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
							else
								pBF->Print("Cost: 200", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
						}
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Purchased", 260 + 15, 160 - 90 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}

					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12, 150 - 90 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12, 150 - 90 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12, 150 - 90 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 200 + 15, 150 - 90 + (55 * i), .7f, .7f);
				}
				else if( i < 9 )
				{
					if( bought == false )
					{
						if( m_nSelected == 0 )
							pBF->Print("Cost: 300", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Cost: 300", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Cost: 300", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Purchased", 510 + 15, 210 - 90 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}

					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12, 200 - 90 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12, 200 - 90 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12, 200 - 90 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 450 + 15, 200 - 90 + (55 * (i-6)), .7f, .7f);
				}
				else
				{
					if( bought == false )
					{
						if( m_nSelected == 0 )
							pBF->Print("Cost: 400", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Cost: 400", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Cost: 400", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Purchased", 500 + 15, 430 - 90, .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
				
					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 525 + 12, 370 - 90 - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 525 + 12, 370 - 90 - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 525 + 12, 370 - 90 - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 525 + 15, 370 - 90, .7f, .7f);
				}
			}
		}
	}
}

CSpellScrollState* CSpellScrollState::GetInstance(void)
{
	static CSpellScrollState s_Instance;
	return &s_Instance;
}

void CSpellScrollState::Initialize( void )
{
	CAbilityManager* pAM = CAbilityManager::GetInstance();
	m_vElemental.push_back(pAM->GetAbility(SP_MAGIC));
	m_vElemental.push_back(pAM->GetAbility(SP_ICEBOLT));
	m_vElemental.push_back(pAM->GetAbility(SP_LIGHTBOLT));
	m_vElemental.push_back(pAM->GetAbility(SP_FIREWEP));
	m_vElemental.push_back(pAM->GetAbility(SP_ICEBLOCK));
	m_vElemental.push_back(pAM->GetAbility(SP_LIGHTSTRIKE));
	m_vElemental.push_back(pAM->GetAbility(SP_FIREBALL));
	m_vElemental.push_back(pAM->GetAbility(SP_ICEAGE));
	m_vElemental.push_back(pAM->GetAbility(SP_LIGHTCHAIN));
	m_vElemental.push_back(pAM->GetAbility(SP_FIRENOVA));

	m_vPhysical.push_back(pAM->GetAbility(SP_HEAVYBLOW));
	m_vPhysical.push_back(pAM->GetAbility(SP_RUSH));
	m_vPhysical.push_back(pAM->GetAbility(SP_SKILLSHOT));
	m_vPhysical.push_back(pAM->GetAbility(SP_CLEAVE));
	m_vPhysical.push_back(pAM->GetAbility(SP_BLADESTORM));
	m_vPhysical.push_back(pAM->GetAbility(SP_EXPSHOT));
	m_vPhysical.push_back(pAM->GetAbility(SP_SWORDDANCE));
	m_vPhysical.push_back(pAM->GetAbility(SP_WHIRLWIND));
	m_vPhysical.push_back(pAM->GetAbility(SP_PSHOT));
	m_vPhysical.push_back(pAM->GetAbility(SP_KILL));

	m_vSupport.push_back(pAM->GetAbility(SP_CARTOGRAPHY));
	m_vSupport.push_back(pAM->GetAbility(SP_HEAL));
	m_vSupport.push_back(pAM->GetAbility(SP_SPEED));
	m_vSupport.push_back(pAM->GetAbility(SP_DESTROYFOREST));
	m_vSupport.push_back(pAM->GetAbility(SP_HEALBURST));
	m_vSupport.push_back(pAM->GetAbility(SP_RALLY));
	m_vSupport.push_back(pAM->GetAbility(SP_PATHFINDER));
	m_vSupport.push_back(pAM->GetAbility(SP_RAISEDEAD));
	m_vSupport.push_back(pAM->GetAbility(SP_SHIELD));
	m_vSupport.push_back(pAM->GetAbility(SP_RAISEMOUNTAIN));

	flipping = false;
	page = 1;
}
