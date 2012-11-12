#include "StdAfx.h"
#include "Unit.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "Archer.h"
#include "Tile.h"
#include "DeSpawnUnitMessage.h"
#include "SpawnUnitMessage.h"
#include "GameManager.h"
#include "AbilityManager.h"
#include "Player.h"
#include "MessageSystem.h"
#include "Hero.h"
#include "ParticleManager.h"
#include "SoundManager.h"
#include "AIManager.h"
#include "SGD Wrappers\CSGD_XAudio2.h"
#include "ObjectManager.h"
#include "FloatingText.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"


CUnit::CUnit(UNIT_TYPE type) : m_eType(type)
{
	m_bPlayAttackAnim = false;
	m_bCharging = false;
	m_nTilesMoved = 0;
	CAbilityManager * pAM = CAbilityManager::GetInstance();

	if( m_eType != UT_CASTLE )
		m_vAbilities.push_back(pAM->GetAbility(SP_MOVE));
	
	if (m_eType == UT_CASTLE)
	{
		m_vAbilities.push_back(pAM->GetAbility(SP_SPAWNARCHER));
		m_vAbilities.push_back(pAM->GetAbility(SP_SPAWNSWORD));
		m_vAbilities.push_back(pAM->GetAbility(SP_SPAWNCALV));
	}
	else if (m_eType != UT_ARCHER)
	{
		m_vAbilities.push_back(pAM->GetAbility(SP_MELEEATTACK));

		if( m_eType == UT_CAVALRY )
			m_vAbilities.push_back(pAM->GetAbility(SP_CHARGE));
		
		if( m_eType == UT_SWORDSMAN )
			m_vAbilities.push_back(pAM->GetAbility(SP_STAND));
	}
	else
	{
		m_vAbilities.push_back(pAM->GetAbility(SP_ARCHERRANGEDATTACK));
		m_vAbilities.push_back(pAM->GetAbility(SP_VOLLEY));
	}

	if (m_eType == UT_HERO)
	{
		m_vAbilities.push_back(pAM->GetAbility(SP_CHAMPSPELL));
	}


	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = m_eType;

	m_nUniqueID = CGameManager::GetInstance()->GenerateUniqueUnitID();

	m_fDodgeChance = 0.0f;
	m_bFreeMove = false;
	m_bIsFleeing = false;
	m_bHasDied = false;
}

bool CUnit::CheckDodged(void)
{
	int n = rand() % RAND_MAX;
	float atk = ((float)n / (float)RAND_MAX);
	if (atk > m_fDodgeChance)
		return false;
	else
		return true;
}

int CUnit::GetPortraitID(void)
{
	switch(m_eType)
	{
	case UT_ARCHER:
		return CGraphicsManager::GetInstance()->GetID(_T("archerportrait"));
		break;
	case UT_CASTLE:
		return CGraphicsManager::GetInstance()->GetID(_T("castleportrait"));
		break;
	case UT_CAVALRY:
		return CGraphicsManager::GetInstance()->GetID(_T("cavalryportrait"));
		break;
	case UT_HERO:
		return CGraphicsManager::GetInstance()->GetID(_T("heroportrait"));
		break;
	case UT_ICEBLOCK:
		return CGraphicsManager::GetInstance()->GetID(_T("iceblockportrait"));
		break;
	case UT_SKELETON:
		return CGraphicsManager::GetInstance()->GetID(_T("skeletonportrait"));
		break;
	case UT_SWORDSMAN:
		return CGraphicsManager::GetInstance()->GetID(_T("swordsmanportrait"));
		break;
	}
	return -1;
}

CUnit::~CUnit(void)
{
	delete m_sAnimStruct;
}

void CUnit::AddWaypoint(CTile* pTile)
{
	if (pTile != nullptr)
		m_vWaypoints.push_back(pTile);
}
CAbility* CUnit::GetAbility(int index)
{
	if ((decltype(m_vAbilities.size()))index < m_vAbilities.size())
		return m_vAbilities[index];
	else
		return nullptr;
}

bool CUnit::GetEffect(SPELL_TYPE p)
{
	for( unsigned int i = 0; i < m_vEffects.size(); i++ )
	{
		if( m_vEffects[i].second->GetType() == p )
			return true;
	}

	return false;
}

