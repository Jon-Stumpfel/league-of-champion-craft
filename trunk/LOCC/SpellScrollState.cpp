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
#include "SoundManager.h"
#include "FloatingText.h"
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
	page = 1;
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
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_bTreeSelect )
			{
				if( m_nSelected == 0 )
					m_nSelected = 3;
				else
					m_nSelected--;
			}
			else
			{
				if( m_nSelected != 3 )
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
							m_nSelectedAbility = 10;
						else
							m_nSelectedAbility--;
					}
				}
				else
				{
					if( m_nSelectedAbility == 0 )
						m_nSelectedAbility = 4;
					else
						m_nSelectedAbility--;
				}
			}
		}
		break;

	case INPUT_DOWN:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_bTreeSelect )
			{
				if( m_nSelected == 3 )
					m_nSelected = 0;
				else
					m_nSelected++;
			}
			else
			{
				if( m_nSelected != 3 )
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
						if( m_nSelectedAbility == 10 )
							m_nSelectedAbility = 6;
						else
							m_nSelectedAbility++;
					}
				}
				else
				{
					if( m_nSelectedAbility == 4 )
						m_nSelectedAbility = 0;
					else
						m_nSelectedAbility++;
				}
			}
		}
		break;

	case INPUT_RIGHT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_nSelected != 3 )
			{
				if( m_nSelectedAbility < 6 )
					m_nSelectedAbility = 6;
				else
					m_nSelectedAbility = 0;
			}
		}
		break;

	case INPUT_LEFT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			if( m_nSelected != 3 )
			{
				if( m_nSelectedAbility < 6 )
					m_nSelectedAbility = 6;
				else
					m_nSelectedAbility = 0;
			}
		}
		break;

	case INPUT_ACCEPT:
		{
			if( m_bTreeSelect )
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("flip")), false, false);
				flipping = true;
				page = 1;
			}
			else
			{
				bool bought = false;

				if( m_nSelected == 0 )
					bought = m_pCustomer->IfBought(m_vElemental[m_nSelectedAbility]);
				else if( m_nSelected == 1 )
					bought = m_pCustomer->IfBought(m_vPhysical[m_nSelectedAbility]);
				else if( m_nSelected == 2 )
					bought = m_pCustomer->IfBought(m_vSupport[m_nSelectedAbility]);
				else
					bought = m_pCustomer->IfBought(m_vEpic[m_nSelectedAbility]);

				if( bought == false )
				{
					if( m_nSelectedAbility < 3 )
					{
						if( m_nSelected != 3 )
						{
							if( m_nExp < 100 )
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
								return;
							}
						
							CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 100);
							CFloatingText::GetInstance()->AddScreenText("-100", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
						}
						else
						{
							if( m_nExp < 500 )
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
								return;
							}
						
							CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 500);
							CFloatingText::GetInstance()->AddScreenText("-500", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
						}
					}
					else if( m_nSelectedAbility < 6 )
					{
						if( m_nSelected != 3 )
						{
							if( m_nExp < 200 )
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
								return;
							}

							CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 200);
							CFloatingText::GetInstance()->AddScreenText("-200", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
						}
						else
						{
							if( m_nExp < 500 )
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
								return;
							}

							CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 500);
							CFloatingText::GetInstance()->AddScreenText("-500", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
						}
					}
					else if( m_nSelectedAbility < 9 )
					{
						if( m_nExp < 300 )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 300);
						CFloatingText::GetInstance()->AddScreenText("-300", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
					}
					else
					{
						if( m_nExp < 400 )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}

						CGameManager::GetInstance()->GetCurrentPlayer()->SetExp(m_nExp - 400);
						CFloatingText::GetInstance()->AddScreenText("-400", Vec2Df(340, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
					}
				}
				else
				{
					if( m_nSelected == 0 )
					{
						if( m_pCustomer->SearchSpells(m_vElemental[m_nSelectedAbility]) )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}
					}
					else if( m_nSelected == 1 )
					{
						if( m_pCustomer->SearchSpells(m_vPhysical[m_nSelectedAbility]) )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}
					}
					else if( m_nSelected == 2 )
					{
						if( m_pCustomer->SearchSpells(m_vSupport[m_nSelectedAbility]) )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}
					}
					else
					{
						if( m_pCustomer->SearchSpells(m_vEpic[m_nSelectedAbility]) )
						{
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("NO")), false, false);
							return;
						}
					}
				}

				CAbility* ability = m_pCustomer->GetSpell(m_nSwap);
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Sword")), false, false);
				if( m_nSelected == 0 )
				{
					if( ability->GetType() != SP_BLANK)
					{
						m_pCustomer->SetCooldown(m_nSwap, m_vElemental[m_nSelectedAbility]->GetCoolDown());
					}
					

					m_pCustomer->SwapSpell(m_vElemental[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vElemental[m_nSelectedAbility]);
				}
				else if( m_nSelected == 1 )
				{
					if( ability->GetType() != SP_BLANK)
					{
						m_pCustomer->SetCooldown(m_nSwap, m_vPhysical[m_nSelectedAbility]->GetCoolDown());
					}

					m_pCustomer->SwapSpell(m_vPhysical[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vPhysical[m_nSelectedAbility]);
				}
				else if( m_nSelected == 2 )
				{
					
					if( ability->GetType() != SP_BLANK)
					{
						m_pCustomer->SetCooldown(m_nSwap, m_vSupport[m_nSelectedAbility]->GetCoolDown());
					}

					m_pCustomer->SwapSpell(m_vSupport[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vSupport[m_nSelectedAbility]);
				}
				else
				{
					if( ability->GetType() != SP_BLANK)
					{
						m_pCustomer->SetCooldown(m_nSwap, m_vEpic[m_nSelectedAbility]->GetCoolDown());
					}

					m_pCustomer->SwapSpell(m_vEpic[m_nSelectedAbility], m_nSwap);
					m_pCustomer->SpellBought(m_vEpic[m_nSelectedAbility]);
				}

				CStateStack::GetInstance()->Pop();
			}
		}
		break;

	case INPUT_CANCEL:
		{
			if( m_bTreeSelect == false )
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("flip")), false, false);
				unflipping = true;
				page = 7;
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
	if ( flipping || unflipping )
	{
		static float time = 0;

		if( time >= .04f )
		{
			if( flipping )
			{
				time = 0;
				page++;
				if( page == 7 )
				{
					flipping = false;
					m_bTreeSelect = !m_bTreeSelect;
				}
			}
			else if( unflipping )
			{
				time = 0;
				page--;
				if( page == 1 )
				{
					unflipping = false;
					m_bTreeSelect = !m_bTreeSelect;
				}
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
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	//pTM->Draw(pGM->GetID(_T("ssbackground")), 0, 0);

	if( page == 1 )
		pTM->Draw(pGM->GetID(_T("Page1")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 2 )
		pTM->Draw(pGM->GetID(_T("Page2")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 3 )
		pTM->Draw(pGM->GetID(_T("Page3")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 4 )
		pTM->Draw(pGM->GetID(_T("Page4")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 5 )
		pTM->Draw(pGM->GetID(_T("Page5")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 6 )
		pTM->Draw(pGM->GetID(_T("Page6")), 175 - 40, -30 + 25, .5f, .5f);
	else if( page == 7 )
		pTM->Draw(pGM->GetID(_T("Page7")), 175 - 40, -30 + 25, .5f, .5f);

	if( flipping == false && unflipping == false )
		pBF->Print("Press Cancel to return", 185, 435, .3f, D3DCOLOR_ARGB(255, 255, 255, 255), 175); 
		

	ostringstream xp;
	xp << "Exp: " << m_nExp;
	pBF->Print(xp.str().c_str(), 10, 20, .4f, D3DCOLOR_ARGB(255, 255, 255, 255));

	if( flipping == false && unflipping == false )
	{
		if( m_bTreeSelect == false )
		{
			pTM->Draw(pGM->GetID(_T("spelldesc")), 145 - 65, 475, .9f, .9f);
			CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			CAbility* selected;
			if( m_nSelected == 0 )
				selected = m_vElemental[m_nSelectedAbility];
			else if( m_nSelected == 1 )
				selected = m_vPhysical[m_nSelectedAbility];
			else if( m_nSelected == 2 )
				selected = m_vSupport[m_nSelectedAbility];
			else 
				selected = m_vEpic[m_nSelectedAbility];


			if( selected->GetIfAttack() )
			pTM->Draw(pGM->GetID(_T("check")), 240 - 50 - 65, 485, .5f, .5f);

			ostringstream tt;
			tt  << selected->GetApCost();
			pBF->Print(tt.str().c_str(), 299 - 50 - 65, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");

			if( selected->GetPhase() == GP_MOVE )
				tt << "Move";
			else
				tt << "Attack";

			pBF->Print(tt.str().c_str(), 278 - 50 - 65, 525, .2f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");

			tt << selected->GetRange();
			pBF->Print(tt.str().c_str(), 373 - 50 - 65, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetCoolDown();
			pBF->Print(tt.str().c_str(), 373 - 50 - 65, 523, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetDamage();
			pBF->Print(tt.str().c_str(), 373 - 50 - 65, 555, .3f, D3DCOLOR_ARGB(255, 255, 255, 255));	

			tt.str("");
			tt << selected->GetName();
			pBF->Print(tt.str().c_str(), 210 - 50 - 65, 556, .2f, D3DCOLOR_ARGB(255, 255, 255, 255));

			tt.str("");
			tt << selected->GetDescription();
			pBF->Print(tt.str().c_str(), 427 - 50 - 65, 493, .3f, D3DCOLOR_ARGB(255, 255, 255, 255), 170);

			int x = 680 - 65, y = 525;
			std::vector< Vec2D > pat = selected->GetPattern();
			std::vector< Vec2D > drawn;

			for( unsigned int i = 0; i < pat.size(); i++ )
			{
				Vec2D tmp;
				tmp.nPosX = x + pat[i].nPosX * 14;
				tmp.nPosY = y + pat[i].nPosY * 14;

				drawn.push_back(tmp);
			}

			CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();

			for( unsigned int i = 0; i < drawn.size(); i++ )
			{
				RECT source = { drawn[i].nPosX, drawn[i].nPosY, drawn[i].nPosX + 14, drawn[i].nPosY + 14 };
				pD3D->DrawRect(source, 0, 255, 0 );
				CGraphicsManager::GetInstance()->DrawWireframeRect(source, 0, 0, 0, true);
			}
		}

		if( m_bTreeSelect )
		{
			ostringstream oss;
			oss << "Ye Olde Table of Contents";
			pBF->Print(oss.str().c_str(), 440 - 40, 50 + 25, .6f, D3DCOLOR_ARGB(255, 255, 255, 255), 240);	
			oss.str("");
			oss << "Elemental";
			pBF->Print(oss.str().c_str(), 450 - 40, 200 - 60 + 25, .7f, m_nSelected == 0 ? D3DCOLOR_ARGB(255, 255, 0, 255) :  D3DCOLOR_ARGB(255, 255, 255, 255));
			oss.str("");
			oss << "Physical";
			pBF->Print(oss.str().c_str(), 450 - 40, 275 - 60 + 25, .7f, m_nSelected == 1 ? D3DCOLOR_ARGB(255, 255, 0, 0) :  D3DCOLOR_ARGB(255, 255, 255, 255));
			oss.str("");
			oss << "Support";
			pBF->Print(oss.str().c_str(), 450 - 40, 350 - 60 + 25, .7f, m_nSelected == 2 ? D3DCOLOR_ARGB(255, 0, 255, 0) :  D3DCOLOR_ARGB(255, 255, 255, 255));
			oss.str("");
			oss << "Epic";
			pBF->Print(oss.str().c_str(), 450 - 40, 425 - 60 + 25, .7f, m_nSelected == 3 ? D3DCOLOR_ARGB(255, 204, 153, 51) :  D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			std::vector< CAbility* > vSelected;
			if( m_nSelected == 0 )
				vSelected = m_vElemental;
			else if( m_nSelected == 1 )
				vSelected = m_vPhysical;
			else if( m_nSelected == 2)
				vSelected = m_vSupport;
			else
				vSelected = m_vEpic;
			
			bool bought = false;
			for( unsigned int i = 0; i < vSelected.size(); i++ )
			{

				if( m_nSelected == 0 )
					bought = m_pCustomer->IfBought(m_vElemental[i]);
				else if( m_nSelected == 1 )
					bought = m_pCustomer->IfBought(m_vPhysical[i]);
				else if( m_nSelected == 2 )
					bought = m_pCustomer->IfBought(m_vSupport[i]);
				else
					bought = m_pCustomer->IfBought(m_vEpic[i]);

				if( i < 6 )
				{
					if( bought == false )
					{
						if( i < 3 )
						{
							if( m_nSelected == 0 )
								pBF->Print("Cost: 100", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
							else if( m_nSelected == 1 )	    
								pBF->Print("Cost: 100", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
							else if( m_nSelected == 2 )				   
								pBF->Print("Cost: 100", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
							else
								pBF->Print("Cost: 500", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,204, 153, 51));
						}
						else if( i < 6 )
						{
							if( m_nSelected == 0 )
								pBF->Print("Cost: 200", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
							else if( m_nSelected == 1 )
								pBF->Print("Cost: 200", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
							else if( m_nSelected == 2 )
								pBF->Print("Cost: 200", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
							else
								pBF->Print("Cost: 500", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,204, 153, 51));
						}
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else if( m_nSelected == 2 )
							pBF->Print("Purchased", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,100,255,100));
						else
							pBF->Print("Purchased", 260 + 15 - 40, 160 - 90 + 25 + (55 * i), .3f, D3DCOLOR_ARGB(255,204, 153, 51));
					}

					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12 - 40, 150 - 90 + 25 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12 - 40, 150 - 90 + 25 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else if( m_nSelected == 2 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12 - 40, 150 - 90 + 25 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 200 + 12 - 40, 150 - 90 + 25 + (55 * i) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 204, 153, 51));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 200 + 15 - 40, 150 - 90 + 25 + (55 * i), .7f, .7f);
				}
				else if( i < 9 )
				{
					if( bought == false )
					{
						if( m_nSelected == 0 )
							pBF->Print("Cost: 300", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Cost: 300", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Cost: 300", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Purchased", 510 + 15 - 40, 210 - 90 + 25 + (55 * (i-6)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}

					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 200 - 90 + 25 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 200 - 90 + 25 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 200 - 90 + 25 + (55 * (i-6)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 450 + 15 - 40, 200 - 90 + 25 + (55 * (i-6)), .7f, .7f);
				}
				else
				{
					if( bought == false )
					{
						if( m_nSelected == 0 )
							pBF->Print("Cost: 400", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Cost: 400", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Cost: 400", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
					else
					{
						if( m_nSelected == 0 )
							pBF->Print("Purchased", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,255,0,255));
						else if( m_nSelected == 1 )
							pBF->Print("Purchased", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,255,100,100));
						else
							pBF->Print("Purchased", 510 + 15 - 40, 380 - 90 + 25 + (55 * (i-9)), .3f, D3DCOLOR_ARGB(255,100,255,100));
					}
				
					if( i == m_nSelectedAbility )
					{
						if( m_nSelected == 0 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 370 - 90 + 25 + (55 * (i-9)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 255));
						else if( m_nSelected == 1 )
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 370 - 90 + 25 + (55 * (i-9)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
						else
							pTM->Draw(pGM->GetID(_T("scrollselect")), 450 + 12 - 40, 370 - 90 + 25 + (55 * (i-9)) - 3, .7f, .7f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 0, 255, 0));
					}

					pTM->Draw(vSelected[i]->GetIconID(), 450 + 15 - 40, 370 - 90 + 25 + (55 * (i-9)), .7f, .7f);
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
	m_vElemental.push_back(pAM->GetAbility(SP_ENCASE));

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
	m_vPhysical.push_back(pAM->GetAbility(SP_DEATH));

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
	m_vSupport.push_back(pAM->GetAbility(SP_FORT));

	m_vEpic.push_back(pAM->GetAbility(SP_MIND));
	m_vEpic.push_back(pAM->GetAbility(SP_TELE));
	m_vEpic.push_back(pAM->GetAbility(SP_MASSRAISE));
	m_vEpic.push_back(pAM->GetAbility(SP_VAMP));
	m_vEpic.push_back(pAM->GetAbility(SP_SAC));


	flipping = false;
	page = 1;
}
