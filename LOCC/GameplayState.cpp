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
#include "ControllerUnpluggedState.h"
#include "StateStack.h"
#include "PauseState.h"
#include "Hero.h"
#include "BitmapFont.h"
#include "FloatingText.h"
#include "HUD.h"
#include "CoinToss.h"
#include "SpellScrollState.h"
#include "SoundManager.h"
#include "BitmapFont.h"
#include "StringTable.h"
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
	musicvolume = 0;
	MusicIncrease = 0.0f;
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
	m_nSpellPanelOffsetYMAX =  CGame::GetInstance()->GetWindowHeight() - 175;
	m_nCardOffsetX = -165;
	m_nCardOffsetMaxX = 46;
	m_nTooltipOffsetY = 600;
	m_nTooltipOffsetMaxY = 340;
	pGM;
	nStoredUnitIndex = 0;

	m_bDayTime = true;
	m_nDayAlphaScale = 255;
	m_nNightAlphaScale = 0;

	if (CGameManager::GetInstance()->GetLoadingFromSave())
	{
		SnapToPosition(CGameManager::GetInstance()->GetChampion(
			CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())->GetPos(), true);
	}
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

	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-033
	// BUG FIX START
	/////////////////////////////////////////////////////////////////

	// Stopped tile manager shutting down when switching from in-game to a new map. Would try to 
	// shutdown after being shutdown and crash

	if (!CGameManager::GetInstance()->GetLoadingFromSave())
		CTileManager::GetInstance()->ShutDown();

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-033
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-017
	// BUG FIX START
	/////////////////////////////////////////////////////////////////

	// Cleaned up particles on gameplay state exit. I believe the crash was caused by
	// looping particles being perpetually looping...it would delete them then in the emitter loop spawn
	// a new one, then delete that then spawn a new one. This seems to do the job, just nuke the
	// entire list of emitters (we are exiting the game anyway, don't need them!
	CParticleManager::GetInstance()->Clear();

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-017
	/////////////////////////////////////////////////////////////////

	CMessageSystem::GetInstance()->ProcessMessages();
	CAnimationManager::GetInstance()->Shutdown();
	delete m_pBitmapFont;
	if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic"))) || CSGD_XAudio2::
		GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic"))) || CSGD_XAudio2::
		GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic"))))
	{
		CSGD_XAudio2::GetInstance()->MusicStopSong(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic")));
		CSGD_XAudio2::GetInstance()->MusicStopSong(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic")));
		CSGD_XAudio2::GetInstance()->MusicStopSong(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")));
	}

}


void CGameplayState::SnapCameraToPosition(Vec2D pPos)
{
	int x = (nFakeTileWidth / 2 * pPos.nPosX) - (nFakeTileHeight / 2 * pPos.nPosY);
	int y = (nFakeTileWidth / 2 * pPos.nPosX) + (nFakeTileHeight  / 2 * pPos.nPosY);
	//m_newCamPixelPos.nPosX = x;
	//m_newCamPixelPos.nPosY = y;
	//m_bLerpingX = true;


	m_oldCamPixelPos = m_currCamPixelPos;
	m_newCamPixelPos = Vec2D(x, y);
	m_fLerpPercent = 1.0f;
	m_bLerpingX = true;
}
// Snaps the camera to the passed in Vec2D. This is used for moving the camera to the player's hero at turn start
// but could be used for anything. Just pass a pUnit in and the camera and selection cursor shifts to that unit.
void CGameplayState::SnapToPosition(Vec2D pPos, bool noSound)
{
	int nSelX = pPos.nPosX - m_SelectionPos.nPosX;
	int nSelY = pPos.nPosY - m_SelectionPos.nPosY;


	MoveCursor(nSelX, nSelY, false, noSound);

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
void CGameplayState::MoveCursor(int dX, int dY, bool lock, bool noSound)
{
	m_SelectionPos.nPosX += dX;
	m_SelectionPos.nPosY += dY;

	if (!noSound)
	{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("selectionmove")), false, false);
	}
	//PUT_SOUND_HERE("Whatever, make it the tick tick tick sound when you move cursors")
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

		CalculateMove(pStartTile, pTargetTile, m_vWaypoints);
	}

	// This locks camera to cursor position
	if (lock == true)
	{
		if (m_CameraPos.nPosX < m_SelectionPos.nPosX)
		{
			SnapCameraToPosition(m_SelectionPos);
			//int n = m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth);
			//int nDistance = m_SelectionPos.nPosX - n;
			//MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosX > m_SelectionPos.nPosX)
		{
			SnapCameraToPosition(m_SelectionPos);

			//int n = m_CameraPos.nPosX;
			//int nDistance = m_SelectionPos.nPosX - n;
			//MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosY < m_SelectionPos.nPosY)
		{
			SnapCameraToPosition(m_SelectionPos);

			//int n = m_CameraPos.nPosY + int(((CGame::GetInstance()->GetWindowHeight() * 0.8f)) / nFakeTileHeight);
			//int nDistance = m_SelectionPos.nPosY - n;
			//MoveCamera(0, nDistance);
		}
		if (m_CameraPos.nPosY > m_SelectionPos.nPosY)
		{
			SnapCameraToPosition(m_SelectionPos);

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
	case INPUT_PAUSE:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			CStateStack::GetInstance()->Push(CPauseState::GetInstance());
		}
		break;
	case INPUT_BUMPERRIGHT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			nStoredUnitIndex++;
				if ((unsigned int)nStoredUnitIndex > CGameManager::GetInstance()->GetUnits().size() - 1)
					nStoredUnitIndex = 0;
			CUnit* pNextUnit = CGameManager::GetInstance()->GetUnits()[nStoredUnitIndex];
			while (pNextUnit->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			{
				int size = CGameManager::GetInstance()->GetUnits().size();
				if ((unsigned int)nStoredUnitIndex >= CGameManager::GetInstance()->GetUnits().size() - 1)
					nStoredUnitIndex = -1;
				nStoredUnitIndex++;
				pNextUnit = CGameManager::GetInstance()->GetUnits()[nStoredUnitIndex];
			}
			SnapToPosition(pNextUnit->GetPos());

		}
		break;
	case INPUT_BUMPERLEFT:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

			nStoredUnitIndex--;
				if (nStoredUnitIndex < 0)
					nStoredUnitIndex = CGameManager::GetInstance()->GetUnits().size() - 1;
			CUnit* pNextUnit = CGameManager::GetInstance()->GetUnits()[nStoredUnitIndex];
			while (pNextUnit->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			{
				if (nStoredUnitIndex <= 0)
				{
					nStoredUnitIndex = CGameManager::GetInstance()->GetUnits().size() - 1;
				}
				else
				{
					nStoredUnitIndex--;
				}
				pNextUnit = CGameManager::GetInstance()->GetUnits()[nStoredUnitIndex];
			}
			SnapToPosition(pNextUnit->GetPos());			

		}
		break;
	case INPUT_UP:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving) && (!m_bIsTargeting) )
			{
				// do nothing, up arrow does nothing with a unit selected
				
				if ( m_bIsFacing )
				{
					m_pSelectedUnit->SetFacing(0);
				}
			}
			else
				MoveCursor(0, -1);
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
				//{
				
				if ( m_bIsFacing )
				{
					m_pSelectedUnit->SetFacing(3);
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				}
				else if (m_bSelectChampionAbility)
				{
					//PUT_SOUND_HERE("Whatever, make it the tick tick tick sound when you move cursors")
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
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
					//PUT_SOUND_HERE("Whatever, make it the tick tick tick sound when you move cursors")
					m_nSelectedAbility--;
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					if (m_nSelectedAbility < 0)
						m_nSelectedAbility = 2;
				}
				//}
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
				//{
					
				if ( m_bIsFacing )
				{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_pSelectedUnit->SetFacing(1);
				}
				else if (m_bSelectChampionAbility)
				{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_nSelectedSpell++;
					//PUT_SOUND_HERE("Whatever, make it the tick tick tick sound when you move cursors")
					CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
					if (m_nSelectedSpell >= (int)pHero->GetNumSpells())
						m_nSelectedSpell = 0;
				}
				else
				{
					// Champion ability is not pulled up, so just move the cursor on the main panel
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_nSelectedAbility++;
					//PUT_SOUND_HERE("Whatever, make it the tick tick tick sound when you move cursors")
					CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
					if (m_nSelectedAbility > 2)
						m_nSelectedAbility = 0;
				}
				//}
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
				
				if ( m_bIsFacing )
				{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_pSelectedUnit->SetFacing(2);
				}
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
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

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
					//PUT_SOUND_HERE("Some kind of accept sound");
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

					MoveToTile(m_SelectionPos);
				}
				else if (m_bIsTargeting)
				{
					if (m_bSelectChampionAbility)
					{
						//PUT_SOUND_HERE("Some kind of accept sound");
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

						m_pTargetedTile = CTileManager::GetInstance()->GetTile(m_SelectionPos.nPosX, m_SelectionPos.nPosY);
						CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);
						UseAbility(pHero->GetSpell(m_nSelectedSpell));
					}
					else
					{
						//PUT_SOUND_HERE("Some kind of accept sound");
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

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
							//PUT_SOUND_HERE("Some kind of accept sound");
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

							UseAbility(pHero->GetSpell(m_nSelectedSpell));							
						}
					}
					else
					{
						//PUT_SOUND_HERE("Some kind of accept sound");


						UseAbility(m_pSelectedUnit->GetAbility(m_nSelectedAbility));
					}
				}
			}
		}
		break;
	case INPUT_CANCEL:
		{
			if (m_pSelectedUnit == nullptr)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				CStateStack::GetInstance()->Push(CPauseState::GetInstance());
			}
			else if (m_pSelectedUnit != nullptr)
			{
				if (m_bIsMoving)
				{
					m_bIsMoving = false;
					m_vWaypoints.clear();
					SnapToPosition(m_pSelectedUnit->GetPos());
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

					//PUT_SOUND_HERE("Some kind of accept sound");
				}
				else if (m_bIsTargeting)
				{
					m_bIsTargeting = false;
					SnapToPosition(m_pSelectedUnit->GetPos());
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

					//PUT_SOUND_HERE("Some kind of accept sound");
				}
				else if (m_bSelectChampionAbility)
				{
					m_bSelectChampionAbility = false;
					m_bShowSpellPanel = false;
					m_nSelectedSpell = 0;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

					//PUT_SOUND_HERE("Some kind of accept sound");
				}
				else if ( m_bIsFacing )
				{
					m_bIsFacing = false;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

					//PUT_SOUND_HERE("Some kind of accept sound");
				}
				else
				{
					ClearSelections();
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				}
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
			if( m_bSelectChampionAbility )
			{
				if( dynamic_cast< CHero* >( m_pSelectedUnit )->GetCooldown(m_nSelectedSpell) == 0 )
					CStateStack::GetInstance()->Push(CSpellScrollState::GetInstance());
			}
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
	CHero* Champ = dynamic_cast<CHero*>(m_pSelectedUnit);

	if (ability == nullptr)
		return;

	if (ability->m_nNumTargets == -1) // champion spell panel
	{
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
		m_bSelectChampionAbility = true;
		return;
	}

	if( ability->m_nNumTargets == -2)
	{
		CStateStack::GetInstance()->Push(CSpellScrollState::GetInstance());		
	}

	if( ability->GetType() == SP_VOLLEY )
	{
		if( m_pSelectedUnit->GetTilesMoved() != 0 )
			return;
	}
					
	CGameManager* pGM = CGameManager::GetInstance();
	if( ability->GetType() == SP_SPAWNARCHER )
	{
		if( pGM->GetCurrentPlayer()->GetPopCap() > pGM->GetCurrentPlayer()->GetMaxPopCap() || pGM->GetCurrentPlayer()->GetMetal() < 5 || pGM->GetCurrentPlayer()->GetWood() < 15 )
		{
			return;
		}
	}

	if( ability->GetType() == SP_SPAWNCALV )
	{
		if( pGM->GetCurrentPlayer()->GetPopCap() > pGM->GetCurrentPlayer()->GetMaxPopCap() || pGM->GetCurrentPlayer()->GetMetal() < 20 || pGM->GetCurrentPlayer()->GetWood() < 20 )
		{
			return;
		}
	}
				
	if( ability->GetType() == SP_SPAWNSWORD )
	{
		if( pGM->GetCurrentPlayer()->GetPopCap() > pGM->GetCurrentPlayer()->GetMaxPopCap() || pGM->GetCurrentPlayer()->GetMetal() < 20 )
		{
			return;
		}
	}

	if (ability->m_nPhase != CGameManager::GetInstance()->GetCurrentPhase())
		return;

	// They used the movement ability
	if (m_pSelectedUnit->GetHasAttacked())
	{
		pSM->Play(pSM->GetID(_T("NO")),false,false);
		return;
	}

	if (ability->GetType() == SP_MOVE)
	{
		if( m_pSelectedUnit->GetEffect(SP_STAND) == false && m_pSelectedUnit->GetEffect(SP_LIGHTSTRIKE) == false )
		{
			m_bIsMoving = true;
			return;
		}
		else 
			return;
	}
	else
	{
		if (ability->m_nNumTargets == 2)
		{
			if( m_bIsFacing == false && ability->GetIfFacing() == true )
			{
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				m_bIsFacing = true;
				return;
			}

			if ( m_pTargetedTile == nullptr && m_bIsTargeting == false)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				m_bIsTargeting = true;
				return;
			}
			else if (m_bIsTargeting == true && m_pTargetedTile == nullptr)
			{
				return;
			}
			else if (m_bIsTargeting == true && m_pTargetedTile != nullptr)
			{
				if( m_p2Target == nullptr )
				{
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_p2Target = CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition());
					return;
				}
				else
				{
					if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()) != nullptr )
						return;

					if( m_pTargetedTile->GetTileType() == TT_WATER )
						return;

					CParticleManager::GetInstance()->LoadParticles(PT_RAISEDEAD, TranslateToPixel(m_p2Target->GetPos()));
					CAbilityManager::GetInstance()->UseAbility(ability, CTileManager::GetInstance()->GetTile(m_p2Target->GetPos().nPosX, m_p2Target->GetPos().nPosY), m_pSelectedUnit);

					dynamic_cast< CHero* >(m_pSelectedUnit)->SetCooldown(m_nSelectedSpell, ability->GetCoolDown());
					int ap = CGameManager::GetInstance()->GetCurrentPlayer()->GetAP();

					if(  ap == 0 )
						return; 
					else
						CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(ap - ability->GetApCost());

					std::ostringstream aposs;
					aposs << "-" << ability->GetApCost();
					CFloatingText::GetInstance()->AddScreenText(aposs.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
								// STATS SAVING
					CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;

					m_p2Target = nullptr;
					m_pTargetedTile = nullptr;
					m_pSelectedUnit = nullptr;
					m_bIsTargeting = false;
					m_bIsFacing = false;
				}
			}
		}
		else if (ability->m_nNumTargets == 1)
		{
			if( m_bIsFacing == false && ability->GetIfFacing() == true )
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				m_bIsFacing = true;
				return;
			}

			if ( m_pTargetedTile == nullptr && m_bIsTargeting == false)
			{
				m_bIsTargeting = true;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);	
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
					pSM->Play(pSM->GetID(_T("NO")),false,false);
					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					return;
				}
				if (m_pSelectedUnit->GetHasAttacked())
				{
					pSM->Play(pSM->GetID(_T("NO")),false,false);
					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					return;
				}

				if( m_pSelectedUnit->GetType() == UT_HERO )
				{
					Champ = dynamic_cast<CHero*>(m_pSelectedUnit);
					//CoolDown Check here

					if (Champ->GetCooldown(m_nSelectedSpell)<0)
					{
						pSM->Play(pSM->GetID(_T("NO")),false,false);
						return;
					}
				}

				// cast the spell!
				if( ability->GetType() == SP_SPAWNARCHER || ability->GetType() == SP_SPAWNSWORD || ability->GetType() == SP_SPAWNCALV || ability->GetType() == SP_ICEBLOCK )
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
								//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap() + 1 );
								pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 5 );
								pGM->GetCurrentPlayer()->SetWood(pGM->GetCurrentPlayer()->GetWood() - 15 );

								// Stats saving!
								pGM->GetCurrentPlayer()->GetStats()->nPlayerMetalSpent+=5;
								pGM->GetCurrentPlayer()->GetStats()->nPlayerWoodSpent+=15;
								CFloatingText::GetInstance()->AddScreenText("-15", Vec2Df(650, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
								CFloatingText::GetInstance()->AddScreenText("-5", Vec2Df(724, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255,20, 20));
								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ARCHER, 2, false, 12);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ARCHER, 0, false, 12);

								CMessageSystem::GetInstance()->SendMessageW(msg);
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("teleport")), false, false);
							}
							break;

						case SP_SPAWNSWORD:
							{
								//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap()+1);
								pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 20 );
								// Stats saving!
								pGM->GetCurrentPlayer()->GetStats()->nPlayerMetalSpent+=20;

								CFloatingText::GetInstance()->AddScreenText("-20", Vec2Df(650, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
									
								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_SWORDSMAN, 2, false, 20);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_SWORDSMAN, 0, false, 20);
								CMessageSystem::GetInstance()->SendMessageW(msg);
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("teleport")), false, false);
							}
							break;

						case SP_SPAWNCALV:
							{
								//pGM->GetCurrentPlayer()->SetPopCap(pGM->GetCurrentPlayer()->GetPopCap()+1);
								pGM->GetCurrentPlayer()->SetMetal(pGM->GetCurrentPlayer()->GetMetal() - 20 );
								pGM->GetCurrentPlayer()->SetWood(pGM->GetCurrentPlayer()->GetWood() - 20 );
								CFloatingText::GetInstance()->AddScreenText("-20", Vec2Df(650, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
								CFloatingText::GetInstance()->AddScreenText("-20", Vec2Df(724, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
								// Stats saving!
								pGM->GetCurrentPlayer()->GetStats()->nPlayerMetalSpent+=20;
								pGM->GetCurrentPlayer()->GetStats()->nPlayerWoodSpent+=20;
									
								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_CAVALRY, 2, false, 22);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_CAVALRY, 0, false, 22);
								CMessageSystem::GetInstance()->SendMessageW(msg);
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("teleport")), false, false);
							}
							break;

						case SP_ICEBLOCK:
							{
								if( cur == 0 )
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ICEBLOCK, 2, false, 22);
								else
									msg = new CSpawnUnitMessage(m_pTargetedTile->GetPosition(), cur, UT_ICEBLOCK, 0, false, 22);
								CMessageSystem::GetInstance()->SendMessageW(msg);
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("ice")), false, false);
							}
							break;
						}


						int ap = CGameManager::GetInstance()->GetCurrentPlayer()->GetAP();
						if(  ap == 0 )
							return;
						else
							CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(ap - ability->GetApCost());
						std::ostringstream aposs;
						aposs << "-" << ability->GetApCost();
						CFloatingText::GetInstance()->AddScreenText(aposs.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
									// STATS SAVING
						CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;
						Vec2D t;
						t.nPosX = m_pTargetedTile->GetPosition().nPosX;
						t.nPosY = m_pTargetedTile->GetPosition().nPosY;
						CParticleManager::GetInstance()->LoadParticles(PT_SPAWN, TranslateToPixel(t));

						m_pTargetedTile = nullptr;
						m_pSelectedUnit = nullptr;
						m_bIsTargeting = false;
						m_bIsFacing = false;
					}
				}
				else if (ability->GetType() == SP_MELEEATTACK || ability->GetType() == SP_ARCHERRANGEDATTACK)
				{
					if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition().nPosX, m_pTargetedTile->GetPosition().nPosY) == m_pSelectedUnit )
						return;

					if( ability->GetType() == SP_MELEEATTACK )
						CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Sword")), false, false);
					else
						CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("ArcherBasicAttack")), false, false);

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
										switch (m_pSelectedUnit->GetType())
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

										if( pUnit->GetEffect(SP_FORT) == false || pUnit->GetEffect(SP_STAND) == false )
										{
											pUnit->SetHP(pUnit->GetHP() - m_pSelectedUnit->GetAttack());

											if( m_pSelectedUnit->GetEffect(SP_VAMP) == true )
											{
												if( m_pSelectedUnit->GetHP() < m_pSelectedUnit->GetMaxHP() )
												{
													m_pSelectedUnit->SetHP(m_pSelectedUnit->GetHP() + m_pSelectedUnit->GetAttack() / 2);
													Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
													std::ostringstream oss;
													oss << m_pSelectedUnit->GetAttack() / 2;
													CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
															Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
												}
												else
												{
													Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
													CFloatingText::GetInstance()->AddText("0", Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
															Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
												}
											}
										}
										else if ( pUnit->GetEffect(SP_FORT) )
										{
											pUnit->SetHP(int(pUnit->GetHP() - (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f))));

											if( m_pSelectedUnit->GetEffect(SP_VAMP) == true )
											{
												if( m_pSelectedUnit->GetHP() < m_pSelectedUnit->GetMaxHP() )
												{
													if ( pUnit->GetEffect(SP_STAND) == false )
													{
														m_pSelectedUnit->SetHP(m_pSelectedUnit->GetHP() + int(m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f)));
														Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
														std::ostringstream oss;
														oss << (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f));
														CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
																Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
													 }
													 else
													 {
														 m_pSelectedUnit->SetHP(m_pSelectedUnit->GetHP() + int(m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f)) / 2);
														Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
														std::ostringstream oss;
														oss << (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f)) / 2;
														CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
																Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
													 }
												}
												else
												{
													Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
													CFloatingText::GetInstance()->AddText("0", Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
															Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
												}
											}
										}
										else if ( pUnit->GetEffect(SP_STAND) )
										{
											pUnit->SetHP(int(pUnit->GetHP() - (m_pSelectedUnit->GetAttack() / 2)));
											Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
											std::ostringstream oss;
											oss << m_pSelectedUnit->GetAttack() / 2;
											CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
													Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
										}

										if(pUnit->GetHP() > 0)
											pSM->Play(pSM->GetID(_T("hurt")), false, false);
										Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
										std::ostringstream oss;
										
										if( pUnit->GetEffect(SP_FORT) == false )
											oss << m_pSelectedUnit->GetAttack();
										else
											oss << (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f));

										CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
											Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 0, 0));
									}
									else
									{
										pUnit->RemoveEffect(SP_SHIELD);
										CParticleManager::GetInstance()->StopLoop(PT_SHIELD);
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
									Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
									std::ostringstream oss;
									oss << "Dodged!";
									CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX, (float)pixelPos.nPosY), 
										Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
								}
							}
							else
							{
								if( pUnit->GetShielded() == false )
								{
										// STATS SAVING
									CPlayer* pSavePlayer = CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID());
									switch (m_pSelectedUnit->GetType())
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

									if( pUnit->GetEffect(SP_FORT) == false )
									{
										pUnit->SetHP(pUnit->GetHP() - m_pSelectedUnit->GetAttack());

										if( m_pSelectedUnit->GetEffect(SP_VAMP) == true )
										{
											if( m_pSelectedUnit->GetHP() < m_pSelectedUnit->GetMaxHP() )
											{
												m_pSelectedUnit->SetHP(m_pSelectedUnit->GetHP() + m_pSelectedUnit->GetAttack() / 2);
												Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
												std::ostringstream oss;
												oss << m_pSelectedUnit->GetAttack() / 2;
												CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
														Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
											}
											else
											{
												Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
												CFloatingText::GetInstance()->AddText("0", Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
														Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
											}
										}
									}
									else
									{
										pUnit->SetHP(int(pUnit->GetHP() - (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f))));

										if( m_pSelectedUnit->GetEffect(SP_VAMP) == true )
										{
											if( m_pSelectedUnit->GetHP() < m_pSelectedUnit->GetMaxHP() )
											{
												m_pSelectedUnit->SetHP(m_pSelectedUnit->GetHP() + int(m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f)) / 2);
												Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
												std::ostringstream oss;
												oss << (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f)) / 2;
												CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
														Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
											}
											else
											{
												Vec2D pixelPos = TranslateToPixel(m_pSelectedUnit->GetPos());
												CFloatingText::GetInstance()->AddText("0", Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
														Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
											}
										}
									}

									if(pUnit->GetHP() > 0)
										pSM->Play(pSM->GetID(_T("hurt")), false, false);
									Vec2D pixelPos = TranslateToPixel(pUnit->GetPos());
									std::ostringstream oss;
										
									if( pUnit->GetEffect(SP_FORT) == false )
										oss << m_pSelectedUnit->GetAttack();
									else
										oss << (m_pSelectedUnit->GetAttack() - (m_pSelectedUnit->GetAttack() * .75f));

									CFloatingText::GetInstance()->AddText(oss.str(), Vec2Df((float)pixelPos.nPosX + 38, (float)pixelPos.nPosY), 
										Vec2Df(0.0f, -50.0f), 1.0f, 0.4f, D3DCOLOR_XRGB(255, 0, 0));
								}
								else
								{
									pUnit->RemoveEffect(SP_SHIELD);
									CParticleManager::GetInstance()->StopLoop(PT_SHIELD);
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
						std::ostringstream aposs;
						aposs << "-" << ability->GetApCost();
						CFloatingText::GetInstance()->AddScreenText(aposs.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
					
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
						}
						
						//ADD BASIC ATTACK ANIMATION HERE
						if (ability->m_bIsAttack)
						{
							int xDistance = m_pSelectedUnit->GetPos().nPosX - m_pTargetedTile->GetPosition().nPosX;
							int yDistance = m_pSelectedUnit->GetPos().nPosY - m_pTargetedTile->GetPosition().nPosY;
							if (yDistance == 1)
								m_pSelectedUnit->SetFacing(0);
							else if (yDistance == -1)
								m_pSelectedUnit->SetFacing(2);
							else if (xDistance == -1)
								m_pSelectedUnit->SetFacing(1);
							else if (xDistance == 1)
								m_pSelectedUnit->SetFacing(3);
							m_pSelectedUnit->SetHasAttacked(true);
						}
						m_bIsTargeting = false;
						m_pTargetedTile = nullptr;
						m_pSelectedUnit = nullptr;
						m_bIsFacing = false;
					}
				}
				else
				{
					if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition().nPosX, m_pTargetedTile->GetPosition().nPosY) == m_pSelectedUnit )
					{
						if( ability->GetDamage() > 0 )
							return;
					}

					if( ability->GetType() == SP_VOLLEY )
						ability->m_nRange = m_pSelectedUnit->GetRange();

					if( ability->GetType() == SP_CHARGE || ability->GetType() == SP_RUSH )
					{
						if( CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()) != nullptr )
							return;

						if( m_pTargetedTile->GetTileType() == TT_WATER )
							return;

						std::vector<Vec2D> vec = CAbilityManager::GetInstance()->GetProperFacing( m_pSelectedUnit->GetFacing(), ability, m_pTargetedTile );
						bool inrange = false;
						for( unsigned int i = 0; i < vec.size(); i++ )
						{
							Vec2D t;
							t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
							t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
							if( m_pTargetedTile->GetPosition() == t )
							{
								inrange = true;
								break;
							}
						}

						if( inrange == false )
							return;
					}

					int nDistance = (int)(abs(double(m_pSelectedUnit->GetPos().nPosX - m_pTargetedTile->GetPosition().nPosX)) +
						abs(double(m_pSelectedUnit->GetPos().nPosY - m_pTargetedTile->GetPosition().nPosY)));

					if (nDistance > ability->GetRange())
						return;

					CAbilityManager* pAM = CAbilityManager::GetInstance();

					if( ability->GetType() == SP_CHARGE || ability->GetType() == SP_RUSH)
					{
						CTileManager* pTM = CTileManager::GetInstance();
						m_bIsMoving = true;
						m_pSelectedUnit->AddWaypoint(m_pTargetedTile);
						pAM->UseAbility(ability, pTM->GetTile( m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY) , m_pSelectedUnit, m_pTargetedTile);
						CParticleManager::GetInstance()->LoadParticles(PT_MOVE, m_pSelectedUnit->GetPos(), m_pSelectedUnit);
					}
					else
						pAM->UseAbility(ability, m_pTargetedTile, m_pSelectedUnit);

					// STATS SAVING
					CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;
					CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() - ability->m_nAPCost);
						std::ostringstream aposs;
						aposs << "-" << ability->GetApCost();
						CFloatingText::GetInstance()->AddScreenText(aposs.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
					
					if (ability->m_bIsAttack && ability->GetType() != SP_CHARGE && ability->GetType() != SP_RUSH )
						m_pSelectedUnit->SetHasAttacked(true);
					else if ( ability->GetType() == SP_CHARGE || ability->GetType() == SP_RUSH )
						m_pSelectedUnit->SetCharging(true);

					if( Champ != nullptr && ability->GetType() != SP_CHARGE && ability->GetType() != SP_RUSH )
						Champ->SetCooldown(m_nSelectedSpell, ability->GetCoolDown());

					if( ability->GetIfFacing() && ability->GetType() != SP_CHARGE && ability->GetType() != SP_RUSH )
					{
						std::vector<Vec2D> vec = CAbilityManager::GetInstance()->GetProperFacing( m_pSelectedUnit->GetFacing(), ability, m_pTargetedTile );
						int size = (int)vec.size()-1;
						for( int i = 0; i <= size; i++ )
						{
							Vec2D t;
							t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
							t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
							Vec2D tmp = TranslateToPixel(t);
							tmp.nPosX += 65;
							tmp.nPosY += 5;
							CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp, CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()));
						
							if( m_pTargetedTile->GetPosition() == t )
								break;
						}
					}
					else if( ability->GetType() != SP_CHARGE && ability->GetType() != SP_RUSH )
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
							CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp, CGameManager::GetInstance()->FindUnit(m_pTargetedTile->GetPosition()));
						}
					}

					m_bIsTargeting = false;
					m_pTargetedTile = nullptr;
					m_pSelectedUnit = nullptr;
					m_bSelectChampionAbility = false;
					m_bIsFacing = false;
				}
				ClearSelections();
			}

		}
		else if (ability->m_nNumTargets == 0) // AOE spell
		{
			if( m_bIsFacing == false && ability->GetIfFacing() == true )
			{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				m_bIsFacing = true;
				return;
			}

			CAbilityManager* pAM = CAbilityManager::GetInstance();
			pAM->UseAbility(ability, CTileManager::GetInstance()->GetTile(m_pSelectedUnit->GetPos().nPosX, 
				m_pSelectedUnit->GetPos().nPosY), m_pSelectedUnit);

			CGameManager::GetInstance()->GetCurrentPlayer()->SetAP(CGameManager::GetInstance()->GetCurrentPlayer()->GetAP() - ability->m_nAPCost);
						std::ostringstream aposs;
						aposs << "-" << ability->GetApCost();
						CFloatingText::GetInstance()->AddScreenText(aposs.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
			// STATS SAVING
			CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerAPSpent+=ability->m_nAPCost;

			if (ability->m_bIsAttack)
				m_pSelectedUnit->SetHasAttacked(true);

			if( m_pSelectedUnit->GetType() == UT_HERO && Champ != nullptr )
				Champ->SetCooldown(m_nSelectedSpell, ability->GetCoolDown());

			if( ability->GetIfFacing() )
			{
				std::vector<Vec2D> vec = CAbilityManager::GetInstance()->GetProperFacing( m_pSelectedUnit->GetFacing(), ability, m_pTargetedTile );
				int size = (int)vec.size()-1;
				for( int i = 0; i <= size; i++ )
				{
					Vec2D t;
					t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
					t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
					Vec2D tmp = TranslateToPixel(t);
					tmp.nPosX += 10;
					tmp.nPosY -= 10;
					CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp);
				}
			}
			else if( ability->GetType() != SP_FORT && ability->GetType() != SP_VAMP && ability->GetType() != SP_ENCASE )
			{
				std::vector<Vec2D> vec = ability->GetPattern();
				for( unsigned int i = 0; i < vec.size(); i++ )
				{
					Vec2D t;
					t.nPosX = vec[i].nPosX + m_pSelectedUnit->GetPos().nPosX;
					t.nPosY = vec[i].nPosY + m_pSelectedUnit->GetPos().nPosY;
					Vec2D tmp = TranslateToPixel(t);
					tmp.nPosX;
					tmp.nPosY;
					CParticleManager::GetInstance()->LoadParticles(ability->GetParticleType(), tmp);
				}
			}

			m_bIsTargeting = false;
			m_pTargetedTile = nullptr;
			m_pSelectedUnit = nullptr;
			m_bSelectChampionAbility = false;
			m_bIsFacing = false;
		}
	}		

}