// Just used for checking if two numbers are close enough together for waypoint moving. Used to be
// 5 pixels, but left some weird off. Now it's just 0, so it's a relic function but it doesn't hurt leaving it
static bool CloseEnough(int n1, int n2)
{
	if (abs(n1 - n2) < 2)
		return true;
	else
		return false;
}
void CUnit::Update(float fElapsedTime)
{

	// reset basic stuff
	m_bFreeMove = false;
	m_bShielded = false;
	m_nSpeed = m_nSpeed;
	switch (m_eType)
	{
	case UT_ARCHER:
		m_nSpeed = 4;
		m_nAttack = 6;
		break;
	case UT_SWORDSMAN:
		m_nSpeed = 3;
		m_nAttack = 8;
		break;
	case UT_CAVALRY:
		m_nSpeed = 5;
		m_nAttack = 6;
		break;
	case UT_HERO:
		m_nSpeed = 4;
		m_nAttack = 10;
		break;
	case UT_CASTLE:
		m_nSpeed = 0;
		m_nAttack = 0;
		break;
	case UT_SKELETON:
		m_nSpeed = 2;
		m_nAttack = 4;
		break;
	case UT_ICEBLOCK:
		m_nSpeed = 0;
		m_nAttack = 0;
		break;
	}
	// do stuff to the unit based on their buffs/debuffs
	for (unsigned int i = 0; i < m_vEffects.size(); ++i)
	{
		switch (m_vEffects[i].second->GetType())
		{
		case SP_SHIELD:
			m_bShielded = true;
			break;
		case SP_CARTOGRAPHY:
		case SP_PATHFINDER:
			m_bFreeMove = true;
			break;
		case SP_SPEED:
			{
				switch (m_eType)
				{
				case UT_ICEBLOCK:
				case UT_CASTLE:
					break;
				default:
					m_nSpeed = m_nSpeed + 1;
				}
			}
			break;
		case SP_RALLY:
			{
				switch (m_eType)
				{
				case UT_ICEBLOCK:
				case UT_CASTLE:
					break;
				default:
					SetAttack(GetAttack() + 2);
				}
			}
			break;

		case SP_ICEBOLT:
			{
				switch (m_eType)
				{
					case UT_ICEBLOCK:
					case UT_CASTLE:
					break;

					default:
						m_nSpeed = m_nSpeed - 2;
				}
			}
			break;

			case SP_FIREWEP:
			{
				switch (m_eType)
				{
					case UT_ICEBLOCK:
					case UT_CASTLE:
					break;

					default:
						m_nAttack = m_nAttack + 2;
				}
			}
			break;

			case SP_LIGHTSTRIKE:
			{
				switch (m_eType)
				{
					case UT_ICEBLOCK:
					case UT_CASTLE:
					break;

					default:
						m_bHasAttacked = true;
				}
			}
			break;
		}
	}
	if ((float)((float)GetHP() / (float)GetMaxHP() <= 0.35f))
	{
		m_bIsFleeing = true;
	}
	else
		m_bIsFleeing = false;

	if( m_eType == UT_SWORDSMAN )
	{
		int i = 0;
		m_bShielded;
	}

	CTile* pMyTile = CTileManager::GetInstance()->GetTile(GetPos().nPosX, GetPos().nPosY);
	if (pMyTile != nullptr)
	{
		if (pMyTile->GetTileType() == TT_FOREST)
			m_fDodgeChance = 0.25f;
		else
			m_fDodgeChance = 0.0f;
		if (m_eType == UT_ARCHER)
			if (pMyTile->GetTileType() == TT_MOUNTAINS || pMyTile->GetTileType() == TT_MINE)
			{
				SetRange(4);
			}
			else
				SetRange(3);
	}
	// move me along the route!
	// If we have any waypoints in our list of waypoints added in from GameplayState::MoveToTile, then we need to move across them
	if(m_nHP > 0 && this->m_bPlayAttackAnim == false)
	{
		if (m_nFacing == 0)
		{
			m_sAnimStruct->animationType = AT_WALK_N; // S
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH+1; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 1)
		{
			m_sAnimStruct->animationType = AT_WALK_E; // N
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH+1; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 2)
		{
			m_sAnimStruct->animationType = AT_WALK_S; // E
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH+1; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 3)
		{
			m_sAnimStruct->animationType = AT_WALK_W; // W
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH+1; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
	}
	if(m_nHP > 0 && this->m_bPlayAttackAnim == true)
	{
		CAnimation* currAnim = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType);
		if(m_sAnimStruct->animationType == AT_WALK_N || m_sAnimStruct->animationType == AT_WALK_E
			|| m_sAnimStruct->animationType == AT_WALK_W || m_sAnimStruct->animationType == AT_WALK_S)
		{
			currAnim->SetCurrFrame(0);
		}
		if (m_nFacing == 0)
		{
			//CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType, m_sAnimStruct->animationType).SetCurrFrame(0);
			m_sAnimStruct->animationType = AT_ATTACK_N; // S
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 1)
		{
			//CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType, m_sAnimStruct->animationType).SetCurrFrame(0);
			m_sAnimStruct->animationType = AT_ATTACK_E; // N
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 2)
		{
			//CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType, m_sAnimStruct->animationType).SetCurrFrame(0);
			m_sAnimStruct->animationType = AT_ATTACK_S; // E
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		else if (m_nFacing == 3)
		{
			//CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType, m_sAnimStruct->animationType).SetCurrFrame(0);
			m_sAnimStruct->animationType = AT_ATTACK_W; // W
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		int currFrame = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame();
		int numFrames = currAnim->GetFrameVec().size();
		int lastFrame = numFrames-1;
		if(currFrame == lastFrame)
		{
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,(int)AT_ATTACK_N,false);
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,(int)AT_ATTACK_E,false);
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,(int)AT_ATTACK_W,false);
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,(int)AT_ATTACK_S,false);
			m_bPlayAttackAnim = false;
		}
	}
	if (m_nHP <= 0)
	{
		if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("ITSDEAD"))) && !m_bHasDied)
		{
			CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("ITSDEAD")),false);
			m_bHasDied = true;
		}
		{
			m_sAnimStruct->animationType = AT_DEATH;
			CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,m_sAnimStruct->animationType,true);
			/*for(int i = 0; i < (int)AT_DEATH; i++)
			{
				if(i != m_sAnimStruct->animationType)
					CAnimationManager::GetInstance()->SetAnimBool(m_sAnimStruct->unitType,i,false);
			}*/
		}
		int currFrame = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame();
		int numFrames = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec().size();
		int lastFrame = numFrames-1;
		if(currFrame == lastFrame && m_sAnimStruct->unitType == UT_ARCHER)
		{
			CAnimation tempanim = *CAnimationManager::GetInstance()->GetAnimation(UT_ARCHER,AT_DEATH);
			int tempframe = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct)->GetFrame();
			float temptime = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct)->GetTimePlayed();
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(currFrame == lastFrame)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(currFrame == lastFrame
			&& m_sAnimStruct->unitType == UT_SKELETON)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(currFrame == lastFrame
			&& m_sAnimStruct->unitType == UT_HERO)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(currFrame == lastFrame
			&& m_sAnimStruct->unitType == UT_SWORDSMAN)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(currFrame == lastFrame && m_sAnimStruct->unitType == UT_CASTLE)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
		else if(m_sAnimStruct->unitType == UT_ICEBLOCK)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);
		}
	}

	if (m_vWaypoints.size() != 0)
	{
		// Set the tile we are moving off of's occupied to false.
		CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY)->SetIfOccupied(false);

		int xDistance = m_sGamePos.nPosX - m_vWaypoints.back()->GetPosition().nPosX;
		int yDistance = m_sGamePos.nPosY - m_vWaypoints.back()->GetPosition().nPosY;
		if (yDistance == 1)
			m_nFacing = 0;
		else if (yDistance == -1)
			m_nFacing = 2;
		else if (xDistance == -1)
			m_nFacing = 1;
		else if (xDistance == 1)
			m_nFacing =3;



		// Find out how we need to move, pixel wise, to our intended target.
		float x = float((nFakeTileWidth / 2 * m_vWaypoints.back()->GetPosition().nPosX ) - (nFakeTileHeight / 2 * m_vWaypoints.back()->GetPosition().nPosY));
		float y = float((nFakeTileWidth / 2 * m_vWaypoints.back()->GetPosition().nPosX ) + (nFakeTileHeight  / 2 * m_vWaypoints.back()->GetPosition().nPosY));
		float nNewPixelPosX = x;//m_vWaypoints.back()->GetPosition().nPosX * nFakeTileWidth;
		float nNewPixelPosY = y;//m_vWaypoints.back()->GetPosition().nPosY * nFakeTileHeight;

		// Moves our posX or posY over time so that our pixel position matches up with the pixel position
		// of the first waypoint
		if (m_sWorldPos.nPosX < nNewPixelPosX)
		{
			m_sWorldPos.nPosX += 2;
		}
		else if (m_sWorldPos.nPosX > nNewPixelPosX)
		{
			m_sWorldPos.nPosX -= 2;
		}
		if (m_sWorldPos.nPosY < nNewPixelPosY)
		{
			m_sWorldPos.nPosY += 2;
		}
		else if (m_sWorldPos.nPosY > nNewPixelPosY)
		{
			m_sWorldPos.nPosY -= 2;
		}

		// If we're "close enough" to the pixel position (i.e. our unit's pixel position and the tile's pixel position match)
		// then we are considered "on" that tile. We've made it!
		// Set our logical position to that tile's position, cause we're on it, and then set that tile to occupied.
		// Progress the number of tiles we have moved by 1
		// Remove that tile from our waypoint, and then if we've moved our speed, clear the rest of the waypoints 
		// because we can't move any further.
		if (CloseEnough((m_sWorldPos.nPosX ) ,((int)x))&&
			CloseEnough((m_sWorldPos.nPosY ),((int)y)))
		{
			m_sGamePos = m_vWaypoints.back()->GetPosition();

			CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY)->SetIfOccupied(true);
			m_nTilesMoved++;


			m_vWaypoints.pop_back();
			if (m_nTilesMoved == m_nSpeed)
			{
				m_vWaypoints.clear();
			}	
			if(m_vWaypoints.size()==0)
			{
				if (CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetIfResourceTile())
				{
					if (!CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetIfCapturing())
					{
						if( CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() )
						{
							if (CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetPlayerID() != -1 )
							{
								CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer(CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetPlayerID());
								if (CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetTileType() == TT_MILL)
									pPlayer->SetMillsOwned(pPlayer->GetMillsOwned() - 1);
								else if (CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetTileType() == TT_MINE)
									pPlayer->SetMinesOwned(pPlayer->GetMinesOwned() - 1);
								else if (CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->GetTileType() == TT_FARM)
									pPlayer->SetFarmsOwned(pPlayer->GetFarmsOwned() - 1);
							}

							CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->SetIfCapturing(true);
							CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX,m_sGamePos.nPosY)->SetPlayerID( GetPlayerID());
						}
					}
				}

				if( m_eType == UT_CAVALRY )
				{
					if( CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying( CSoundManager::GetInstance()->GetID(_T("Gallop")) ) )
						CSGD_XAudio2::GetInstance()->SFXStopSound( CSoundManager::GetInstance()->GetID(_T("Gallop")) );
				}
				else
				{
					if( CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying( CSoundManager::GetInstance()->GetID(_T("Footstep")) ) )
						CSGD_XAudio2::GetInstance()->SFXStopSound( CSoundManager::GetInstance()->GetID(_T("Footstep")) );
				}

				CParticleManager::GetInstance()->StopLoop(PT_MOVE);
				if( m_bCharging == true )
				{
					m_bHasAttacked = true;
					m_bCharging = false;
				}

				if( GetEffect(SP_DEATH) == true )
				{
					if( m_eType != UT_HERO )
						m_nHP = 0;
					else
					{
						Vec2Df tmp;
						tmp.fVecX = (float)m_sWorldPos.nPosX;
						tmp.fVecY = (float)m_sWorldPos.nPosY;
						CFloatingText::GetInstance()->AddText("-10", tmp, Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_ARGB(255, 255, 20, 20));
						m_nHP -= 10;
					}
				}
			}
		}
	}

}

