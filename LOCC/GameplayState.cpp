#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"
#include "AddResourceMessage.h"
#include "DeSpawnUnitMessage.h"
#include "AIManager.h"
#include "Unit.h"
#include "ParticleManager.h"
#include "Player.h"
#include "TileManager.h"
#include "Tile.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "StateStack.h"
#include "PauseState.h"
#include "Hero.h"
#include "BitmapFont.h"
#include "FloatingText.h"
#include "SoundManager.h"
#include "CoinToss.h"
//CGameplayState* CGameplayState::s_Instance = nullptr;

CGameplayState::CGameplayState(void)
{
}

CGameplayState::~CGameplayState(void)
{
	m_pBitmapFont = nullptr;
	delete m_pBitmapFont;
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState s_Instance;
	return &s_Instance;
}

void CGameplayState::Enter(void)
{
	// test stuff
	CAbilityManager* pAM = CAbilityManager::GetInstance();

	//CGameManager::GetInstance()->NewGame();

	m_pBitmapFont = new CBitmapFont();
	CGameManager* pGM = CGameManager::GetInstance();
	CParticleManager* pPM = CParticleManager::GetInstance();

	CAnimationManager::GetInstance()->Load("Assets/Animations/TestAnimation.xml");

	SetRect(&rCamRect, 0, 0, 
		CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth, CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight);

	// INITIALIZATION SETUP

	m_bIsMoving = false;
	m_bIsTargeting = false;
	m_pSelectedUnit = nullptr;
	m_pHighlightedUnit = nullptr;
	//	m_CameraPos = Vec2D(0, 0);
	m_SelectionPos = Vec2D(0, 0);
	m_bLerpingX = false;
	m_bIsHighlighting = false;
	m_nSelectedAbility = 0;
	m_bSelectChampionAbility = false;
	m_bShowSpellPanel = false;
	m_nSelectedSpell = 0;
	m_nSpellPanelOffsetY = CGame::GetInstance()->GetWindowHeight();
	m_nSpellPanelOffsetYMAX =  CGame::GetInstance()->GetWindowHeight() - 120;
	m_nCardOffsetX = CGame::GetInstance()->GetWindowWidth();
	m_nCardOffsetMaxX = CGame::GetInstance()->GetWindowWidth() - 230;
	m_nTooltipOffsetX = -50;
	m_nTooltipOffsetMaxX = 0;
	pGM;
	SnapToPosition(CGameManager::GetInstance()->GetChampion(0)->GetPos());

}

int CGameplayState::GetCamOffsetX(void)
{
	return m_currCamPixelPos.nPosX - (4 * nFakeTileWidth);
	//return rCamRect.left * nFakeTileWidth;
}
int CGameplayState::GetCamOffsetY(void)
{
	return m_currCamPixelPos.nPosY - (2 * nFakeTileHeight);
	//return rCamRect.top * nFakeTileHeight;
}
void CGameplayState::Exit(void)
{
	CMessageSystem::GetInstance()->ProcessMessages();
	CAnimationManager::GetInstance()->Shutdown();
	delete m_pBitmapFont;
}

// Snaps the camera to the passed in Vec2D. This is used for moving the camera to the player's hero at turn start
// but could be used for anything. Just pass a pUnit in and the camera and selection cursor shifts to that unit.
void CGameplayState::SnapToPosition(Vec2D pPos)
{
	int nSelX = pPos.nPosX - m_SelectionPos.nPosX;
	int nSelY = pPos.nPosY - m_SelectionPos.nPosY;

	MoveCursor(nSelX, nSelY, false);

	//m_oldCamPixelPos = m_currCamPixelPos;
	int x = (nFakeTileWidth / 2 * m_SelectionPos.nPosX) - (nFakeTileHeight / 2 * m_SelectionPos.nPosY);
	int y = (nFakeTileWidth / 2 * m_SelectionPos.nPosX) + (nFakeTileHeight  / 2 * m_SelectionPos.nPosY);
	//m_newCamPixelPos.nPosX = x;
	//m_newCamPixelPos.nPosY = y;
	//m_bLerpingX = true;


	m_oldCamPixelPos = m_currCamPixelPos;
	m_newCamPixelPos = Vec2D(x, y);
	m_fLerpPercent = 1.0f;
	m_bLerpingX = true;
	//MoveCamera(nDesiredCamX, nDesiredCamY );
}