// Attempts to move the selectedUnit to the tile at position nTilePosition
void CGameplayState::MoveToTile(Vec2D nTilePosition)
{
	if (m_pSelectedUnit == nullptr)
		return;
	// Cheapest movement algorithm hooray
	CTileManager* pTM = CTileManager::GetInstance();
	CTile* pStartTile = pTM->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY);
	CTile* pTargetTile = pTM->GetTile(nTilePosition.nPosX, nTilePosition.nPosY);

	// Check if where we are going to is Impassable and occupied, if so, return out of function
	if (pTargetTile == nullptr)
		return;
	if (pTargetTile->GetIfImpassable() || pTargetTile->GetIfOccupied())
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

	std::vector<CTile*> vWaypsToAdd;
	// If the total AP cost of the move is more than we have, return out. We can't afford to move


	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-029
	// BUG FIX START
	/////////////////////////////////////////////////////////////////

	// Updated this so that instead of just returning if totalcost of move is greater than
	// total player AP, it spends what it can to move as far as it can on the final cost.

	if (nTotalAPCost > CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP())
	{
		// Lets only add the waypoints we can afford
		int nTestAP = CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP();
		int nAPSpent = 0;
		while (nTestAP > 0)
		{
			int nTileAP = m_vWaypoints.back()->GetAPCost();
			if (nTileAP > nTestAP)
				break;
			if (nTileAP <= nTestAP)
			{
				vWaypsToAdd.insert(vWaypsToAdd.begin(), m_vWaypoints.back());
				m_vWaypoints.pop_back();
				//nCount++;
				nTestAP -= nTileAP;
				nAPSpent += nTileAP;
			}
		}
		nTotalAPCost = nAPSpent;
	}
	else
	{
		vWaypsToAdd = m_vWaypoints;
	}

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-029
	/////////////////////////////////////////////////////////////////

	std::ostringstream oss;
	oss << "-" << nTotalAPCost;
	CFloatingText::GetInstance()->AddScreenText(oss.str(), Vec2Df(450, 546), Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));
	// If we're here, we're movin. Subtract the cost of the move from the player's AP
	CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->SetAP(
		CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP() - nTotalAPCost);

	// STATS SAVING
	CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetStats()->nPlayerAPSpent += nTotalAPCost;

	// Add the tile waypoints to the unit so that he can slide along them neatly

	for (unsigned int i = 0; i < vWaypsToAdd.size(); ++i)
	{
		m_pSelectedUnit->AddWaypoint(vWaypsToAdd[i]);
	}
	// After we hit enter we want to cancel and clear, either we're moving or we're not.
	//m_pSelectedUnit->SetIsMoving(true);

	if (vWaypsToAdd.size() != 0)
	{
		if( m_pSelectedUnit->GetType() == UT_CAVALRY )
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Gallop")), true, false);
		else
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("Footstep")), true, false);

		CParticleManager::GetInstance()->LoadParticles(PT_MOVE, m_pSelectedUnit->GetPos(), m_pSelectedUnit);

		unsigned int numMoves = m_pSelectedUnit->GetSpeed() - m_pSelectedUnit->GetTilesMoved();
		if (vWaypsToAdd.size() >=(unsigned int) numMoves)
		{
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-014
			// BUG FIX START
			/////////////////////////////////////////////////////////////////

			// Was running down the waypoint list backwards last time, resulting in random tiles being flagged
			// occupied incorrectly, resulting in pathfinding later on in the game thinking that tile is occupied
			int index = vWaypsToAdd.size() -1;
			index -= (numMoves -1);

			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-014
			/////////////////////////////////////////////////////////////////

			vWaypsToAdd[index]->SetIfOccupied(true);
		}
		if (vWaypsToAdd.size() < (unsigned int) numMoves)
		{
			vWaypsToAdd.front()->SetIfOccupied(true);
		}
	}
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_vWaypoints.clear();
	return;
}