void CUnit::Render(void)
{


}

// Sets our logical position to the passed in X/Y and sets that tile to occupied. Sets our previous
// tile to no longer occupied, and sets our pixel position to equal that new tile
void CUnit::SetPos(int posX, int posY)
{
	int x = (nFakeTileWidth / 2 * posX ) - (nFakeTileHeight / 2 * posY);
	int y = (nFakeTileWidth / 2 *posX ) + (nFakeTileHeight  / 2 * posY);
	m_sWorldPos.nPosX = x;//posX * nFakeTileWidth;
	m_sWorldPos.nPosY = y;//posY * nFakeTileHeight;
	CTile* pTile = CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY);
	if (pTile != nullptr)
		pTile->SetIfOccupied(false);
	m_sGamePos.nPosX = posX;
	m_sGamePos.nPosY = posY;
	pTile = CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY);
	if (pTile != nullptr)
		pTile->SetIfOccupied(true);
}

void CUnit::SetPos(Vec2D pos)
{
	SetPos(pos.nPosX, pos.nPosY);
}

void CUnit::RemoveEffect(SPELL_TYPE spType)
{
	for (unsigned int i = 0; i < m_vEffects.size(); ++i)
	{
		if (m_vEffects[i].second->GetType() == spType)
		{
			m_vEffects.erase(m_vEffects.begin() + i--);
			return;
		}
	}
}
void CUnit::UpdateEffects(void)
{
	for (unsigned int i = 0; i < m_vEffects.size(); ++i)
	{
		m_vEffects[i].first -= 1;
		if (m_vEffects[i].first <= 0)
		{
			if( m_vEffects[i].second->GetType() == SP_STAND )
				CParticleManager::GetInstance()->StopLoop(PT_STAND);

			if( m_vEffects[i].second->GetType() == SP_ICEBOLT )
				CParticleManager::GetInstance()->StopLoop(PT_ICEBOLT);

			if( m_vEffects[i].second->GetType() == SP_FIREWEP )
				CParticleManager::GetInstance()->StopLoop(PT_FIREWEP);

			if( m_vEffects[i].second->GetType() == SP_FORT )
				CParticleManager::GetInstance()->StopLoop(PT_FORT);
			
			if( m_vEffects[i].second->GetType() == SP_SPEED )
				CParticleManager::GetInstance()->StopLoop(PT_SPEED);

			m_vEffects.erase(m_vEffects.begin() + i--);
		}
	}
}