// Moves the selection cursor by deltaX and deltaY values. Lock when true locks the camera from moving, otherwise
// the camera will stick with the cursor should it go off screen. Lock defaults to true
void CGameplayState::MoveCursor(int dX, int dY, bool lock)
{
	m_SelectionPos.nPosX += dX;
	m_SelectionPos.nPosY += dY;

	if (CGameManager::GetInstance()->FindUnit(m_SelectionPos))
	{
		m_bIsHighlighting = true;
		m_pHighlightedUnit = CGameManager::GetInstance()->FindUnit(m_SelectionPos);
	}
	else
		m_bIsHighlighting = false;

	// If we're in moving mode, then calculate the best path
	if (m_bIsMoving)
	{
		CTileManager* pTM = CTileManager::GetInstance();
		CTile* pStartTile = pTM->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY);
		CTile* pTargetTile = pTM->GetTile(m_SelectionPos.nPosX, m_SelectionPos.nPosY);

		CalculateMove(pStartTile, pTargetTile);
	}

	// This locks camera to cursor position
	if (lock == true)
	{
		if (m_CameraPos.nPosX < m_SelectionPos.nPosX)
		{
			SnapToPosition(m_SelectionPos);
			//int n = m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth);
			//int nDistance = m_SelectionPos.nPosX - n;
			//MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosX > m_SelectionPos.nPosX)
		{
			SnapToPosition(m_SelectionPos);

			//int n = m_CameraPos.nPosX;
			//int nDistance = m_SelectionPos.nPosX - n;
			//MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosY < m_SelectionPos.nPosY)
		{
			SnapToPosition(m_SelectionPos);

			//int n = m_CameraPos.nPosY + int(((CGame::GetInstance()->GetWindowHeight() * 0.8f)) / nFakeTileHeight);
			//int nDistance = m_SelectionPos.nPosY - n;
			//MoveCamera(0, nDistance);
		}
		if (m_CameraPos.nPosY > m_SelectionPos.nPosY)
		{
			SnapToPosition(m_SelectionPos);

			//int n = m_CameraPos.nPosY;
			//int nDistance = m_SelectionPos.nPosY - n;
			//MoveCamera(0, nDistance);
		}
	}
}

static bool CloseEnough(int n1, int n2)
{
	if (abs(n1 - n2) < 10)
		return true;
	else
		return false;
}

// Lerping helper function
Vec2D Lerp(Vec2D start, Vec2D end, float fPercent)
{
	Vec2D lerp;
	lerp.nPosX = int(end.nPosX + fPercent*(start.nPosX - end.nPosX));
	lerp.nPosY = int(end.nPosY + fPercent*(start.nPosY - end.nPosY));
	return lerp;
}
// Smoothly lerps the camera from it's current position to the destination position
void CGameplayState::LerpCamera(float fElapsedTime)
{
	if (m_bLerpingX)
	{
		if (m_currCamPixelPos.nPosY > 2000)
		{
			int x = 9;
		}
		m_currCamPixelPos = Lerp(m_oldCamPixelPos, m_newCamPixelPos, m_fLerpPercent);

		m_fLerpPercent -= nCameraScrollSpeed * fElapsedTime;
	}
	if (m_fLerpPercent < 0)
	{
		m_bLerpingX = false;
		m_oldCamPixelPos = m_newCamPixelPos;
		m_fLerpPercent = 0.0f;
	}
}

// Moves the camera by dX and dY values (delta)
void CGameplayState::MoveCamera(int dX, int dY)
{
	m_oldCamPixelPos.nPosX = m_currCamPixelPos.nPosX;
	m_oldCamPixelPos.nPosY = m_currCamPixelPos.nPosY;
	if (dX > 0)
		m_newCamPixelPos.nPosX = m_currCamPixelPos.nPosX  + 10;
	else if (dX < 0)
		m_newCamPixelPos.nPosX = m_currCamPixelPos.nPosX  -  10;
	if (dY > 0)
		m_newCamPixelPos.nPosY =  m_currCamPixelPos.nPosY  + 10;
	else if (dY < 0)
		m_newCamPixelPos.nPosY =  m_currCamPixelPos.nPosY  - 10;
	m_bLerpingX = true;
}

void CGameplayState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_UP:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving) && (!m_bIsTargeting))
			{
				// do nothing, up arrow does nothing with a unit selected
			}
			else
			{
				MoveCursor(0, -1);
			}
		}
		break;
	case INPUT_LEFT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)&& (!m_bIsTargeting))// we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (ShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell--;
				//	if (m_nSelectedChampSpell < 0)
				//		m_nSelectedChampSpell = 3;
				//}
				//else
				{
					if (m_bSelectChampionAbility)
					{
						m_nSelectedSpell--;
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						if (m_nSelectedSpell < 0)
						{
							if (pHero->GetNumSpells() == 0)
								m_nSelectedSpell = 0;
							else
								m_nSelectedSpell = pHero->GetNumSpells()-1;
						}
					}
					else
					{
						// Champion ability is not pulled up, so just move the cursor on the main panel
						m_nSelectedAbility--;
						if (m_nSelectedAbility < 0)
							m_nSelectedAbility = 2;
					}
				}
			}
			else
				MoveCursor(-1, 0);
		}
		break;
	case INPUT_RIGHT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)&& (!m_bIsTargeting)) // we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (m_bShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell++;
				//	if (m_nSelectedChampSpell > 3)
				//		m_nSelectedChampSpell = 0;
				//}
				//else
				{
					if (m_bSelectChampionAbility)
					{
						m_nSelectedSpell++;
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						if (m_nSelectedSpell >= (int)pHero->GetNumSpells())
							m_nSelectedSpell = 0;
					}
					else
					{
						// Champion ability is not pulled up, so just move the cursor on the main panel
						m_nSelectedAbility++;
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						if (m_nSelectedAbility > 2)
							m_nSelectedAbility = 0;
					}
				}
			}
			else
				MoveCursor(1, 0);
		}
		break;
	case INPUT_DOWN:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)&& (!m_bIsTargeting)) // we have a unit selected
			{
				// do nothing! Up arrow does nada;
			}
			else
				MoveCursor(0, 1);
		}
		break;
	case INPUT_ACCEPT:
		{
			if (m_pSelectedUnit == nullptr)
			{
				// Stop them from selecting a unit that is not theirs
				m_pSelectedUnit = CGameManager::GetInstance()->FindUnit(m_SelectionPos);
				if (m_pSelectedUnit != nullptr)
				{
					int nUnitPlayerID = m_pSelectedUnit->GetPlayerID();
					CPlayer* player = CGameManager::GetInstance()->GetCurrentPlayer();
					int nPlayerPlayerID = player->GetPlayerID();

					if (nUnitPlayerID != nPlayerPlayerID)
					{
						m_pSelectedUnit = nullptr;
					}
				}
			}
			else
			{
				if (m_bIsMoving)
				{
					MoveToTile(m_SelectionPos);
				}
				else if (m_bIsTargeting)
				{
					if (m_bSelectChampionAbility)
					{
						m_pTargetedTile = CTileManager::GetInstance()->GetTile(m_SelectionPos.nPosX, m_SelectionPos.nPosY);
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						UseAbility(pHero->GetSpell(m_nSelectedSpell));
					}
					else
					{
						m_pTargetedTile = CTileManager::GetInstance()->GetTile(m_SelectionPos.nPosX, m_SelectionPos.nPosY);
						if (m_pTargetedTile != nullptr)
							UseAbility(m_pSelectedUnit->GetAbility(m_nSelectedAbility));
					}
				}
				else
				{
					if (m_bSelectChampionAbility)
					{
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						//if the spell is in cooldown you can't use it-DG
						if (pHero->GetCooldown(m_nSelectedSpell)==0)
						{
							UseAbility(pHero->GetSpell(m_nSelectedSpell));							
						}
					}
					else
					{
						UseAbility(m_pSelectedUnit->GetAbility(m_nSelectedAbility));
					}
				}
			}
		}
		break;
	case INPUT_CANCEL:
		{
			if (m_pSelectedUnit == nullptr)
				CStateStack::GetInstance()->Push(CPauseState::GetInstance());
			else if (m_pSelectedUnit != nullptr)
			{
				if (m_bIsMoving)
				{
					m_bIsMoving = false;
					m_vWaypoints.clear();
					SnapToPosition(m_pSelectedUnit->GetPos());
				}
				else if (m_bIsTargeting)
				{
					m_bIsTargeting = false;
					SnapToPosition(m_pSelectedUnit->GetPos());
				}
				else if (m_bSelectChampionAbility)
				{
					m_bSelectChampionAbility = false;
					m_bShowSpellPanel = false;
					m_nSelectedSpell = 0;
				}
				else
					ClearSelections();
			}


		}
		break;
	case INPUT_START:
		{
			CGameManager::GetInstance()->NextPhase();
		}
		break;
	case INPUT_SELECT:
		{
			// spell scroll state here
		}
		break;
	case INPUT_CAM_UP:
		MoveCamera(0, -1);
		break;
	case INPUT_CAM_DOWN:
		MoveCamera(0, 1);
		break;
	case INPUT_CAM_LEFT:
		MoveCamera(-1, 0);
		break;
	case INPUT_CAM_RIGHT:
		MoveCamera(1, 0);
		break;
	case INPUT_AI_CLEAR: // AI specific to clear selected so we dont fudge stuff up
		ClearSelections();
		break;
	case INPUT_AI_SELECTABILITY_1:
		m_nSelectedAbility = 0;
		break;
	case INPUT_AI_SELECTABILITY_2:
		m_nSelectedAbility = 1;
		break;
	case INPUT_AI_SELECTABILITY_3:
		m_nSelectedAbility = 2;
		break;
	case INPUT_AI_CHAMPSPELL:
		m_bSelectChampionAbility = true;
		break;
	case INPUT_AI_SELECTSPELL1:
		m_nSelectedSpell = 0;
		break;
	case INPUT_AI_SELECTSPELL2:
		m_nSelectedSpell = 1;
		break;
	case INPUT_AI_SELECTSPELL3:
		m_nSelectedSpell = 2;
		break;
	case INPUT_AI_SELECTSPELL4:
		m_nSelectedSpell = 3;
		break;
	default:
		break;
	}
}