// Uses A* pathfinding algorithm to find a cheap route from startTile to targetTile
bool CGameplayState::CalculateMove(CTile* startTile, CTile* targetTile, std::vector<CTile*>& m_vVector)
{

	// If either of the tiles are null or we can't move into the last tile, don't calculate anything.
	if (startTile == nullptr || targetTile == nullptr || targetTile->GetIfOccupied() || targetTile->GetIfImpassable())
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

	int nNumTilesFound = 0;

	while (true && (safeCheck < 1000))
	{
		// This loop will go through and check all tiles adjacent to our active tile. If they are legit tiles
		// I.E not null, are Impassable and are not occupied, then we add them to our openList of available tiles to move
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
			bool pPass = !(pTestTile->GetIfImpassable());
			bool pOcc = !(pTestTile->GetIfOccupied());
			if (iter == closedList.end() && !(pTestTile->GetIfImpassable()) && !(pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					int testCost = n->nCost + pTestTile->GetAPCost();
					if (testCost < (*iter)->nCost)
					{
						(*iter)->parent = n;
						(*iter)->nCost = testCost;
						(*iter)->nF = pTestTile->GetAPCost() + n->nH;
					}
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
					newNode->nH = (abs(xDist) + abs(yDist)) * nEstimatedTileCost;
					//newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
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
			if (iter == closedList.end() && (!pTestTile->GetIfImpassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					int testCost = n->nCost + pTestTile->GetAPCost();
					if (testCost < (*iter)->nCost)
					{
						(*iter)->parent = n;
						(*iter)->nCost = testCost;
						(*iter)->nF = pTestTile->GetAPCost() + n->nH;
					}
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
					newNode->nH = (abs(xDist) + abs(yDist)) * nEstimatedTileCost;
					//newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
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
			if (iter == closedList.end() && (!pTestTile->GetIfImpassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					int testCost = n->nCost + pTestTile->GetAPCost();
					if (testCost < (*iter)->nCost)
					{
						(*iter)->parent = n;
						(*iter)->nCost = testCost;
						(*iter)->nF = pTestTile->GetAPCost() + n->nH;
					}
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
					newNode->nH = (abs(xDist) + abs(yDist)) * nEstimatedTileCost;
					//newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
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
			if (iter == closedList.end() && (!pTestTile->GetIfImpassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					int testCost = n->nCost + pTestTile->GetAPCost();
					if (testCost < (*iter)->nCost)
					{
						(*iter)->parent = n;
						(*iter)->nCost = testCost;
						(*iter)->nF = pTestTile->GetAPCost() + n->nH;
					}
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
					newNode->nH = (abs(xDist) + abs(yDist)) * nEstimatedTileCost;
					//newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
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

		nNumTilesFound = closedList.size();
		if (nNumTilesFound >= 200)
			break;
	}

	// if we didnt find anything, get out of here
	if (closedList.size() == 0)
	{
		return false;
	}

	// Go through the list of found tiles and add them to our waypoints of our path
	ASNode* nNode = closedList.back();
	safeCheck = 0;
		if (nNode->pTile != targetTile)
		{
			m_vVector.clear();
		}
		else
		{
		while (nNode->parent != nullptr && (safeCheck < 5000))
		{
			m_vVector.push_back(nNode->pTile);
			nNode = nNode->parent;
		}
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
	//PUT_SOUND_HERE("Some kind of accept sound");
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

	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-024	
	// BUG FIX START
	/////////////////////////////////////////////////////////////////

	// I took out the code that was doing it :\

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-024
	/////////////////////////////////////////////////////////////////

	if (m_bDayTime)
	{
		m_nDayAlphaScale += 10;
		if (m_nDayAlphaScale >= 255)
			m_nDayAlphaScale = 255;
		m_nNightAlphaScale -= 10;
		if (m_nNightAlphaScale <= 0)
			m_nNightAlphaScale = 0;
	}
	else
	{
		m_nDayAlphaScale -= 10;
		if (m_nDayAlphaScale <= 0)
			m_nDayAlphaScale = 0;
		m_nNightAlphaScale += 10;
		if (m_nNightAlphaScale >= 255)
			m_nNightAlphaScale = 255;

	}
	if (m_bIsHighlighting == true)
	{
		if (m_nCardOffsetX < m_nCardOffsetMaxX)
		{
			m_nCardOffsetX += (int)(450 * fElapsedTime);
		}
		if (m_nCardOffsetX > m_nCardOffsetMaxX)
			m_nCardOffsetX = m_nCardOffsetMaxX;
		if (m_nCardOffsetX >  -165)
			m_bShowingCard = true;
	}
	else
	{
		m_nCardOffsetX -= (int)(450 * fElapsedTime);
		if (m_nCardOffsetX <= -165)
			m_nCardOffsetX = -165;
	}

	if (m_pSelectedUnit != nullptr)
	{
		if (m_nTooltipOffsetY > m_nTooltipOffsetMaxY)
		{
			m_nTooltipOffsetY -= (int)(450 * fElapsedTime);
		}

		if (m_nTooltipOffsetY < m_nTooltipOffsetMaxY)
			m_nTooltipOffsetY = m_nTooltipOffsetMaxY;
	}
	else
	{
		m_nTooltipOffsetY += (int)(450 * fElapsedTime);
		if (m_nTooltipOffsetY > 620)
			m_nTooltipOffsetY = 620;
	}
	if (m_nSpellPanelOffsetY < CGame::GetInstance()->GetWindowHeight())
			m_bShowSpellPanel = true;
	if (m_bSelectChampionAbility)
	{
		if (m_nSpellPanelOffsetY > m_nSpellPanelOffsetYMAX)
		{
			m_nSpellPanelOffsetY -= (int)(650 * fElapsedTime);
		}
		if (m_nSpellPanelOffsetY < m_nSpellPanelOffsetYMAX)
			m_nSpellPanelOffsetY = m_nSpellPanelOffsetYMAX;


	}
	else
	{
		m_nSpellPanelOffsetY += (int)(650 * fElapsedTime);
		if (m_nSpellPanelOffsetY > CGame::GetInstance()->GetWindowHeight())
			m_nSpellPanelOffsetY = CGame::GetInstance()->GetWindowHeight();
	}
	// Testing Particle Rendering
	CAIManager::GetInstance()->UpdateAI(fElapsedTime);

	CParticleManager::GetInstance()->Update(fElapsedTime);
	CObjectManager::GetInstance()->UpdateAllObjects(fElapsedTime);
	CAnimationManager::GetInstance()->Update(fElapsedTime);
	CGameManager::GetInstance()->Update(fElapsedTime);
	CFloatingText::GetInstance()->Update(fElapsedTime);
	if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")))
		&& CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
	{
		CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic")),true);
		CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic")),true);
		CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(0.0f);
		CSoundManager::GetInstance()->Play(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")),true,true);
		TiXmlDocument doc;
		doc.LoadFile("Assets\\Menus\\Options.xml");
		TiXmlElement* pRoot = doc.RootElement();
		TiXmlElement* Option = pRoot->FirstChildElement("Option");
		while(Option != nullptr)
		{
			Option->Attribute("MusicVolume", &musicvolume);
			Option = Option->NextSiblingElement("Option");
		}
	}
	if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic"))) 
		&& CGameManager::GetInstance()->GetCurrentPhase() == GP_ATTACK)
	{
		CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic")),true);
		CSoundManager::GetInstance()->Stop(CSoundManager::
		GetInstance()->GetID(_T("MovementPhaseMusic")),true);
		CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(0.0f);
		CSoundManager::GetInstance()->Play(CSoundManager::
		GetInstance()->GetID(_T("AttackPhaseMusic")),true,true);
		TiXmlDocument doc;
		doc.LoadFile("Assets\\Menus\\Options.xml");
		TiXmlElement* pRoot = doc.RootElement();
		TiXmlElement* Option = pRoot->FirstChildElement("Option");
		while(Option != nullptr)
		{
			Option->Attribute("MusicVolume", &musicvolume);
			Option = Option->NextSiblingElement("Option");
		}
	}
	if(MusicIncrease < float(musicvolume*0.01f))
	{
		CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(MusicIncrease);
		MusicIncrease += 0.001f;
	}
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
	CHUD* pHud = CHUD::GetInstance();
	RECT hudRECT;
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);
	//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("skybox")), 0, 0);
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
			//CGraphicsManager::GetInstance()->DrawWireframeRect(tileRect, r, g, b);
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
			if( drawAbility->GetType() == SP_VOLLEY )
					drawAbility->m_nRange = m_pSelectedUnit->GetRange();

			std::vector< Vec2D > pattern, range;
			if (drawAbility->GetType() == SP_ARCHERRANGEDATTACK || drawAbility->GetType() ==SP_MELEEATTACK)
				range = CAbilityManager::GetInstance()->GetRange(m_pSelectedUnit->GetRange());				
			else
			{
				if( drawAbility->GetIfFacing() )
				{
					range = CAbilityManager::GetInstance()->GetProperFacing(m_pSelectedUnit->GetFacing(), drawAbility, 
												CTileManager::GetInstance()->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY));
				}
				else
					range = CAbilityManager::GetInstance()->GetRange(drawAbility->GetRange());
			}

			if(  !drawAbility->GetIfFacing() )
			{
				pattern = CAbilityManager::GetInstance()->GetProperFacing(m_pSelectedUnit->GetFacing(), drawAbility, 
												CTileManager::GetInstance()->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY));
			}

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
	{
		if (CGameManager::GetInstance()->GetCurrentLevel() != 5)
		{
		CGraphicsManager::GetInstance()->DrawWireframeDiag(diamondRect, 255, 255, 255 );
		}
		else
		{
		CGraphicsManager::GetInstance()->DrawWireframeDiag(diamondRect, 20, 20, 20 );

		}
	}
	CObjectManager::GetInstance()->RenderAllObjects();
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	//Render the map

	// Testing particle rendering
	CParticleManager::GetInstance()->Render();

	if( m_bIsFacing )
	{
		float rot;
		RECT source = {0, 0, 256, 128};
		CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

		if (m_pSelectedUnit!= nullptr)
		switch(m_pSelectedUnit->GetFacing())
		{

		case 0:
			{
				rot = -45 * 3.1415926f / 180;
				if( m_pSelectedUnit->GetPlayerID() == 1 )
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX + 60 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY - 50 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
				else
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX + 60 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY - 50 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 0, 0, 255));
				}
			}
			break;

		case 1:
			{
				rot = -315 * 3.1415926f / 180;
				if( m_pSelectedUnit->GetPlayerID() == 1 )
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX + 55 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY - GetCamOffsetY() + 55, .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
				else
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX + 55 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY + 55 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 0, 0, 255));
				}
			}
			break;

		case 2:
			{
				rot = -225 * 3.1415926f / 180;
				if( m_pSelectedUnit->GetPlayerID() == 1 )
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX - 50 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY + 60 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
				else
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX - 50 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY + 60 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 0, 0, 255));
				}
			}
			break;

		case 3:
			{
				rot = -135 * 3.1415926f / 180;
				if( m_pSelectedUnit->GetPlayerID() == 1 )
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX - 50 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY - 50 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
				else
				{
					pTM->Draw(CGraphicsManager::GetInstance()->GetID(_T("facingarrow")), TranslateToPixel(m_pSelectedUnit->GetPos()).nPosX - 50 - GetCamOffsetX(), 
						TranslateToPixel(m_pSelectedUnit->GetPos()).nPosY - 50 - GetCamOffsetY(), .3f, .3f, &source, 256 / 2, 128 / 2, rot, D3DCOLOR_ARGB(255, 0, 0, 255));
				}
			}
			break;
		}
	}

	// DAY/NIGHT
 /// BEGINNING OF INTERFACE RENDER
	if (CGameManager::GetInstance()->GetCurrentLevel() != 5)
	{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("vignette_night")), 0, -50, 1.0f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(m_nNightAlphaScale, 255, 255, 255));
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("vignette")), 0, -50, 1.0f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(m_nDayAlphaScale, 255, 255, 255));
	}
	else
	{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("vignette_snow")), 0, -50, 1.0f, 1.0f);
	}

	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("tooltip")), 200, m_nTooltipOffsetY, 1.2f, 1.2f);

	if( m_pSelectedUnit != nullptr )
	{
		if( m_bSelectChampionAbility == true )
		{	
			CHero* pHero = dynamic_cast< CHero* >(m_pSelectedUnit);
			if( pHero != nullptr )
			{
				std::ostringstream tt;
				CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
				CGraphicsManager* pGM = CGraphicsManager::GetInstance();
				CAbility* pA = pHero->GetSpell(m_nSelectedSpell);
				if (pA != nullptr)
				{
					tt << pA->GetDamage() < 0 ? abs(pA->GetDamage()) : pA->GetDamage();

					if( pA->GetType() == SP_MELEEATTACK || pA->GetType() == SP_ARCHERRANGEDATTACK )
					{
						tt.str("");
						tt << m_pSelectedUnit->GetAttack();
					}

					if( pA->GetType() == SP_VOLLEY )
					{
						tt.str("");
						tt << m_pSelectedUnit->GetAttack() * 2;
					}

					m_pBitmapFont->Print(tt.str().c_str(), 380, m_nTooltipOffsetY + 45, 0.25f, pA->GetDamage() < 0 ? D3DCOLOR_XRGB(0,255,0) : D3DCOLOR_XRGB(255,0,0));
					tt.str("");
					tt << m_pSelectedUnit->GetAttack();

					tt.str("");
					tt << pA->GetRange();

					if( pA->GetType() == SP_MOVE )
					{
						tt.str("");
						tt << m_pSelectedUnit->GetSpeed();
					}

					m_pBitmapFont->Print(tt.str().c_str(), 276, m_nTooltipOffsetY + 12, 0.25f, D3DCOLOR_XRGB(255,255,255));
					tt.str("");

					tt << pA->GetCoolDown();
					m_pBitmapFont->Print(tt.str().c_str(), 276, m_nTooltipOffsetY + 45, 0.25f, D3DCOLOR_XRGB(255,255,255));
					tt.str("");

					tt << pA->GetApCost();
					m_pBitmapFont->Print(tt.str().c_str(),  376, m_nTooltipOffsetY + 12, 0.25f, D3DCOLOR_XRGB(255,255,255));
					tt.str("");

					m_pBitmapFont->Print(pA->GetDescription().c_str(), 438, m_nTooltipOffsetY + 12, 0.2f, D3DCOLOR_XRGB(255,255,255), 120);
				}
			}
		}
		else if( m_bSelectChampionAbility == false )
		{
			std::ostringstream tt;
			CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
			CGraphicsManager* pGM = CGraphicsManager::GetInstance();
			CAbility* pA = m_pSelectedUnit->GetAbility(m_nSelectedAbility);
			if (pA != nullptr)
			{
				tt << pA->GetDamage() < 0 ? abs(pA->GetDamage()) : pA->GetDamage();

				if( pA->GetType() == SP_MELEEATTACK || pA->GetType() == SP_ARCHERRANGEDATTACK )
				{
					tt.str("");
					tt << m_pSelectedUnit->GetAttack();
				}

				if( pA->GetType() == SP_VOLLEY )
				{
					tt.str("");
					tt << m_pSelectedUnit->GetAttack() * 2;
				}

				m_pBitmapFont->Print(tt.str().c_str(), 380, m_nTooltipOffsetY + 45, 0.25f, pA->GetDamage() < 0 ? D3DCOLOR_XRGB(0,255,0) : D3DCOLOR_XRGB(255,0,0));
				tt.str("");
				tt << m_pSelectedUnit->GetAttack();

				tt.str("");
				tt << pA->GetRange();

				if( pA->GetType() == SP_MOVE )
				{
					tt.str("");
					tt << m_pSelectedUnit->GetSpeed();
				}

				m_pBitmapFont->Print(tt.str().c_str(), 276, m_nTooltipOffsetY + 12, 0.25f, D3DCOLOR_XRGB(255,255,255));
				tt.str("");

				tt << pA->GetCoolDown();
				m_pBitmapFont->Print(tt.str().c_str(), 276, m_nTooltipOffsetY + 45, 0.25f, D3DCOLOR_XRGB(255,255,255));
				tt.str("");

				tt << pA->GetApCost();
				m_pBitmapFont->Print(tt.str().c_str(),  376, m_nTooltipOffsetY + 12, 0.25f, D3DCOLOR_XRGB(255,255,255));
				tt.str("");

				m_pBitmapFont->Print(pA->GetDescription().c_str(), 438, m_nTooltipOffsetY + 12, 0.2f, D3DCOLOR_XRGB(255,255,255), 120);
			}
		}
	}
	//if (m_bIsMoving)
	//	CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 0, 255, 0);
	//else
	//	CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 255, 255, 255);

	// Render the UI Overlay
	// HUD PARTS

	hudRECT = pHud->GetRect(HP_MAINBAR);
	CSGD_TextureManager::GetInstance()->Draw(
		CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 210, 411, 1.0f, 1.0f, &hudRECT);

	hudRECT = pHud->GetRect(HP_UNITCARD);
	CSGD_TextureManager::GetInstance()->Draw(
		CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 577, 358, 1.0f, 1.0f, &hudRECT);

	hudRECT = pHud->GetRect(HP_MINIMAP);
	CSGD_TextureManager::GetInstance()->Draw(
		CGraphicsManager::GetInstance()->GetID(_T("hudparts")),56 ,377, 1.0f, 1.0f, &hudRECT);

	

	// MINIMAP
	int nMiniMapOffsetX = 64;
	int nMiniMapOffsetY = 385;
	RECT miniR = {nMiniMapOffsetX, nMiniMapOffsetY, nMiniMapOffsetX + 170, nMiniMapOffsetY + 152};
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	//CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	float nMiniMapWidth = 139;
	float nMiniMapHeight = 139;
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
				g=83; r=36; b=9; break;
			case TT_FOREST:
				rSrc = CellAlgorithm(TT_FOREST);
				g=70; r=16; b=4; break;
			case TT_MOUNTAINS:
				rSrc = CellAlgorithm(TT_MOUNTAINS);
				g=73;r=60; b=50; break;
			case TT_WATER:
				rSrc = CellAlgorithm(TT_WATER);
				g=56;r=4;b=116;break; 
			case TT_MINE:
				rSrc = CellAlgorithm(TT_MINE);
				g=190;r=190; b=0; break;
			case TT_MILL:
				rSrc = CellAlgorithm(TT_MILL);
				g=190; r=190; b=0; break;
			case TT_FARM:
				rSrc = CellAlgorithm(TT_FARM);
				g=190; r=190; b=0; break;
			case TT_CASTLE:
				rSrc = CellAlgorithm(TT_CASTLE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);
				//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("Map")),
			//	tileRect.left, tileRect.top, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);

			if (i == m_SelectionPos.nPosX && j == m_SelectionPos.nPosY)
			{
				CGraphicsManager::GetInstance()->DrawWireframeRect(tileRect, 255, 255, 255, true);
			}

			r = 255 * !(pTile->GetPlayerID());
			b = 255 * (pTile->GetPlayerID());
			g = 0;

	
			float fX = nMiniTileWidth / 16.0f;
			float fY = nMiniTileHeight / 16.0f;

			if (r == 0 && g == 0 && b == -255)
			{
				r = b = g = 110;
			}
			switch (pTile->GetTileType())
			{
			case TT_MILL:
			case TT_MINE:
			case TT_FARM:
				CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("minitriangle")),
					(int)tileRect.left, (int)tileRect.top, fX, fY,(RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(r,g,b));
				break;
			}
		}
		float fX = nMiniTileWidth / 16.0f;
		float fY = nMiniTileHeight / 16.0f;
		// Render the units as circles
		for (decltype(CGameManager::GetInstance()->GetUnits().size()) i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
		{
			int r = 255 * (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == 1);
			int b = 255 * (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == 0);
			int g = 0;
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("minicircle")),
				int(CGameManager::GetInstance()->GetUnits()[i]->GetPos().nPosX * nMiniTileWidth + nMiniMapOffsetX),
				int(CGameManager::GetInstance()->GetUnits()[i]->GetPos().nPosY * nMiniTileHeight + nMiniMapOffsetY),
				fX, fY, (RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(r, g, b));
		}
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	if (m_bShowingCard)
	{
		hudRECT = pHud->GetRect(HP_UNITCARD);
		CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("hudparts")),m_nCardOffsetX ,357	, 1.0f, 1.0f, &hudRECT);
		//CSGD_TextureManager::GetInstance()->Draw(
		//	CGraphicsManager::GetInstance()->GetID(_T("showcard")), m_nCardOffsetX, 356, 1.0f, 0.8f);
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
		if (m_pHighlightedUnit != nullptr)
		{
			std::ostringstream moss;
			hudRECT = pHud->GetPortrait(m_pHighlightedUnit->GetType());
			CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("hudparts")), m_nCardOffsetX + 10, 368, 1.08f, 1.11f,
				&hudRECT);

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("speedicon")),
			//	m_nCardOffsetX + 150, 248, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetSpeed();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 255, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 124, 506, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			moss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("damageicon")),
			//	m_nCardOffsetX + 150, 288, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetAttack();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 295, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 49, 472
				, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			moss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("rangeicon")),
			//	m_nCardOffsetX + 150, 338, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetRange();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 345, 255, 255, 255);
			m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 49, 506, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			moss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("tilesmovedicon")),
			//	m_nCardOffsetX + 150, 378, 0.5f, 0.5f);
			moss << m_pHighlightedUnit->GetTilesMoved();
			m_pBitmapFont->Print(moss.str().c_str(),m_nCardOffsetX + 124, 472, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 200, 385, 255, 255, 255);
			moss.str((""));

			if (m_pHighlightedUnit->GetDodgeChance() > 0.0f)
			{
				moss << "Dodge: " << (m_pHighlightedUnit->GetDodgeChance() * 100) << "%";
				//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 15, 222, 255, 255, 255);
				m_pBitmapFont->Print(moss.str().c_str(), m_nCardOffsetX + 23, 341, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

				moss.str((""));

			}
			float fhpPercent = (float)m_pHighlightedUnit->GetHP() / (float)m_pHighlightedUnit->GetMaxHP();

			int colR = 0, colG = 255;
			if (fhpPercent < 0.80f)
			{
				colR += 128; 
			}
			if (fhpPercent < 0.60f)
			{
				colR += 128; 
			}
			if (fhpPercent < 0.40f)
			{
				colG -= 128; 
			}
			if (fhpPercent < 0.20f)
			{
				colG -= 128; 
			}
			if (colR > 255)
				colR = 255;
			if (colG < 0)
				colG = 0;
			//RECT hpRect = { m_nCardOffsetX + 20, 350, m_nCardOffsetX + 20 + (LONG)(102 * fhpPercent), 360 };
			//CSGD_Direct3D::GetInstance()->DrawRect(hpRect, colR, colG, 0);

			RECT hpRect = pHud->GetHealthbar();
			int nWidth = hpRect.right - hpRect.left;
			hpRect.right = (LONG)(hpRect.left + nWidth * fhpPercent);
			D3DCOLOR col = D3DCOLOR_XRGB(colR, colG, 0);
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("healthbar")),m_nCardOffsetX + 9, 451, 0.98f, 1.0f, &hpRect, 0.0f, 0.0f,
				0.0f, col);

			int hp = m_pHighlightedUnit->GetHP();
			std::ostringstream hposs;
			hposs << hp;
			m_pBitmapFont->Print(hposs.str().c_str(), m_nCardOffsetX + 48, 451, 0.25f, D3DCOLOR_XRGB(255, 255 ,255));

			// debuffs
			int nRow = 0;
			int nColumn = 0;
			for (int i = 0; i < m_pHighlightedUnit->GetNumEffects(); ++i)
			{
				nRow = i % 2;
				nColumn = i / 2;
				CSGD_TextureManager::GetInstance()->Draw(
					CGraphicsManager::GetInstance()->GetID(m_pHighlightedUnit->GetEffect(i)->m_szInterfaceIcon), 
					m_nCardOffsetX + 105 + nRow * 27, 370 + nColumn * 27, 0.4f, 0.4f);
			}
		}
	}

	if (m_pSelectedUnit != nullptr)
	{
		int nCursorPosX = 0;
		int nCursorPosY = 442;
		switch (m_nSelectedAbility)
		{
		default:
		case 0:
			nCursorPosX = 271;
			break;
		case 1:
			nCursorPosX = 358;
			break;
		case 2:
			nCursorPosX = 446;
			break;
		}

		RECT selectRect = pHud->GetRect(HP_SELECTICON);
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("hudparts")),
			nCursorPosX, nCursorPosY, 1.0f, 1.0f,&selectRect);

		// drawin icons. Could loop it, don't see a reason to

		CAbility* pAbility = m_pSelectedUnit->GetAbility(0);
		D3DCOLOR drawColor = D3DCOLOR_XRGB(255, 255, 255);

		if (pAbility != nullptr)
		{
			if (pAbility->GetPhase() != CGameManager::GetInstance()->GetCurrentPhase())
			{
				drawColor = D3DCOLOR_XRGB(120, 120, 120);
			}
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 275, 446, 1.0f, 1.0f, (RECT*)0, 0.0f, 0.0f,
				0.0f, drawColor);
		}
		pAbility = m_pSelectedUnit->GetAbility(1);
		drawColor = D3DCOLOR_XRGB(255,255,255);

		if (pAbility != nullptr)
		{
			if (pAbility->GetPhase() != CGameManager::GetInstance()->GetCurrentPhase())
			{
				drawColor = D3DCOLOR_XRGB(120, 120, 120);
			}
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 362, 446, 1.0f, 1.0f, (RECT*)0, 0.0f, 0.0f,
				0.0f, drawColor);
		}
		pAbility = m_pSelectedUnit->GetAbility(2);
		drawColor = D3DCOLOR_XRGB(255,255,255);
		if (pAbility != nullptr)
		{
			//TODO: AddCooldown
			if (pAbility->GetPhase() != CGameManager::GetInstance()->GetCurrentPhase())
			{
				drawColor = D3DCOLOR_XRGB(120, 120, 120);
			}

			if (pAbility->GetType() == SP_VOLLEY)
			{
				if (m_pSelectedUnit->GetTilesMoved() > 0)
				{
					drawColor = D3DCOLOR_XRGB(120, 120, 120);
				}
			}

			if (pAbility->GetType() == SP_CHAMPSPELL)
					drawColor = D3DCOLOR_XRGB(255, 255, 255);

			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(pAbility->m_szInterfaceIcon), 450, 446, 1.0f, 1.0f, (RECT*)0, 0.0f, 0.0f,
				0.0f, drawColor);
		}

		int n = CGame::GetInstance()->GetWindowWidth();
		int y = CGame::GetInstance()->GetWindowHeight();
	
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
		CHero* pHero = dynamic_cast<CHero*>(m_pSelectedUnit);

		if (m_bShowSpellPanel)
		{
			hudRECT = pHud->GetRect(HP_SPELLBAR);
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 210, m_nSpellPanelOffsetY, 1.0f, 1.0f, &hudRECT);

			if (pHero != nullptr)
			{
				for (unsigned int i = 0; i < pHero->GetNumSpells(); ++i)
				{
					if (pHero->GetCooldown(i) == 0)
					{
						if( pHero->GetSpell(i)->GetPhase() == CGameManager::GetInstance()->GetCurrentPhase() || pHero->GetSpell(i)->GetType() == SP_BLANK )
						{
							CSGD_TextureManager::GetInstance()->Draw(
								CGraphicsManager::GetInstance()->GetID(pHero->GetSpell(i)->m_szInterfaceIcon),
								233 +( i * 86), m_nSpellPanelOffsetY + 23);
						}
						else
						{
							CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(pHero->GetSpell(i)->m_szInterfaceIcon),
									233 +( i * 86), m_nSpellPanelOffsetY + 23,1.0f,1.0f,(RECT*)0,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(100,100,100));
						}
					}
					else
					{
						CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(pHero->GetSpell(i)->m_szInterfaceIcon),
									233 +( i * 86), m_nSpellPanelOffsetY + 23,1.0f,1.0f,(RECT*)0,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(100,100,100));
						CBitmapFont bitmap;
						ostringstream oss;
						oss << pHero->GetCooldown(i);
						bitmap.Print(oss.str().c_str(), 254 + (i * 86), m_nSpellPanelOffsetY + 42, 0.6f, D3DCOLOR_XRGB(255, 255, 255));
					}
					if (m_nSelectedSpell == i)
					{
						RECT iconRect = pHud->GetRect(HP_SELECTICON);
						CSGD_TextureManager::GetInstance()->Draw(
							CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 
							229 + (i * 86), m_nSpellPanelOffsetY + 19, 1.0f, 1.0f, &iconRect);
					}
				}
			}
		}
	}
	
		// UNIT CARD STUFF HOORAY
		if (m_pSelectedUnit != nullptr)
		{
			std::ostringstream woss;

			hudRECT = pHud->GetPortrait(m_pSelectedUnit->GetType());
			CSGD_TextureManager::GetInstance()->Draw(
			CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 586, 368, 1.08f, 1.11f,
				&hudRECT);

			if (m_pSelectedUnit->GetDodgeChance() > 0.0f)
			{
				woss << "Dodge: " << (m_pSelectedUnit->GetDodgeChance() * 100) << "%";
				//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)moss.str().c_str(), m_nCardOffsetX + 15, 222, 255, 255, 255);
				m_pBitmapFont->Print(woss.str().c_str(), 605, 341, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

				woss.str((""));
				
			}
			//CSGD_TextureManager::GetInstance()->Draw(m_pSelectedUnit->GetPortraitID(), 578, 435, 1.6f, 1.6f);

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("speedicon")),
			//	710, 440, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetSpeed();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 445, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 700, 506, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("damageicon")),
			//	710, 480, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetAttack();
			//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 485, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 625, 473, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("rangeicon")),
			//	710, 520, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetRange();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 525, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 625, 506, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("tilesmovedicon")),
			//	710, 560, 0.5f, 0.5f);
			woss << m_pSelectedUnit->GetTilesMoved();
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 755, 565, 255, 255, 255);
			m_pBitmapFont->Print(woss.str().c_str(), 700, 473, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			woss.str((""));

			float fhpPercent = (float)m_pSelectedUnit->GetHP() / (float)m_pSelectedUnit->GetMaxHP();

			int colR = 0, colG = 255;
			if (fhpPercent < 0.80f)
			{
				colR += 128; 
			}
			if (fhpPercent < 0.60f)
			{
				colR += 128; 
			}
			if (fhpPercent < 0.40f)
			{
				colG -= 128;
			}
			if (fhpPercent < 0.20f)
			{
				colG -= 128;
			}
			if (colR > 255)
				colR = 255;
			if (colG < 0)
				colG = 0;

			RECT hpRect = pHud->GetHealthbar();
			int nWidth = hpRect.right - hpRect.left;
			hpRect.right = (LONG)(hpRect.left + nWidth * fhpPercent);
			D3DCOLOR col = D3DCOLOR_XRGB(colR, colG, 0);
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("healthbar")),586, 451, 0.98f, 1.0f, &hpRect, 0.0f, 0.0f,
				0.0f, col);

			int hp = m_pSelectedUnit->GetHP();
			std::ostringstream hposs;
			hposs << hp;
			m_pBitmapFont->Print(hposs.str().c_str(),  625 , 450, 0.25f, D3DCOLOR_XRGB(255, 255 ,255));
			//CSGD_Direct3D::GetInstance()->DrawRect(hpRect, colR, colG, 0);

			// debuffs
			int nRow = 0;
			int nCol = 0;
			for (int i = 0; i < m_pSelectedUnit->GetNumEffects(); ++i)
			{
				nRow = i % 2;
				nCol = i / 2;
				CSGD_TextureManager::GetInstance()->Draw(
					CGraphicsManager::GetInstance()->GetID(m_pSelectedUnit->GetEffect(i)->m_szInterfaceIcon), 682 + nRow * 27,
					368 + nCol * 27, 0.4f, 0.4f);
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
			hudRECT = pHud->GetRect(HP_BORDERBAR);
			CSGD_TextureManager::GetInstance()->Draw(
				CGraphicsManager::GetInstance()->GetID(_T("hudparts")), 0, 550, 1.09f, 1.0f, &hudRECT);
			//oss.str(_T(""));
			RECT turnRect = pHud->GetRect(HP_STATUSBAR);
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("hudparts")),
				0, 532, 1.0f, 1.0f, &turnRect);



			oss << pDebugPlayer->GetAP();
			// DRAW RESOURCES
			m_pBitmapFont->Print(oss.str().c_str(), 450, 546, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			oss.str("");
			oss << pDebugPlayer->GetPopCap() << '/' << pDebugPlayer->GetMaxPopCap();
			if (pDebugPlayer->GetPopCap() >= pDebugPlayer->GetMaxPopCap())
			{
				m_pBitmapFont->Print(oss.str().c_str(), 530, 546, 0.3f, D3DCOLOR_XRGB(255, 0, 0));
			}
			else
			{
				m_pBitmapFont->Print(oss.str().c_str(), 530, 546, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			}

			oss.str("");
			oss << pDebugPlayer->GetWood();
			m_pBitmapFont->Print(oss.str().c_str(), 650, 546, 0.3f, D3DCOLOR_XRGB(255, 255, 255));
			oss.str("");
			oss << pDebugPlayer->GetMetal();
			m_pBitmapFont->Print(oss.str().c_str(), 724, 546, 0.3f, D3DCOLOR_XRGB(255, 255, 255));



			//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("hudparts")),
			//	273, -10, 1.0f, 1.0f, &turnRect, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));


			ostringstream woss;
			woss << CGameManager::GetInstance()->GetCurrentPlayer()->GetExp();
			m_pBitmapFont->Print(woss.str().c_str(),340,546,0.33f,D3DXCOLOR(255,255,255,255));
			///	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 258, 486, 255, 255, 255);
			oss.str((""));
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-004
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() == 0)
				oss << StringTable::GetInstance()->GetString("Player ") << "1 "; // Put Stringtable's GetString function here...
			else 
				oss << StringTable::GetInstance()->GetString("Player ") << "2 "; // ...here...
			m_pBitmapFont->Print(oss.str().c_str(), 49, 546, 0.33f, D3DCOLOR_XRGB(255, 255, 255));
			oss.str("");
			if (CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
			{
				oss << StringTable::GetInstance()->GetString("Movement"); // ...here...
			}
			else
				oss << StringTable::GetInstance()->GetString("Attack"); // ...and here. This will now retrieve Anglo-Saxon English for these lines.
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-004
			/////////////////////////////////////////////////////////////////
			m_pBitmapFont->Print(oss.str().c_str(), 160, 546, 0.33f, D3DCOLOR_XRGB(255, 255, 255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 600, 0, 255, 255, 255);
			//oss.str((""));
			//int nTurn = CGameManager::GetInstance()->GetCurrentTurn();
			//oss << "Current Turn: " << CGameManager::GetInstance()->GetCurrentTurn();
			//const char* tempchar = "CURRENT TURN:";
			//const char* tempchar = "";
			//m_pBitmapFont->Print(tempchar,0,40,0.4f,D3DXCOLOR(0,255,0,255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 600, 30, 255, 255, 255);

			//oss.str((""));
			//oss << "Selected Unit: ";
			//if (m_pSelectedUnit != nullptr)
			//{
			//	oss << m_pSelectedUnit->GetType() << ", X: " << m_pSelectedUnit->GetPos().nPosX << ", Y: " << 
			//		m_pSelectedUnit->GetPos().nPosY << ", HP: " << m_pSelectedUnit->GetHP() << ", facing: " << m_pSelectedUnit->GetFacing();
			//}
			//m_pBitmapFont->Print((const char*)oss.str().c_str(),0, 350, 1.0f,(DWORD)(255,255,255));
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 350, 255, 255, 255);
		}



		// AI debug render input queue
	/*	int nY = 40;
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
		}*/

		//std::wostringstream woss;
		//woss << "Active Player Mines Owned: " << CGameManager::GetInstance()->GetCurrentPlayer()->GetMinesOwned() <<
		//	", Mills Owned: " << CGameManager::GetInstance()->GetCurrentPlayer()->GetMillsOwned();
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 60, 150, 255, 0, 255);

		CFloatingText::GetInstance()->Render();
}