void CUnit::PushEffect(CAbility* effect, int nDuration)
{
	Effect eff;
	eff.first = nDuration;
	eff.second = effect;
	for (unsigned int i = 0; i < m_vEffects.size(); ++i)
	{
		if (m_vEffects[i].second->GetType() == effect->GetType())
		{
			m_vEffects[i].first = nDuration;
			return; // it's already on, so just overwrite it. Update duration here? - DONE
		}
	}
	m_vEffects.push_back(eff);
}

int CUnit::SetFreeMove(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_CARTOGRAPHY), 1);
	}
	return 0;
}

int CUnit::Shield(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_SHIELD), INT_MAX);
	}
	return 0;
}

int CUnit::Volley( lua_State* L )
{
	CUnit* arch = CGameplayState::GetInstance()->GetSelectedUnit();
	lua_pushnumber(L, arch->GetAttack() * 2);
	return 1;
}

int CUnit::FindTeam( lua_State* L )
{
	int ID = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
	vector< CGameObject* > objects = CObjectManager::GetInstance()->GetList();
	lua_newtable(L);
	int nCount = 0;
	for( unsigned int i = 0; i < objects.size(); i++ )
	{
		CUnit* tmp = dynamic_cast< CUnit* >(objects[i]);

		if( tmp->GetPlayerID() != ID )
			continue;

		lua_newtable(L);
		lua_pushstring(L, "posX");
		lua_pushnumber(L, tmp->GetPos().nPosX);
		lua_settable(L, -3);
		lua_pushstring(L, "posY");
		lua_pushnumber(L, tmp->GetPos().nPosY);
		lua_settable(L, -3);
		lua_pushstring(L, "uniqueID");
		lua_pushnumber(L, tmp->GetUniqueID());
		lua_settable(L, -3);
		lua_pushnumber(L, nCount+1);
		nCount++;
		lua_insert(L, -2);
		lua_settable(L, -3);
	}

	lua_setglobal(L, "tAffected");

	return nCount+1;
}