void CGameplayState::UseAbility(CAbility* ability)
{
	CSoundManager* pSM = CSoundManager::GetInstance();
	CHero* Champ = nullptr;

	if (ability == nullptr)
		return;

	if (ability->m_nNumTargets == -1) // champion spell panel
	{
		m_bSelectChampionAbility = true;
		return;
	}

	if( ability->GetType() == SP_VOLLEY )
	{
		if( m_pSelectedUnit->GetTilesMoved() != 0 )
			return;
	}

	if (ability->m_nPhase != CGameManager::GetInstance()->GetCurrentPhase())
		return;

	// They used the movement ability
	if (m_pSelectedUnit->GetHasAttacked())
		return;

	if (ability->GetType() == SP_MOVE)
	{
		if( m_pSelectedUnit->GetEffect(SP_STAND) == false || m_pSelectedUnit->GetEffect(SP_LIGHTSTRIKE) == false )
		{
			m_bIsMoving = true;
			return;
		}
		else 
			return;
	}
	else
	{
		if (ability->m_nNumTargets == 1)
		{
			if ( m_pTargetedTile == nullptr && m_bIsTargeting == false)
			{
				m_bIsTargeting = true;
				return;
			}
			else if (m_bIsTargeting == true && m_pTargetedTile == nullptr)
			{
				return;
			}
			else if (m_bIsTargeting == true && m_pTargetedTile != nullptr)
			{
				// not enough AP to cast!
				if (CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() < ability->GetApCost()) 
				{
					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					return;
				}
				if (m_pSelectedUnit->GetHasAttacked())
				{
					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					return;
				}

				if( m_pSelectedUnit->GetType() == UT_HERO )
				{
					Champ = dynamic_cast<CHero*>(m_pSelectedUnit);
					//CoolDown Check here
					if (Champ->GetCooldown(m_nSelectedSpell)<0)
						return;
				}

				if( ability->GetType() == SP_CHARGE )
				{
					std::vector<Vec2D> vec = ability->GetPattern();
					for( unsigned int i = vec.size()-1; i > 0; i-- )
					{
						Vec2D t;
						t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
						t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
						Vec2D tmp = TranslateToPixel(t);
						tmp.nPosX += 65;
						tmp.nPosY += 5;
						CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp);
						
						if( m_pTargetedTile->GetPosition() == vec[i] )
							break;
					}
				}
				else
				{
					std::vector<Vec2D> vec = ability->GetPattern();
					for( unsigned int i = 0; i < vec.size(); i++ )
					{
						Vec2D t;
						t.nPosX = vec[i].nPosX + m_pTargetedTile->GetPosition().nPosX;
						t.nPosY = vec[i].nPosY + m_pTargetedTile->GetPosition().nPosY;
						Vec2D tmp = TranslateToPixel(t);
						tmp.nPosX;
						tmp.nPosY;
						CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp);
						//if( ability->GetParticleType() == PT_BLOOD )
							//CParticleManager::GetInstance()->LoadParticles(PT_OBLOOD, tmp);
					}
				}
				// cast the spell!
				if( ability->GetType() == SP_SPAWNARCHER || ability->GetType() == SP_SPAWNSWORD || ability->GetType() == SP_SPAWNCALV )
				{
					int nDistance = (int)(abs(double(m_pSelectedUnit->GetPos().nPosX - m_pTargetedTile->GetPosition().nPosX)) +
						abs(double(m_pSelectedUnit->GetPos().nPosY - m_pTargetedTile->GetPosition().nPosY)));
					if (nDistance <= ability->GetRange() && !(m_pTargetedTile->GetPosition() == m_pSelectedUnit->GetPos()))
					{
						int cur = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();

						if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()) != nullptr )
							return;

						CSpawnUnitMessage* msg;
						switch(ability->GetType())
						{
						case SP_SPAWNARCHER:
							{
								CGameManager* pGM = CGameManager::GetInstance();
								if( pGM->GetCurrentPlayer()->GetPopCap() < pGM->GetCurrentPlayer()->GetMaxPopCap() )
								{
									if( pGM->GetCurrentPlayer()->GetMetal() >= 5 )
									{
										if( pGM->GetCurrentPlayer()->GetWood() >= 15 )
										{	
											//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap() + 1 );
											pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 5 );
											pGM->GetCurrentPlayer()->SetWood(pGM->GetCurrentPlayer()->GetWood() - 15 );

											// Stats saving!
											pGM->GetCurrentPlayer()->GetStats()->nPlayerMetalSpent+=5;
											pGM->GetCurrentPlayer()->GetStats()->nPlayerWoodSpent+=15;

										}
										else
											return;
									}
									else
										return;
								}
								else
									return;

								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ARCHER, 2, false, 12);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ARCHER, 0, false, 12);

								CMessageSystem::GetInstance()->SendMessageW(msg);
							}
							break;

						case SP_SPAWNSWORD:
							{
								CGameManager* pGM = CGameManager::GetInstance();
								if( pGM->GetCurrentPlayer()->GetPopCap() < pGM->GetCurrentPlayer()->GetMaxPopCap() )
								{
									if( pGM->GetCurrentPlayer()->GetMetal() >= 20 )
									{
										//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap()+1);
										pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 20 );
											// Stats saving!
											pGM->GetCurrentPlayer()->GetStats()->nPlayerWoodSpent+=20;
									}
									else
										return;
								}
								else
									return;

								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_SWORDSMAN, 2, false, 20);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_SWORDSMAN, 0, false, 20);
								CMessageSystem::GetInstance()->SendMessageW(msg);
							}
							break;

						case SP_SPAWNCALV:
							{
								CGameManager* pGM = CGameManager::GetInstance();
								if( pGM->GetCurrentPlayer()->GetPopCap() < pGM->GetCurrentPlayer()->GetMaxPopCap() )
								{
									if( pGM->GetCurrentPlayer()->GetMetal() >= 10 )
									{
										if( pGM->GetCurrentPlayer()->GetWood() >= 10 )
										{	
											//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap()+1);
											pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 10 );
											pGM->GetCurrentPlayer()->SetWood(pGM->GetCurrentPlayer()->GetWood() - 10 );
											// Stats saving!
											pGM->GetCurrentPlayer()->GetStats()->nPlayerMetalSpent+=10;
											pGM->GetCurrentPlayer()->GetStats()->nPlayerWoodSpent+=10;
										}
										else
											return;
									}
									else
										return;
								}
								else 
									return;

								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_CAVALRY, 2, false, 22);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_CAVALRY, 0, false, 22);
								CMessageSystem::GetInstance()->SendMessageW(msg);
							}
							break;
						}

						int ap = CGameManager::GetInstance()->GetCurrentPlayer()->GetAP();
						if(  ap == 0 )
							return;
						else
							CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(ap - ability->GetApCost());
									// STATS SAVING
						CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;
						m_pTargetedTile = nullptr;
						m_pSelectedUnit = nullptr;
						m_bIsTargeting = false;
					}
				}
				else if (ability->GetType() == SP_MELEEATTACK || ability->GetType() == SP_ARCHERRANGEDATTACK)
				{
					int nDistance = (int)(abs(double(m_pSelectedUnit->GetPos().nPosX - m_pTargetedTile->GetPosition().nPosX)) +
						abs(double(m_pSelectedUnit->GetPos().nPosY - m_pTargetedTile->GetPosition().nPosY)));
					if (nDistance <= m_pSelectedUnit->GetRange())
					{
						CUnit* pUnit = CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition());
						if (pUnit != nullptr)
						{
							if (ability->GetType() == SP_ARCHERRANGEDATTACK)
							{
								if (!pUnit->CheckDodged())
								{
									if( pUnit->GetShielded() == false )
									{
										// STATS SAVING
										CPlayer* pSavePlayer = CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID());
										switch (pUnit->GetType())
										{
										case UT_ARCHER:
											pSavePlayer->GetStats()->nArcherDamageDone+=m_pSelectedUnit->GetAttack();
											break;
										case UT_SWORDSMAN:
											pSavePlayer->GetStats()->nSwordsmanDamageDone+=m_pSelectedUnit->GetAttack();
											break;
										case UT_CAVALRY:
											pSavePlayer->GetStats()->nCalvaryDamageDone+=m_pSelectedUnit->GetAttack();
											break;
										case UT_HERO:
											pSavePlayer->GetStats()->nChampionDamageDone+=m_pSelectedUnit->GetAttack();
											break;
										}

										pUnit->SetHP(pUnit->GetHP() - m_pSelectedUnit->GetAttack());
										pSM->Play(pSM->GetID(_T("hurt")), false, false);
										Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
										std::ostringstream oss;
										oss << m_pSelectedUnit->GetAttack();
										CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
											Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 0, 0));
									}
									else
									{
										pUnit->RemoveEffect(SP_SHIELD);
										Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
										std::ostringstream oss;
										oss << "Shielded!";
										CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX, (float)pixelPos.nPosY), 
											Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
									}
								}
								else
								{
									// miss!
								}


							}
							else
							{
								if( pUnit->GetShielded() == false )
								{
										// STATS SAVING
									CPlayer* pSavePlayer = CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID());
									switch (pUnit->GetType())
									{
									case UT_ARCHER:
										pSavePlayer->GetStats()->nArcherDamageDone+=m_pSelectedUnit->GetAttack();
										break;
									case UT_SWORDSMAN:
										pSavePlayer->GetStats()->nSwordsmanDamageDone+=m_pSelectedUnit->GetAttack();
										break;
									case UT_CAVALRY:
										pSavePlayer->GetStats()->nCalvaryDamageDone+=m_pSelectedUnit->GetAttack();
										break;
									case UT_HERO:
										pSavePlayer->GetStats()->nChampionDamageDone+=m_pSelectedUnit->GetAttack();
										break;
										}
									pUnit->SetHP(pUnit->GetHP() - m_pSelectedUnit->GetAttack());
									Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
									std::ostringstream oss;
									oss << m_pSelectedUnit->GetAttack();
									pSM->Play(pSM->GetID(_T("hurt")), false, false);
									CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
										Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 0, 0));
								}
								else
								{
									pUnit->RemoveEffect(SP_SHIELD);
									//	pUnit->SetShielded(0);
									Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
									std::ostringstream oss;
									oss << "Shielded!";
									CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX, (float)pixelPos.nPosY), 
										Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
								}
							}
						}
						// STATS SAVING
						CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;
						CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() - ability->m_nAPCost);
						//ADD BASIC ATTACK ANIMATION HERE
						if (ability->m_bIsAttack)
							m_pSelectedUnit->SetHasAttacked(true);
						m_bIsTargeting = false;
						m_pTargetedTile = nullptr;
						m_pSelectedUnit = nullptr;
					}
				}
				else
				{
					if( ability->GetType() == SP_CHARGE )
					{
						if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()) != nullptr )
							return;
					}

					CAbilityManager* pAM = CAbilityManager::GetInstance();

					if( ability->GetType() == SP_CHARGE )
					{
						CTileManager* pTM = CTileManager::GetInstance();
						m_bIsMoving = true;
						m_pSelectedUnit->AddWaypoint(m_pTargetedTile);
						pAM->UseAbility(ability, pTM->GetTile( m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY) , m_pSelectedUnit, m_pTargetedTile);
					}
					else
						pAM->UseAbility(ability, m_pTargetedTile, m_pSelectedUnit);

					// STATS SAVING
					CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;
					CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() - ability->m_nAPCost);

					if (ability->m_bIsAttack)
						m_pSelectedUnit->SetHasAttacked(true);

					if( m_pSelectedUnit->GetType() == UT_HERO && Champ != nullptr )
						Champ->SetCooldown(m_nSelectedSpell, ability->GetCoolDown());

					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					m_pSelectedUnit = nullptr;
					m_bSelectChampionAbility = false;
				}
				ClearSelections();
			}
		}
		else if (ability->m_nNumTargets == 0) // AOE spell
		{
			std::vector<Vec2D> vec = ability->GetPattern();
			for( unsigned int i = 0; i < vec.size(); i++ )
			{
				Vec2D t;
				t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
				t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
				Vec2D tmp = TranslateToPixel(t);
				tmp.nPosX += 65;
				tmp.nPosY += 5;
				CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp);
			}
			CAbilityManager* pAM = CAbilityManager::GetInstance();
			pAM->UseAbility(ability, CTileManager::GetInstance()->GetTile(m_pSelectedUnit->GetPos().nPosX, 
				m_pSelectedUnit->GetPos().nPosY), m_pSelectedUnit);

			CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() - ability->m_nAPCost);

			// STATS SAVING
			CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;

			if (ability->m_bIsAttack)
				m_pSelectedUnit->SetHasAttacked(true);

			if( m_pSelectedUnit->GetType() == UT_HERO && Champ != nullptr )
				Champ->SetCooldown(m_nSelectedSpell, ability->GetCoolDown());

			m_bIsTargeting = false;
			m_pTargetedTile = nullptr;
			m_pSelectedUnit = nullptr;
			m_bSelectChampionAbility = false;
		}
	}		
}