int CUnit::Death( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_DEATH), 4);
	}
	return 0;
}

int CUnit::Fortify( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_FORT), 2);
	}

	CParticleManager::GetInstance()->LoadParticles(PT_FORT, TranslateToPixel(pUnit->GetPos()), pUnit);
	return 0;
}

int CUnit::Chain(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	CAbility* pAbility = CAbilityManager::GetInstance()->GetAbility(SP_LIGHTCHAIN);
	std::vector< CUnit* > affected;
	std::vector< CUnit* > found;
	if( pUnit != nullptr )
	{
		CUnit* target = pUnit;
		CUnit* org;
		int count = 0;
		std::vector< Vec2D > tilepos = CAbilityManager::GetInstance()->GetRange(1);
		affected.push_back(pUnit);
		org = pUnit;

		while( true )
		{
			Vec2D tmp = tilepos[count];
			tmp.nPosX += target->GetPos().nPosX;
			tmp.nPosY += target->GetPos().nPosY;
			target = CGameManager::GetInstance()->FindUnit(tmp);

			if( target != nullptr )
			{
				bool already = false;
				for( unsigned int i = 0; i < affected.size(); i++ )
				{
					if( affected[i] == target )
						already = true;
				}
				
				for( unsigned int i = 0; i < found.size(); i++ )
				{
					if( found[i] == target )
						already = true;
				}

				if( already == false )
				{
					found.push_back(target);
				}
				target = org;
			}
			else
				target = org;

			count++;

			if( count == 4 )
			{
				if( found.size() == 0 )
					break;
				affected.push_back(found[0]);
				org = found[0];
				target = org;
				found.erase(found.begin());
				count = 0;
			}
		}

		lua_newtable(L);
		int nCount = 0;
		for( unsigned int i = 0; i < affected.size(); i++ )
		{
			lua_newtable(L);
			lua_pushstring(L, "posX");
			lua_pushnumber(L, affected[i]->GetPos().nPosX);
			lua_settable(L, -3);
			lua_pushstring(L, "posY");
			lua_pushnumber(L, affected[i]->GetPos().nPosY);
			lua_settable(L, -3);
			lua_pushstring(L, "uniqueID");
			lua_pushnumber(L, affected[i]->GetUniqueID());
			lua_settable(L, -3);
			lua_pushnumber(L, nCount+1);
			nCount++;
			lua_insert(L, -2);
			lua_settable(L, -3);
		}

		lua_setglobal(L, "tAffected");

	}
	
	for( unsigned int i = 1; i < affected.size(); i++ )
	{
		CParticleManager::GetInstance()->LoadParticles(PT_LIGHTBOLT, TranslateToPixel(affected[i]->GetPos()));
	}

	return affected.size();
}


int CUnit::IceAge( lua_State* L )
{
	int l = (int)lua_tonumber(L, 1);
	CAbility* iceage = CAbilityManager::GetInstance()->GetAbility(SP_ICEAGE);
	CUnit* pHero = CGameplayState::GetInstance()->GetSelectedUnit();

	CTileManager* pTM = CTileManager::GetInstance();
	std::vector< Vec2D > pat = CAbilityManager::GetInstance()->GetProperFacing(pHero->GetFacing(), iceage, pTM->GetTile(pHero->GetPos().nPosX, pHero->GetPos().nPosY));
	for( unsigned int i = 0; i < pat.size(); i++ )
	{
		CTile* j = pTM->GetTile(pat[i].nPosX + pHero->GetPos().nPosX, pat[i].nPosY + pHero->GetPos().nPosY);
		if( j == nullptr )
			continue;

		j->SetIfFrozen(true);

		MapModification mod;
		mod.modType = SP_ICEAGE;
		mod.posX = pat[i].nPosX + pHero->GetPos().nPosX;
		mod.posY = pat[i].nPosY + pHero->GetPos().nPosY;

		CGameManager::GetInstance()->AddModification(mod);
	}

	return 0;
}

int CUnit::FireWep( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if( pUnit != nullptr )
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_FIREWEP), 1);
	}
	return 0;
}