// Attempts to move the selectedUnit to the tile at position nTilePosition
void CGameplayState::MoveToTile(Vec2D nTilePosition)
{
	// Cheapest movement algorithm hooray
	CTileManager* pTM = CTileManager::GetInstance();
	CTile* pStartTile = pTM->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY);
	CTile* pTargetTile = pTM->GetTile(nTilePosition.nPosX, nTilePosition.nPosY);

	// Check if where we are going to is passable and occupied, if so, return out of function
	if (pTargetTile == nullptr)
		return;
	if (pTargetTile->GetIfPassable() || pTargetTile->GetIfOccupied())
	{
		return;
	}

	// Check if the unit has already moved a number of tiles this turn up to their speed, if so, return out and clear stuff
	if (m_pSelectedUnit->GetTilesMoved() == m_pSelectedUnit->GetSpeed())
	{
		m_bIsMoving = false;
		m_pSelectedUnit = nullptr;
		m_vWaypoints.clear();
		// error sound?
		return;
	}


	// Calculate total number of moves this will take as well as total AP cost for the path. If the path ends
	// up taking us past our speed (or available tiles left to move), break out early and only count what we will make 
	// it to
	int nTotalAPCost = 0;
	int nMoveCount = 0;
	for (int i = m_vWaypoints.size() - 1; i >= 0 ; --i)
	{
		if (m_pSelectedUnit->GetFreeMove())
		{
			nTotalAPCost += 1;
		}
		else
			nTotalAPCost+= m_vWaypoints[i]->GetAPCost();

		nMoveCount++;
		if (nMoveCount == (m_pSelectedUnit->GetSpeed() - m_pSelectedUnit->GetTilesMoved()))
		{
			break;
		}
	}

	// If the total AP cost of the move is more than we have, return out. We can't afford to move
	if (nTotalAPCost > CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP())
	{
		// play error sound?
		return;
	}
	// If we're here, we're movin. Subtract the cost of the move from the player's AP
	CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->SetAP(
		CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP() - nTotalAPCost);

	// STATS SAVING
	CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetStats()->nPlayerAPSpent += nTotalAPCost;

	// Add the tile waypoints to the unit so that he can slide along them neatly
	for (unsigned int i = 0; i < m_vWaypoints.size(); ++i)
	{
		m_pSelectedUnit->AddWaypoint(m_vWaypoints[i]);
	}
	// After we hit enter we want to cancel and clear, either we're moving or we're not.


	if (pTargetTile->GetIfResourceTile())
	{
		if (!pTargetTile->GetIfCapturing())
		{
			pTargetTile->SetIfCapturing(true);
			pTargetTile->SetPlayerID( m_pSelectedUnit->GetPlayerID());
		}
	}
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_vWaypoints.clear();
	return;
}