int CUnit::Slow( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if( pUnit != nullptr )
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_ICEBOLT), 2);
	}
	return 0;
}

int CUnit::Speed(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_SPEED), 1);
	}
	return 0;
}

int CUnit::DoDamage(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		int damage = (int)lua_tonumber(L, 2);
		
		if( pUnit->GetEffect(SP_STAND) == true )
		{
			damage = damage / 2;
			pUnit->RemoveEffect(SP_STAND);
		}

		if( pUnit->GetEffect(SP_FORT) == true )
		{
			damage = damage - (int)(damage * .75f);
			pUnit->RemoveEffect(SP_FORT);
		}

		pUnit->SetHP(pUnit->GetHP() - damage);
		// STATS RECORDING
		CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer(CGameplayState::GetInstance()->GetSelectedUnit()->GetPlayerID());
		switch (CGameplayState::GetInstance()->GetSelectedUnit()->GetType())
		{
		case UT_SWORDSMAN:
			pPlayer->GetStats()->nSwordsmanDamageDone+=damage;
			break;
		case UT_ARCHER:
			pPlayer->GetStats()->nArcherDamageDone+=damage;
			break;
		case UT_CAVALRY:
			pPlayer->GetStats()->nCalvaryDamageDone+=damage;
			break;
		case UT_HERO:
			{
				if (damage > 0)
					pPlayer->GetStats()->nChampionDamageDone+=damage;
				else if (damage < 0)
					pPlayer->GetStats()->nChampionHealingDone+=damage;
			}
			break;

		}
		
		if (pUnit->GetHP() > pUnit->GetMaxHP())
		{
			pUnit->SetHP(pUnit->GetMaxHP());
		}
		lua_pushnumber(L, damage);
	}
	return 1;
}

int CUnit::Encase( lua_State* L )
{
	int ID = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
	int posX = (int)lua_tonumber(L, 1);
	int posY = (int)lua_tonumber(L, 2);
	
	IMessage* msg;
	CUnit* target;
	target = CGameManager::GetInstance()->FindUnit(Vec2D(posX, posY));

	if( CTileManager::GetInstance()->GetTile(posX, posY) == nullptr )
		return 0;

	if( target == nullptr )
	{
		if( ID == 0 )
			msg = new CSpawnUnitMessage(Vec2D(posX, posY), ID, UT_ICEBLOCK, 2, false, 22);
		else
			msg = new CSpawnUnitMessage(Vec2D(posX, posY), ID, UT_ICEBLOCK, 0, false, 22);

		CMessageSystem::GetInstance()->SendMessageW(msg);
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("ice")), false, false);
		CParticleManager::GetInstance()->LoadParticles(PT_ICEBOLT, Vec2D(posX, posY));
	}
	else
	{
		Vec2Df tmp;
		tmp.fVecX = (float)TranslateToPixel(target->GetPos()).nPosX;
		tmp.fVecY = (float)TranslateToPixel(target->GetPos()).nPosY;
		target->SetHP(target->GetHP() - 10);
		CFloatingText::GetInstance()->AddText("-10", tmp, Vec2Df(0, -40), 2.0f, 0.4f, D3DCOLOR_XRGB(255, 20, 20));	
	}
	return 0;
}

int CUnit::Rally(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		if (pUnit->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_RALLY), 1);
	}
	return 0;
}

int CUnit::Teleport( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	Vec2D tele = CGameplayState::GetInstance()->GetSelectionPos();
	CTileManager::GetInstance()->GetTile(pUnit->GetPos().nPosX, pUnit->GetPos().nPosY)->SetIfOccupied(false);
	pUnit->SetPos(tele);
	CTileManager::GetInstance()->GetTile(pUnit->GetPos().nPosX, pUnit->GetPos().nPosY)->SetIfOccupied(true);
	CParticleManager::GetInstance()->LoadParticles(PT_RAISEDEAD, TranslateToPixel(pUnit->GetPos()));
	return 0;
}

int CUnit::Sacrifice( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	pUnit->SetHP(0);
	CGameManager::GetInstance()->SetExtraTurn(true);
	return 0;
}

int CUnit::MindControl( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr && pUnit->GetType() != UT_HERO)
	{
		if( pUnit->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() )
		{
			if( pUnit->GetPlayerID() == 0 )
				pUnit->SetPlayerID(1);
			else
				pUnit->SetPlayerID(0);
		}

		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_MIND), INT_MAX);
	}

	return 0;
}

int CUnit::Pathfind(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		if (pUnit->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_PATHFINDER),1);
	}
	return 0;
}

int CUnit::LightStrike(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
			pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_LIGHTSTRIKE),2);
	}
	return 0;
}

int CUnit::StandGround(lua_State* L)
{
	int nUniqueID = (int)lua_tonumber(L,1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if( pUnit != nullptr )
	{
		if( pUnit->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_STAND), 2);
	}
	return 0;
}

int CUnit::Vamp( lua_State* L )
{
	int nUniqueID = (int)lua_tonumber(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUniqueID);
	if (pUnit != nullptr)
	{
		pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(SP_VAMP), 1);
	}

	CParticleManager::GetInstance()->LoadParticles(PT_MIND, TranslateToPixel(pUnit->GetPos()), pUnit);
	return 0;
}

int CUnit::RaiseDead(lua_State* L)
{
	int posX = (int)lua_tonumber(L, 1);
	int posY = (int)lua_tonumber(L, 2);

	CTile* pTile = CTileManager::GetInstance()->GetTile(posX, posY);
	CPlayer* pPlayer = CGameManager::GetInstance()->GetCurrentPlayer();
	if( pTile == nullptr )
		return 0;

	if (pTile->GetIfOccupied() != true)
	{
		if (pTile->GetIfDeadTile() == true)
		{
			CSpawnUnitMessage* pmsg = new CSpawnUnitMessage(Vec2D(posX, posY), CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID(),
				UT_SKELETON, 0, false);
			CMessageSystem::GetInstance()->SendMessageW(pmsg);
			pTile->SetIfOccupied(true);
			pTile->SetIfDeadTile(false);
		}
	}
	return 0;
}
int CUnit::Whirlwind(lua_State* L)
{	
	//LUA Lovin' : get the guy effect
	int ntheguy = lua_tointeger(L, 1);
	CUnit* guyontile = CGameManager::GetInstance()->GetUnitByID(ntheguy);

	Vec2D nextopen = CAIManager::GetInstance()->NearestOpen(CGameplayState::GetInstance()->GetSelectedUnit()->GetPos(),guyontile->GetPos());
	guyontile->AddWaypoint(CTileManager::GetInstance()->GetTile(nextopen.nPosX,nextopen.nPosY));

	return 0;
}

int CUnit::GetUnitPosition(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);

	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		lua_pushinteger(L, -1);
		return 1;
	}
	lua_pushinteger(L, pUnit->GetPos().nPosX);
	lua_pushinteger(L, pUnit->GetPos().nPosY);

	return 2;
}

int CUnit::GetFleeing(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		return 1;
	}

	if (pUnit->GetFleeing())
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

int CUnit::GetTilesMoved(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);

	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		return 1;
	}
	int nTilesMoved = pUnit->GetTilesMoved();
	
	lua_pushinteger(L, nTilesMoved);

	return 1;
}

int CUnit::GetHealth(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);

	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		return 1;
	}
	int nHealth = pUnit->GetHP();
	
	lua_pushinteger(L, nHealth);

	return 1;
}
int CUnit::GetMaxHealth(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);

	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		return 1;
	}
	int nMaxHP = pUnit->GetMaxHP();
	
	lua_pushinteger(L, nMaxHP);

	return 1;
}

int CUnit::GetPlayerID(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	if (pUnit == nullptr)
	{
		lua_pushinteger(L, -1);
		return 1;
	}

	int nPlayerID = pUnit->GetPlayerID();

	lua_pushinteger(L, nPlayerID);

	return 1;
}