// Uses A* pathfinding algorithm to find a cheap route from startTile to targetTile
bool CGameplayState::CalculateMove(CTile* startTile, CTile* targetTile)
{
	// If either of the tiles are null or we can't move into the last tile, don't calculate anything.
	if (startTile == nullptr || targetTile == nullptr || targetTile->GetIfOccupied() || targetTile->GetIfPassable())
		return false;

	// Create our lists that we will work inside and add the initial tile to the closed list
	CTileManager* pTM = CTileManager::GetInstance();
	std::list<ASNode*> openList;
	std::list<ASNode*> closedList;
	typedef std::list<ASNode*>::iterator closedIter;
	m_vWaypoints.clear();
	ASNode* n = new ASNode();
	n->pTile = startTile;
	n->nCost = 0;

	int safeCheck = 0;
	closedList.push_back(n);
	openList.remove(n);

	int nEstimatedTileCost = 3;

	while (true && (safeCheck < 1000))
	{
		// This loop will go through and check all tiles adjacent to our active tile. If they are legit tiles
		// I.E not null, are passable and are not occupied, then we add them to our openList of available tiles to move
		// we calculate the estimated cost on how much that tile will take us to get to our target if we go that way
		// Once we added all adjacent tiles, we find which of those tiles on the openList has the cheapest estimated route
		// we make the cheapest one our active tile, then repeat the process adding the tiles adjacent to the active tile.
		// We do this until we find our target tile and when we do, we break out of the loop.
		// We go to our targetTile node and see which tile we had set as it's parent in the path, then go to that. Then we loop
		// through parents until we get back to the start and we then have our path

		if (n->pTile->GetPosition().nPosY -1 >= 0) // check north
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY -1);
			if (pTestTile == nullptr)
			{
				int x = 9;
			}
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			bool pPass = !(pTestTile->GetIfPassable());
			bool pOcc = !(pTestTile->GetIfOccupied());
			if (iter == closedList.end() && !(pTestTile->GetIfPassable()) && !(pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY -1);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosY + 1 < pTM->GetNumColumns()) // check south
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY + 1);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY +1);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosX -1 >= 0) // check West
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX - 1, n->pTile->GetPosition().nPosY);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX -1, n->pTile->GetPosition().nPosY);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosX +1 < pTM->GetNumRows()) // check east
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX + 1, n->pTile->GetPosition().nPosY);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX + 1, n->pTile->GetPosition().nPosY);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}

		// find which one in the open list has the cheapest cost and make it our active tile, and add it to the closed list
		ASNode* lowestF = nullptr;
		int nLowestF = INT_MAX;
		std::list<ASNode*>::iterator listIter;
		for (listIter = openList.begin(); listIter != openList.end(); ++listIter)
		{
			if ((*listIter)->nF < nLowestF)
			{
				nLowestF = (*listIter)->nF;
				lowestF = (*listIter);
			}
		}

		if (lowestF == nullptr)
			break;
		openList.remove(lowestF);
		closedList.push_back(lowestF);

		// if the lowest cost is our target tile, we're done!
		if (lowestF->pTile == targetTile)
		{
			break;
		}
		n = lowestF;
		safeCheck++;
	}

	// if we didnt find anything, get out of here
	if (closedList.size() == 0)
	{
		return false;
	}

	// Go through the list of found tiles and add them to our waypoints of our path
	ASNode* nNode = closedList.back();
	safeCheck = 0;
	while (nNode->parent != nullptr && (safeCheck < 5000))
	{
		m_vWaypoints.push_back(nNode->pTile);
		nNode = nNode->parent;
	}

	// CLEANUP. delete all memory we made
	std::list<ASNode*>::iterator listIter;
	for (listIter = openList.begin(); listIter != openList.end(); ++listIter)
	{
		delete (*listIter);
	}
	for (listIter = closedList.begin(); listIter != closedList.end(); ++listIter)
	{
		delete (*listIter);
	}

	// return that it worked fine
	return true;
}

void CGameplayState::ClearSelections(void)
{
	m_bIsMoving = false;
	m_bIsTargeting = false;
	m_bSelectChampionAbility = false;
	m_pTargetedTile = nullptr;
	m_pSelectedUnit = nullptr;
	m_nSelectedAbility =0;
	m_pHighlightedUnit = nullptr;
	m_bIsHighlighting = false;
	m_bShowSpellPanel = false;
	m_vWaypoints.clear();
}
void CGameplayState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	LerpCamera(fElapsedTime);

	if (pDI->KeyPressed(DIK_J))
	{
		int xRand = rand() % 800;
		int yRand = rand() % 600;
		CFloatingText::GetInstance()->AddText(std::string("test"), Vec2Df(50.0f, 100.0f), Vec2Df(0.0f, -50.0f), 5.0f, 0.4f, D3DCOLOR_XRGB(255, 0, 0));
		CFloatingText::GetInstance()->AddText(std::string("test"), Vec2Df(50.0f, 100.0f), Vec2Df(0.0f, 50.0f), 5.0f, 0.5f);
		CFloatingText::GetInstance()->AddText(std::string("test"), Vec2Df(50.0f, 100.0f), Vec2Df(50.0f, 0.0f), 5.0f, 0.5f);
		CFloatingText::GetInstance()->AddText(std::string("test"), Vec2Df(50.0f, 100.0f), Vec2Df(-50.0f, 0.0f), 5.0f, 0.5f);
	}

	if (m_bIsHighlighting == true)
	{
		if (m_nCardOffsetX > m_nCardOffsetMaxX)
		{
			m_nCardOffsetX -= (int)(450 * fElapsedTime);
		}
		if (m_nCardOffsetX < m_nCardOffsetMaxX)
			m_nCardOffsetX = m_nCardOffsetMaxX;
		if (m_nCardOffsetX < CGame::GetInstance()->GetWindowWidth())
			m_bShowingCard = true;
	}
	else
	{
		m_nCardOffsetX += (int)(450 * fElapsedTime);
		if (m_nCardOffsetX > CGame::GetInstance()->GetWindowWidth())
			m_nCardOffsetX = CGame::GetInstance()->GetWindowWidth();
	}

	if (m_pSelectedUnit != nullptr)
	{
		if (m_nTooltipOffsetX < m_nTooltipOffsetMaxX)
		{
			m_nTooltipOffsetX += (int)(450 * fElapsedTime);
		}

		if (m_nTooltipOffsetX > m_nTooltipOffsetMaxX)
			m_nTooltipOffsetX = m_nTooltipOffsetMaxX;
	}
	else
	{
		m_nTooltipOffsetX -= (int)(450 * fElapsedTime);
		if (m_nTooltipOffsetX < -300)
			m_nTooltipOffsetX = -300;
	}

	if (m_bSelectChampionAbility)
	{
		if (m_nSpellPanelOffsetY > m_nSpellPanelOffsetYMAX)
		{
			m_nSpellPanelOffsetY -= (int)(650 * fElapsedTime);
		}
		if (m_nSpellPanelOffsetY < m_nSpellPanelOffsetYMAX)
			m_nSpellPanelOffsetY = m_nSpellPanelOffsetYMAX;
		if (m_nSpellPanelOffsetY < CGame::GetInstance()->GetWindowHeight())
			m_bShowSpellPanel = true;

	}
	else
	{
		m_nSpellPanelOffsetY += (int)(650 * fElapsedTime);
		if (m_nSpellPanelOffsetY > CGame::GetInstance()->GetWindowHeight())
			m_nSpellPanelOffsetY = CGame::GetInstance()->GetWindowHeight();
	}

	if (pDI->KeyPressed(DIK_R))
	{
		CAddResourceMessage* pMsg = new CAddResourceMessage(TT_MILL, 0);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	// Testing Particle Rendering
	CAIManager::GetInstance()->UpdateAI(fElapsedTime);

	CParticleManager::GetInstance()->Update(fElapsedTime);
	CObjectManager::GetInstance()->UpdateAllObjects(fElapsedTime);
	CAnimationManager::GetInstance()->Update(fElapsedTime);
	CGameManager::GetInstance()->Update(fElapsedTime);
	CFloatingText::GetInstance()->Update(fElapsedTime);
}

RECT CellAlgorithm( int id )
{

	// quick fix for rendering the wrong tiles
	//if (id == 1)
	//	id = 2;
	//else if (id == 2)
	//	id = 1;
	RECT rSource;

	rSource.left	= (id % 4) * (nFakeTileWidth - 26);
	rSource.top		= (id / 4) * (nFakeTileHeight - 27);

	rSource.right	= rSource.left	+ (nFakeTileWidth - 26) +1;
	rSource.bottom	= rSource.top	+ (nFakeTileHeight - 27);

	return rSource;

}
void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);
	CTileManager::GetInstance()->Render();
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	// render the waypoints?
	if (m_pSelectedUnit != nullptr)
	{
		int nTilesCanMove = m_pSelectedUnit->GetSpeed() - m_pSelectedUnit->GetTilesMoved();
		int nAPCost = 0;
		int r = 0;
		int g = 255;
		int b = 0;

		for (int i = m_vWaypoints.size() - 1; i >= 0; --i)
		{
			nAPCost += m_vWaypoints[i]->GetAPCost();
			nTilesCanMove--;
			CPlayer* pPlayer = CGameManager::GetInstance()->GetCurrentPlayer();
			if (nAPCost > CGameManager::GetInstance()->GetCurrentPlayer()->GetAP())
			{
				r = 255;
				g = 0;
			}
			if (nTilesCanMove < 0)
			{
				r = 255;
				g = 0;
			}

			int x = (nFakeTileWidth / 2 * m_vWaypoints[i]->GetPosition().nPosX ) - (nFakeTileHeight / 2 * m_vWaypoints[i]->GetPosition().nPosY);
			int y = (nFakeTileWidth / 2 * m_vWaypoints[i]->GetPosition().nPosX ) + (nFakeTileHeight  / 2 * m_vWaypoints[i]->GetPosition().nPosY);
			RECT tileRect = { x - GetCamOffsetX(), 
				y - GetCamOffsetY(),  
				nFakeTileWidth, nFakeTileHeight};
			//	CGraphicsManager::GetInstance()->DrawWireframeRect(tileRect, r, g, b);
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("wphighlight")),
				tileRect.left, tileRect.top, 1.0f, 1.0f, (RECT*)0, nFakeTileWidth / 2.0f, nFakeTileHeight / 2.0f, (45.0f * 3.1415928f / 180.0f), D3DCOLOR_ARGB(120,r, g, b));
		}


		// Draw the doohickeys on the ground to show the pattern
		CAbility* drawAbility ;
		if (m_bSelectChampionAbility)
			drawAbility = (dynamic_cast<CHero*>(m_pSelectedUnit))->GetSpell(m_nSelectedSpell);
		else
			drawAbility = m_pSelectedUnit->GetAbility(m_nSelectedAbility);
		if( drawAbility != nullptr )
		{
			std::vector< Vec2D > pattern, range;
			if (drawAbility->GetType() == SP_ARCHERRANGEDATTACK || drawAbility->GetType() ==SP_MELEEATTACK)
				range = CAbilityManager::GetInstance()->GetRange(m_pSelectedUnit->GetRange());				
			else
			{
				if( drawAbility->GetType() == SP_CHARGE )
					range = drawAbility->GetPattern();
				else
					range = CAbilityManager::GetInstance()->GetRange(drawAbility->GetRange());
			}
			if( drawAbility->GetType() != SP_CHARGE )
				pattern = drawAbility->GetPattern();

			if( drawAbility->GetApCost() == 5 )
				int i = 0;
			if (drawAbility != nullptr && !drawAbility->m_bIsMove)
			{
				//if (drawAbility->GetType() == SP_ARCHERRANGEDATTACK || drawAbility->GetType() == SP_MELEEATTACK)
				//{

				//	pattern = CAbilityManager::GetInstance()->GetRange(m_pSelectedUnit->GetRange());
				//}
				// it's a real ability and it's not the move one

				// Draw the range
				for (unsigned int i = 0; i < range.size(); ++i)
				{

					int x = range[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
					int y = range[i].nPosY + m_pSelectedUnit->GetPos().nPosY;

					CTile* pPatternTile = CTileManager::GetInstance()->GetTile(x, y);

					if (pPatternTile != nullptr)
					{
						int r = 255 * !(drawAbility->m_nPhase == CGameManager::GetInstance()->GetCurrentPhase());
						int g = 255 * (drawAbility->m_nPhase == CGameManager::GetInstance()->GetCurrentPhase());

						int x = (nFakeTileWidth / 2 * pPatternTile->GetPosition().nPosX) - (nFakeTileHeight / 2 * pPatternTile->GetPosition().nPosY);
						int y = (nFakeTileWidth / 2 * pPatternTile->GetPosition().nPosX) + (nFakeTileHeight  / 2 * pPatternTile->GetPosition().nPosY);
						CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("wphighlight")),
							x - GetCamOffsetX(),
							y - GetCamOffsetY()
							, 1.0f, 1.0f, (RECT*)0, nFakeTileWidth / 2.0f, nFakeTileHeight / 2.0f, (45.0f * 3.1415928f / 180.0f), D3DCOLOR_ARGB(90, r, g, 255));
					}
				}

				// Draw the target pattern
				Vec2D targetVec = m_pSelectedUnit->GetPos();
				if (m_bIsTargeting)
					targetVec = m_SelectionPos;

				for (unsigned int i = 0; i < pattern.size(); ++i)
				{

					int x = pattern[i].nPosX + targetVec.nPosX;
					int y = pattern[i].nPosY + targetVec.nPosY;

					CTile* pPatternTile = CTileManager::GetInstance()->GetTile(x, y);

					if (pPatternTile != nullptr)
					{
						int r = 255 * !(drawAbility->m_nPhase == CGameManager::GetInstance()->GetCurrentPhase());
						int g = 255 * (drawAbility->m_nPhase == CGameManager::GetInstance()->GetCurrentPhase());

						int x = (nFakeTileWidth / 2 * pPatternTile->GetPosition().nPosX) - (nFakeTileHeight / 2 * pPatternTile->GetPosition().nPosY);
						int y = (nFakeTileWidth / 2 * pPatternTile->GetPosition().nPosX) + (nFakeTileHeight  / 2 * pPatternTile->GetPosition().nPosY);
						CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("wphighlight")),
							x - GetCamOffsetX(),
							y - GetCamOffsetY()
							, 1.0f, 1.0f, (RECT*)0, nFakeTileWidth / 2.0f, nFakeTileHeight / 2.0f, (45.0f * 3.1415928f / 180.0f), D3DCOLOR_ARGB(90, r, g, 0));
					}
				}
			}
		}
	}

	int x = (nFakeTileWidth / 2 * m_SelectionPos.nPosX) - (nFakeTileHeight / 2 * m_SelectionPos.nPosY);
	int y = (nFakeTileWidth / 2 * m_SelectionPos.nPosX) + (nFakeTileHeight  / 2 * m_SelectionPos.nPosY);
	// selection cursor
	RECT selectRect = { m_SelectionPos.nPosX * nFakeTileWidth - GetCamOffsetX(), m_SelectionPos.nPosY * nFakeTileHeight - GetCamOffsetY(),  
		nFakeTileWidth, nFakeTileHeight};
	x -= 1;
	y-=18;
	RECT diamondRect = {x- GetCamOffsetX(), y -GetCamOffsetY(), nFakeTileWidth, nFakeTileHeight };

	if (m_bIsMoving)
		CGraphicsManager::GetInstance()->DrawWireframeDiag(diamondRect, 0, 255, 0);
	else if (m_bIsTargeting)
		CGraphicsManager::GetInstance()->DrawWireframeDiag(diamondRect, 255, 0, 0);
	else
		CGraphicsManager::GetInstance()->DrawWireframeDiag(diamondRect, 255, 255, 255);

	CObjectManager::GetInstance()->RenderAllObjects();
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	//Render the map

	// Testing particle rendering
	CParticleManager::GetInstance()->Render();




	//if (m_bIsMoving)
	//	CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 0, 255, 0);
	//else
	//	CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 255, 255, 255);

	// Render the UI Overlay
	CSGD_TextureManager::GetInstance()->Draw(
		CGraphicsManager::GetInstance()->GetID(_T("uioverlay")), 0, 0, 0.8f,0.6f);

	if (m_bShowingCard)
	{
		CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("showcard")), m_nCardOffsetX, 240, 1.0f, 0.8f);
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
		if (m_pHighlightedUnit != nullptr)
		{
			std::ostringstream moss;
			CSGD_TextureManager::GetInstance()->Draw(m_pHighlightedUnit->GetPortraitID(), m_nCardOffsetX + 20, 244, 1.6f, 1.6f);

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("speedicon")),
				m_nCardOffsetX + 150, 248, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetSpeed();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 255, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 200, 255, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			moss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("damageicon")),
				m_nCardOffsetX + 150, 288, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetAttack();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 295, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 200, 295, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			moss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("rangeicon")),
				m_nCardOffsetX + 150, 338, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetRange();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 345, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 200, 345, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			moss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("tilesmovedicon")),
				m_nCardOffsetX + 150, 378, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetTilesMoved();
			m_pBitmapFont->Print(moss.str().c_str(),m_nCardOffsetX + 200, 385, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 385, 255, 255, 255);
			moss.str((""));

			if (m_pHighlightedUnit->GetDodgeChance() > 0.0f)
			{
				moss << "Dodge Chance: " << (m_pHighlightedUnit->GetDodgeChance() * 100) << "%";
				//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 15, 222, 255, 255, 255);
				m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 15, 222, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

				moss.str((""));

			}
			float fhpPercent = (float)m_pHighlightedUnit->GetHP() / (float)m_pHighlightedUnit->GetMaxHP();

			int colR = 0, colG = 255;
			if (fhpPercent < 0.80f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.60f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.40f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.20f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (colR > 255)
				colR = 255;
			if (colG < 0)
				colG = 0;
			RECT hpRect = { m_nCardOffsetX + 20, 350, m_nCardOffsetX + 20 + (LONG)(102 * fhpPercent), 360 };
			CSGD_Direct3D::GetInstance()->DrawRect(hpRect, colR, colG, 0);

			// debuffs

			for (int i = 0; i < m_pHighlightedUnit->GetNumEffects(); ++i)
			{
				CSGD_TextureManager::GetInstance()->Draw(
					CGraphicsManager::GetInstance()->GetID(m_pHighlightedUnit->GetEffect(i)->m_szInterfaceIcon), 
					m_nCardOffsetX + 20 + (25*i), 370, 0.4f, 0.4f);
			}


		}
	}

	if (m_pSelectedUnit != nullptr)
	{
		int nCursorPosX = 0;
		int nCursorPosY = 515;
		switch (m_nSelectedAbility)
		{
		default:
		case 0:
			nCursorPosX = 280;
			break;
		case 1:
			nCursorPosX = 375;
			break;
		case 2:
			nCursorPosX = 470;
			break;
		}

		CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("panelselect")),  nCursorPosX, nCursorPosY, 0.6f, 0.6f);

		// drawin icons. Could loop it, don't see a reason to

		CAbility* pAbility = m_pSelectedUnit->GetAbility(0);
		if (pAbility != nullptr)
		{
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 287, 522);
		}
		pAbility = m_pSelectedUnit->GetAbility(1);
		if (pAbility != nullptr)
		{
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 382, 522);
		}
		pAbility = m_pSelectedUnit->GetAbility(2);
		if (pAbility != nullptr)
		{
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 477, 522);
		}

		int n = CGame::GetInstance()->GetWindowWidth();
		int y = CGame::GetInstance()->GetWindowHeight();
		CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("showcard")), m_nTooltipOffsetX - 50, 240, 1.0f, 0.8f);
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

		if (m_bShowSpellPanel)
		{
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("spellpanel")), 245, m_nSpellPanelOffsetY, 0.64f, 0.6f);

			CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
			if (pHero != nullptr)
			{
				for (unsigned int i = 0; i < pHero->GetNumSpells(); ++i)
				{
					CSGD_TextureManager::GetInstance()->Draw(
						CGraphicsManager::GetInstance()->GetID(pHero->GetSpell(i)->m_szInterfaceIcon),
						260 + (i * 78), m_nSpellPanelOffsetY + 42);
					if (m_nSelectedSpell == i)
					{
						CSGD_TextureManager::GetInstance()->Draw(
							CGraphicsManager::GetInstance()->GetID(_T("panelselect")), 
							253 + (i * 78), m_nSpellPanelOffsetY + 36, 0.6f, 0.6f);
					}
				}

				std::ostringstream tt;
				CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
				CGraphicsManager* pGM = CGraphicsManager::GetInstance();
				CAbility* pA = pHero->GetSpell(m_nSelectedSpell);
				if (pA != nullptr)
				{
					pTM->Draw(pA->GetIconID(), m_nTooltipOffsetX + 30, 248, 1.0f, 1.0f);

					pTM->Draw(pGM->GetID(_T("damageicon")), m_nTooltipOffsetX + 120, 248, 0.5f, 0.5f);
					tt << pA->GetDamage() < 0 ? abs(pA->GetDamage()) : pA->GetDamage();

					if( pA->GetType() == SP_MELEEATTACK || pA->GetType() == SP_ARCHERRANGEDATTACK )
					{
						tt.str("");
						tt << pHero->GetAttack();
					}

					m_pBitmapFont->Print(tt.str().c_str(), m_nTooltipOffsetX + 170, 255, 0.3f, pA->GetDamage() < 0 ? D3DCOLOR_XRGB(0,255,0) : D3DCOLOR_XRGB(255,0,0));
					tt.str("");
					tt << pHero->GetAttack();

					tt.str("");
					pTM->Draw(pGM->GetID(_T("rangeicon")), m_nTooltipOffsetX + 120, 288, 0.5f, 0.5f);
					tt << pA->GetRange();

					if( pA->GetType() == SP_MOVE )
					{
						tt.str("");
						tt << pHero->GetSpeed();
					}

					m_pBitmapFont->Print(tt.str().c_str(), m_nTooltipOffsetX + 170, 295, 0.3f, D3DCOLOR_XRGB(255,255,255));
					tt.str("");

					m_pBitmapFont->Print(pA->GetDescription().c_str(), m_nTooltipOffsetX + 5, 338, .3f, D3DCOLOR_XRGB(255,255,255), 150);
				}
			}
		}
		else 
		{
			std::ostringstream tt;
			CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
			CGraphicsManager* pGM = CGraphicsManager::GetInstance();
			CAbility* pA = m_pSelectedUnit->GetAbility(m_nSelectedAbility);
			if (pA != nullptr)
			{
				pTM->Draw(pA->GetIconID(), m_nTooltipOffsetX + 30, 248, 1.0f, 1.0f);

				pTM->Draw(pGM->GetID(_T("damageicon")), m_nTooltipOffsetX + 120, 248, 0.5f, 0.5f);
				tt << pA->GetDamage() < 0 ? abs(pA->GetDamage()) : pA->GetDamage();

				int damage = pA->GetDamage();
				if( pA->GetType() == SP_MELEEATTACK || pA->GetType() == SP_ARCHERRANGEDATTACK )
				{
					tt.str("");
					tt << m_pSelectedUnit->GetAttack();
					damage = m_pSelectedUnit->GetAttack();
				}

				m_pBitmapFont->Print(tt.str().c_str(), m_nTooltipOffsetX + 170, 255, 0.3f, damage < 0 ? D3DCOLOR_XRGB(0,255,0) : D3DCOLOR_XRGB(255,0,0));
				tt.str("");

				pTM->Draw(pGM->GetID(_T("rangeicon")), m_nTooltipOffsetX + 120, 288, 0.5f, 0.5f);
				tt << pA->GetRange();

				if( pA->GetType() == SP_MOVE )
				{
					tt.str("");
					tt << m_pSelectedUnit->GetSpeed();
				}

				m_pBitmapFont->Print(tt.str().c_str(), m_nTooltipOffsetX + 170, 295, 0.3f, D3DCOLOR_XRGB(255,255,255));
				tt.str("");

				m_pBitmapFont->Print(pA->GetDescription().c_str(), m_nTooltipOffsetX + 5, 338, .3f, D3DCOLOR_XRGB(255,255,255), 170);
			}
		}
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("showcard")), m_nTooltipOffsetX, 240, 1.0f, 0.8f);
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	}
	// MINI MAP TIME! Render this ontop of the interface thing. Will need to tweak when we go isometric

	int nMiniMapOffsetX = 10;
	int nMiniMapOffsetY = 440;
	RECT miniR = {nMiniMapOffsetX, nMiniMapOffsetY, nMiniMapOffsetX + 225, nMiniMapOffsetY + 152};
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	float nMiniMapWidth = 225.0f;
	float nMiniMapHeight = 152.0f;
	float nMiniTileWidth = nMiniMapWidth / CTileManager::GetInstance()->GetNumRows();
	float nMiniTileHeight = nMiniMapHeight / CTileManager::GetInstance()->GetNumColumns();

	// Render the tiles. Only using colored blocks for now
	for (int i = 0; i < CTileManager::GetInstance()->GetNumRows(); ++i)
		for (int j = 0; j < CTileManager::GetInstance()->GetNumColumns(); ++j)
		{
			RECT tileRect = { (LONG)(i * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			CTile* pTile = CTileManager::GetInstance()->GetTile(i, j);
			RECT rSrc;
			switch (pTile->GetTileType())
			{
			case TT_PLAINS:
				rSrc = CellAlgorithm(TT_PLAINS);
				g=177; r=34; b=76; break;
			case TT_FOREST:
				rSrc = CellAlgorithm(TT_FOREST);
				g=128; r=0; b=0; break;
			case TT_MOUNTAINS:
				rSrc = CellAlgorithm(TT_MOUNTAINS);
				g=64;r=128; b=0; break;
			case TT_WATER:
				rSrc = CellAlgorithm(TT_WATER);
				g=128;r=0;b=192;break; 
			case TT_MINE:
				rSrc = CellAlgorithm(TT_MINE);
				g=64;r=128; b=0; break;
			case TT_MILL:
				rSrc = CellAlgorithm(TT_MILL);
				g=128; r=0; b=0; break;
			case TT_FARM:
				rSrc = CellAlgorithm(TT_FARM);
				g=177; r=34; b=76; break;
			case TT_CASTLE:
				rSrc = CellAlgorithm(TT_CASTLE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("GrassTile")),
				tileRect.left, tileRect.top, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);

			//CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);

			r = 255 * !(pTile->GetPlayerID());
			b = 255 * (pTile->GetPlayerID());
			g = 0;
			switch (pTile->GetTileType())
			{
			case TT_MILL:
			case TT_MINE:
			case TT_FARM:
				CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("minitriangle")),
					(int)tileRect.left + 1, (int)tileRect.top + 1, 1.0f, 1.0f,(RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(r,g,b));
				break;
			}
		}

		// Render the units as circles
		for (decltype(CGameManager::GetInstance()->GetUnits().size()) i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
		{
			int r = 255 * (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == 0);
			int b = 255 * (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == 1);
			int g = 0;
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("minicircle")),
				int(CGameManager::GetInstance()->GetUnits()[i]->GetPos().nPosX * nMiniTileWidth + nMiniMapOffsetX + 1),
				int(CGameManager::GetInstance()->GetUnits()[i]->GetPos().nPosY * nMiniTileHeight + nMiniMapOffsetY),
				1.0f, 1.0f, (RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(r, g, b));
		}
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

		// UNIT CARD STUFF HOORAY
		if (m_pSelectedUnit != nullptr)
		{
			std::ostringstream woss;
			CSGD_TextureManager::GetInstance()->Draw(m_pSelectedUnit->GetPortraitID(), 578, 435, 1.6f, 1.6f);

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("speedicon")),
				710, 440, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetSpeed();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 445, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 755, 445, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("damageicon")),
				710, 480, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetAttack();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 485, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 755, 485, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("rangeicon")),
				710, 520, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetRange();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 525, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 755, 525, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("tilesmovedicon")),
				710, 560, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetTilesMoved();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 565, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 755, 565, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			float fhpPercent = (float)m_pSelectedUnit->GetHP() / (float)m_pSelectedUnit->GetMaxHP();

			int colR = 0, colG = 255;
			if (fhpPercent < 0.80f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.60f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.40f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (fhpPercent < 0.20f)
			{
				colR += 65; 
				colG -= 65;
			}
			if (colR > 255)
				colR = 255;
			if (colG < 0)
				colG = 0;
			RECT hpRect = { 578, 540, 578 + (LONG)(102 * fhpPercent), 550 };
			CSGD_Direct3D::GetInstance()->DrawRect(hpRect, colR, colG, 0);

			// debuffs

			for (int i = 0; i < m_pSelectedUnit->GetNumEffects(); ++i)
			{
				CSGD_TextureManager::GetInstance()->Draw(
					CGraphicsManager::GetInstance()->GetID(m_pSelectedUnit->GetEffect(i)->m_szInterfaceIcon), 580 + (25*i), 560, 0.4f, 0.4f);
			}
		}




		// DEBUG STUFF
		CPlayer* pDebugPlayer = CGameManager::GetInstance()->GetCurrentPlayer();
		std::ostringstream oss;
		if (pDebugPlayer != nullptr)
		{
			//oss << "CurrCamPixel X: " << m_currCamPixelPos.nPosX << " Y: " << m_currCamPixelPos.nPosY;
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 10, 250, 255, 255, 255);
			//oss.str(_T(""));
			//oss << "NewCamPixel X: " << m_newCamPixelPos.nPosX << " Y: " << m_newCamPixelPos.nPosY;
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 10, 270, 255, 255, 255);

			//oss.str(_T(""));

			oss << "AP: " << pDebugPlayer->GetAP() << ", Pop: "<< pDebugPlayer->GetPopCap() <<'/'<<pDebugPlayer->GetMaxPopCap()<<", Wood: " << pDebugPlayer->GetWood() << 
				", Metal: " << pDebugPlayer->GetMetal() << '\n';
			m_pBitmapFont->Print(oss.str().c_str(), 258, 486, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			ostringstream woss;
			woss<<"EXP: "<< CGameManager::GetInstance()->GetCurrentPlayer()->GetExp();
			m_pBitmapFont->Print(woss.str().c_str(),10,10,0.5f,D3DXCOLOR(255,255,255,255));
			///	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 258, 486, 255, 255, 255);
			oss.str((""));
			if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() == 0)
				oss << "PLAYER 1 ";
			else 
				oss << "PLAYER 2 ";
			if (CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
			{
				oss << "MOVEMENT";
			}
			else
				oss << "ATTACK";
			m_pBitmapFont->Print(oss.str().c_str(), 580, 10, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 600, 0, 255, 255, 255);
			oss.str((""));
			int nTurn = CGameManager::GetInstance()->GetCurrentTurn();
			oss << "Current Turn: " << CGameManager::GetInstance()->GetCurrentTurn();
			//const char* tempchar = "CURRENT TURN:";
			const char* tempchar = "";
			m_pBitmapFont->Print(tempchar,0,40,0.4f,D3DXCOLOR(0,255,0,255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 600, 30, 255, 255, 255);

			oss.str((""));
			oss << "Selected Unit: ";
			if (m_pSelectedUnit != nullptr)
			{
				oss << m_pSelectedUnit->GetType() << ", X: " << m_pSelectedUnit->GetPos().nPosX << ", Y: " << 
					m_pSelectedUnit->GetPos().nPosY << ", HP: " << m_pSelectedUnit->GetHP() << ", facing: " << m_pSelectedUnit->GetFacing();
			}
			//m_pBitmapFont->Print((const char*)oss.str().c_str(),0, 350, 1.0f,(DWORD)(255,255,255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 350, 255, 255, 255);
		}



		// AI debug render input queue
		int nY = 40;
		for (unsigned int i = 0; i < CAIManager::GetInstance()->m_vInputQueue.size(); ++i)
		{
			std::wostringstream woss;
			switch (CAIManager::GetInstance()->m_vInputQueue[i])
			{
			case INPUT_UP:
				woss << "AI UP";
				break;
			case INPUT_DOWN:
				woss << "AI DOWN";
				break;
			case INPUT_LEFT:
				woss << "AI LEFT";
				break;
			case INPUT_RIGHT:
				woss << "AI RIGHT";
				break;
			case INPUT_ACCEPT:
				woss << "AI ACCEPT";
				break;
			case INPUT_AI_CLEAR:
				woss << "AI CLEAR";
				break;
			case INPUT_AI_SELECTED:
				woss << "AI SELECTED";
				break;
			case INPUT_AI_MOVED:
				woss << "AI MOVED";
				break;
			case INPUT_AI_ATTACKED:
				woss << "AI ATTACKED";
				break;
			case INPUT_AI_SELECTABILITY_1:
				woss << "AI SELECTABILITY 1";
				break;
			case INPUT_AI_SELECTABILITY_2:
				woss << "AI SELECTABILITY 2";
				break;
			case INPUT_AI_SELECTABILITY_3:
				woss << "AI SELECTABILITY 3";
				break;
			case INPUT_AI_CHAMPSPELL:
				woss << "AI CHAMPSPELL";
				break;
			case INPUT_AI_SELECTSPELL1:
				woss << "AI SELECTSPELL 1";
				break;
			case INPUT_AI_SELECTSPELL2:
				woss << "AI SELECTSPELL 2";
				break;
			case INPUT_AI_SELECTSPELL3:
				woss << "AI SELECTSPELL 3";
				break;
			case INPUT_AI_SELECTSPELL4:
				woss << "AI SELECTSPELL 4";
				break;
			}
			CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 20, nY, 255, 255, 255);
			nY += 20;
		}


		CFloatingText::GetInstance()->Render();


}
