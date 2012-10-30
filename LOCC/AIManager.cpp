#include "StdAfx.h"
#include "AIManager.h"
#include "AbilityManager.h"
#include "StateStack.h"
#include "Player.h"
#include "GameManager.h"
#include "GameplayState.h"
#include "FloatingText.h"
#include "TileManager.h"
#include "Unit.h"
#include "Hero.h"

CAIManager* CAIManager::s_Instance = nullptr;

CAIManager* CAIManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CAIManager();
	return s_Instance;
}
void CAIManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CAIManager::Initialize(void)
{
	m_bHandlingUnits = false;
	m_bHandled = false;
	m_pFocusUnit = nullptr;
	m_bDone = true;
	m_bSelected = false;
	m_bMoved = true;

	m_bOrderFinished = false;

	AIL = lua_open();
	luaL_openlibs(AIL);
	lua_register(AIL, "AddText", CFloatingText::AddText);
	lua_register(AIL, "TranslateToPixel", TranslateToPixel);
	lua_register(AIL, "SetFreeMove", CUnit::SetFreeMove);
	lua_register(AIL, "Shield", CUnit::Shield);
	lua_register(AIL, "Speed", CUnit::Speed);
	lua_register(AIL, "DoDamage", CUnit::DoDamage);
	lua_register(AIL, "GetSelectedTile", CTileManager::GetSelectedTile);
	lua_register(AIL, "DestroyForest", CTileManager::DestroyForest);
	lua_register(AIL, "Rally", CUnit::Rally);
	lua_register(AIL, "Pathfind", CUnit::Pathfind);
	lua_register(AIL, "RaiseMountain", CTileManager::RaiseMountain);
	lua_register(AIL, "StandGround", CUnit::StandGround);
	lua_register(AIL, "RaiseDead", CUnit::RaiseDead);
	lua_register(AIL, "Slow", CUnit::Slow);
	lua_register(AIL, "FireWep", CUnit::FireWep);
	lua_register(AIL, "LightStrike", CUnit::LightStrike);
	lua_register(AIL, "IceAge", CUnit::IceAge);
	lua_register(AIL, "Chain", CUnit::Chain);
	lua_register(AIL, "Whirlwind", CUnit::Whirlwind);
	// new AI functions
	lua_register(AIL, "IssueOrder", CAIManager::IssueOrder);
	lua_register(AIL, "FindNearest", CAIManager::FindNearest);
	lua_register(AIL, "GetUnitPosition", CUnit::GetUnitPosition);
	lua_register(AIL, "GetFleeing", CUnit::GetFleeing);
	lua_register(AIL, "FindChampion", CAIManager::FindChampion);
	lua_register(AIL, "GetHealth", CUnit::GetHealth);
	lua_register(AIL, "GetMaxHealth", CUnit::GetMaxHealth);
	lua_register(AIL, "GetTilesMoved", CUnit::GetTilesMoved);
	lua_register(AIL, "FindUnitByTile", CAIManager::FindUnitByTile);
	lua_register(AIL, "GetPlayerID", CUnit::GetPlayerID);
	lua_register(AIL, "HasSpell", CHero::HasSpell);
	lua_register(AIL, "GetSpellCooldown", CHero::GetSpellCooldown);
	lua_register(AIL, "GetFriendlyUnitsInRange", CAIManager::GetFriendlyUnitsInRange);
	lua_register(AIL, "GetEnemyUnitsInRange", CAIManager::GetEnemyUnitsInRange);
	lua_register(AIL, "GetMillsOwned", CPlayer::GetMillsOwned);
	lua_register(AIL, "GetMinesOwned", CPlayer::GetMinesOwned);
	lua_register(AIL, "FindNearestResource", CAIManager::FindNearestResource);
}
void CAIManager::Shutdown(void)
{
	lua_close(AIL);
}


bool CAIManager::CheckInputQueue(float fElapsedTime)
{
	static float fTimeToPop = 0.0f;
	if (m_vInputQueue.size() != 0)
	{
		fTimeToPop += fElapsedTime;
		if (fTimeToPop > 0.2f)
		{
			if (m_vInputQueue.front() == INPUT_AI_ORDERFINISHED)
			{
				m_vInputQueue.erase(m_vInputQueue.begin());
				fTimeToPop = 0.0f;
				return false;
			}

			CStateStack::GetInstance()->GetTop()->Input(m_vInputQueue.front());
			if (m_vInputQueue.size() != 0)
			{
				m_vInputQueue.erase(m_vInputQueue.begin());
			}

			fTimeToPop = 0.0f;
		}
	}
	else
	{
		return false;
	}

	//static float fTimeToPop = 0.0f;
	//if (m_vInputQueue.size() != 0)
	//{
	//	fTimeToPop += fElapsedTime;
	//	if (fTimeToPop > 0.4f)
	//	{
	//		if (m_vInputQueue.back() == INPUT_AI_ORDERFINISHED)
	//		{
	//			m_bOrderFinished = true;
	//		}
	//		if (m_vInputQueue.back() == INPUT_AI_ATTACKED)
	//		{
	//			m_bAttacked = true;
	//		}
	//		if (m_vInputQueue.back() == INPUT_AI_SELECTED)
	//		{
	//			m_bSelected = true;
	//		}
	//		if (m_vInputQueue.back() == INPUT_AI_MOVED)
	//		{
	//			m_bMoved = true;
	//			m_bSelected = false;
	//		}
	//		CStateStack::GetInstance()->GetTop()->Input(m_vInputQueue.back());
	//		if (m_vInputQueue.size() != 0)
	//			m_vInputQueue.pop_back();
	//		fTimeToPop = 0.0f;
	//		if (m_vInputQueue.size() == 0)
	//			m_bDone = true;
	//	}
	//}

	return (m_vInputQueue.size() != 0);
}
void CAIManager::SelectUnit(CUnit* pToSelect)
{
	int xDistance = pToSelect->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
	int yDistance = pToSelect->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;

	m_vInputQueue.push_back(INPUT_AI_SELECTED);
	m_vInputQueue.push_back(INPUT_ACCEPT);

	for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
	{
		if (xDistance < 0)
			m_vInputQueue.push_back(INPUT_LEFT);
		if (xDistance > 0)
			m_vInputQueue.push_back(INPUT_RIGHT);
		else
			continue;
	}
	for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
	{
		if (yDistance < 0)
			m_vInputQueue.push_back(INPUT_UP);
		if (yDistance > 0)
			m_vInputQueue.push_back(INPUT_DOWN);
		else
			continue;
	}
	m_vInputQueue.push_back(INPUT_AI_CLEAR);
}

void CAIManager::BeginMovement(void)
{
	bool bAITurn = false;
	for (unsigned int i = 0; i < m_vPlayerIDs.size(); ++i)
	{
		if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() == m_vPlayerIDs[i])
			bAITurn = true;
	}
	if (!bAITurn)
		return;
	//if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
	//	return;
	m_vUnitsToHandle.clear();
	m_vInputQueue.clear();
	m_vOrderQueue.clear();
	m_bMoved = true;
	m_bDone = true;
	m_bSelected = false;
	std::vector<CUnit*> m_vGuysToHandle;
	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			if (CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_CASTLE || CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_ICEBLOCK)
				continue;
			m_vGuysToHandle.push_back(CGameManager::GetInstance()->GetUnits()[i]);
			//if (CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_CASTLE)
			//	continue;
			//m_vUnitsToHandle.push_back(CGameManager::GetInstance()->GetUnits()[i]);
		}
	}

	//for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
	//{
	//	if (m_vGuysToHandle[i]->GetType() == UT_ARCHER)
	//	{
	//		m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
	//		return;
	//	}
	//}

	while (m_vGuysToHandle.size() != 0)
	{
		// Fleeing guys have first movement priority to get them in range of the hero
		for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
		{
			if (m_vGuysToHandle[i]->GetFleeing() == true)
			{
				m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
				m_vGuysToHandle.erase(m_vGuysToHandle.begin() + i++);
			}
		}

		// Hero has next priority to heal those people
		for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
		{
			if (m_vGuysToHandle[i]->GetType() == UT_HERO)
			{
				m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
				m_vGuysToHandle.erase(m_vGuysToHandle.begin() + i++);
				break;
			}
		}

		// Lump everyone else in there
		for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
		{
			m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
			m_vGuysToHandle.erase(m_vGuysToHandle.begin() + i++);
		}
	}
}
void CAIManager::BeginAttack(void)
{
	bool bAITurn = false;
	for (unsigned int i = 0; i < m_vPlayerIDs.size(); ++i)
	{
		if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() == m_vPlayerIDs[i])
			bAITurn = true;
	}
	if (!bAITurn)
		return;
	//if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
	//	return;
	m_vUnitsToHandle.clear();
	m_vInputQueue.clear();
	m_vOrderQueue.clear();
	m_bMoved = true;
	m_bDone = true;
	m_bSelected = false;
	std::vector<CUnit*> m_vGuysToHandle;
	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() ==CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			if (CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_CASTLE || CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_ICEBLOCK)
				continue;
			m_vGuysToHandle.push_back(CGameManager::GetInstance()->GetUnits()[i]);
		}
	}

	while (m_vGuysToHandle.size() != 0)
	{
		// Hero has first attack priority due to AP considerations. His attacks are more important
		for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
		{
			if (m_vGuysToHandle[i]->GetType() == UT_HERO)
			{
				m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
				m_vGuysToHandle.erase(m_vGuysToHandle.begin() + i++);
				break;
			}
		}

		// Then everyone else
		for (unsigned int i = 0; i < m_vGuysToHandle.size(); ++i)
		{
			m_vUnitsToHandle.push_back(m_vGuysToHandle[i]);
			m_vGuysToHandle.erase(m_vGuysToHandle.begin() + i++);
		}
	}

}

Vec2D CAIManager::NearestOpen(Vec2D pTargetUnit, Vec2D pSelectedUnit)
{
	int xDistance = pTargetUnit.nPosX - pSelectedUnit.nPosX;
	int yDistance = pTargetUnit.nPosY - pSelectedUnit.nPosY;
	Vec2D vTarget = pTargetUnit;
	std::list<std::pair<int, Vec2D>> vTargets;
	int nPreference = 1;
	bool bDoWork = true;


	// test using A*
	//std::vector<CTile*> m_vWayps;
	//CGameplayState::GetInstance()->CalculateMove(
	//	CTileManager::GetInstance()->GetTile(pSelectedUnit.nPosX, pSelectedUnit.nPosY),
	//	CTileManager::GetInstance()->GetTile(pTargetUnit.nPosX, pTargetUnit.nPosY),
	//	m_vWayps);
	//if (m_vWayps.size() == 0)
	//{
	//	return pSelectedUnit;
	//}
	//return m_vWayps.front()->GetPosition();

	while (bDoWork)
	{
		CTile* pTile = CTileManager::GetInstance()->GetTile(vTarget.nPosX, vTarget.nPosY);
		if (pTile == nullptr)
		{
			
		}
		else 
		{
			if (!pTile->GetIfOccupied() && !pTile->GetIfPassable())
			{
				break;
			}
			Vec2D AdjacentWest = Vec2D(vTarget.nPosX - 1, vTarget.nPosY);
			if (AdjacentWest == Vec2D(9, 2))
				int x = 9;
			Vec2D AdjacentEast = Vec2D(vTarget.nPosX + 1, vTarget.nPosY);
						if (AdjacentWest == Vec2D(9, 2))
				int x = 9;
			Vec2D AdjacentNorth = Vec2D(vTarget.nPosX, vTarget.nPosY - 1);
						if (AdjacentWest == Vec2D(9, 2))
				int x = 9;
			Vec2D AdjacentSouth = Vec2D(vTarget.nPosX, vTarget.nPosY + 1);
						if (AdjacentWest == Vec2D(9, 2))
				int x = 9;
			int Direction = -1;
			if (pTargetUnit.nPosX < pSelectedUnit.nPosX) // west
			{
				if (pTargetUnit.nPosY < pSelectedUnit.nPosY)
					Direction = 0; // Northwest
				else if (pTargetUnit.nPosY > pSelectedUnit.nPosY)
					Direction = 1; // Southwest;
				else
					Direction = 2; // West
			}
			else if (pTargetUnit.nPosX > pSelectedUnit.nPosX) // east
			{
				if (pTargetUnit.nPosY < pSelectedUnit.nPosY)
					Direction = 3; // Northeast
				else if (pTargetUnit.nPosY > pSelectedUnit.nPosY)
					Direction = 4; // Southeast;
				else
					Direction = 5; // east
			}
			else
			{
				if (pTargetUnit.nPosY < pSelectedUnit.nPosY)
					Direction = 6; // north;
				else
					Direction = 7; // South
			}
			std::pair<int, Vec2D> tmp;

			switch (Direction)
			{
			case 0:
				tmp.first = nPreference;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 1:
				tmp.first = nPreference + 1;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 2:
				tmp.first = nPreference + 1;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 3:
				tmp.first = nPreference;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 4:
				tmp.first = nPreference + 1;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 5:
				tmp.first = nPreference + 1;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 6:
				tmp.first = nPreference;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			case 7:
				tmp.first = nPreference + 1;
				tmp.second = AdjacentSouth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentWest;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference + 1;
				tmp.second = AdjacentEast;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				tmp.first = nPreference;
				tmp.second = AdjacentNorth;
				if (!CTileManager::GetInstance()->GetTile(tmp.second.nPosX, tmp.second.nPosY)->GetIfPassable())
				{
					vTargets.push_back(tmp);
				}
				break;
			}
		}
		int nLowestPreference = INT_MAX;

		for (std::list<std::pair<int, Vec2D>>::iterator iter = vTargets.begin(); iter != vTargets.end(); ++iter)
		{
			if ((*iter).first < nLowestPreference)
				nLowestPreference = (*iter).first;
		}

		for (std::list<std::pair<int, Vec2D>>::iterator iter = vTargets.begin(); iter != vTargets.end();)
		{
			if ((*iter).first == nLowestPreference)
			{
				vTarget = (*iter).second;
				vTargets.erase(iter++);
			}
			if (iter != vTargets.end())
				++iter;

		}
		nPreference++;

	}
	int x = 9;

	return vTarget;
}
void CAIManager::MoveUnit(CUnit* pMoveUnit)
{
	CUnit* pNearestEnemy;
	int lowestDistance = INT_MAX;
	int nNumToMove = INT_MAX;
	bool bSkipMove = false;

	std::vector<CUnit*> vUnitsUnder25;

	if (pMoveUnit->GetType() == UT_SWORDSMAN)
	{
		// Check surrounding tiles for occupation by enemies.
		int nNumEnemiesNearby = 0;
		Vec2D myPos = pMoveUnit->GetPos();
		// north
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(myPos.nPosX, myPos.nPosY - 1));
		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() != pMoveUnit->GetPlayerID())
			{
				nNumEnemiesNearby++;
			}
		}
		// south
		pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(myPos.nPosX, myPos.nPosY + 1));
		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() != pMoveUnit->GetPlayerID())
			{
				nNumEnemiesNearby++;
			}
		}
		// west
		pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(myPos.nPosX -1, myPos.nPosY));
		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() != pMoveUnit->GetPlayerID())
			{
				nNumEnemiesNearby++;
			}
		}

		// east
		pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(myPos.nPosX + 1, myPos.nPosY));
		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() != pMoveUnit->GetPlayerID())
			{
				nNumEnemiesNearby++;
			}
		}

		if (nNumEnemiesNearby >= 2)
		{
			bSkipMove = false;
			m_vInputQueue.push_back(INPUT_AI_CLEAR);
			m_vInputQueue.push_back(INPUT_AI_MOVED);
			m_vInputQueue.push_back(INPUT_ACCEPT);
			m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
			SelectUnit(pMoveUnit);
		}
	}
	else if (pMoveUnit->GetType() == UT_HERO)
	{
		if ((float)((float)pMoveUnit->GetHP() / (float)pMoveUnit->GetMaxHP() <= 0.25f))
		{
			bSkipMove = true;
		}
		for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
		{
			CUnit* pWorkUnit = CGameManager::GetInstance()->GetUnits()[i];
			if (pWorkUnit->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			{
				if (pWorkUnit->GetType() == UT_HERO || pWorkUnit->GetType() == UT_CASTLE)
				{
					continue;
				}
				if ((float)((float)pWorkUnit->GetHP() / (float)pWorkUnit->GetMaxHP()) <= 0.25f)
				{
					vUnitsUnder25.push_back(pWorkUnit);
				}
			}
		}
		if (vUnitsUnder25.size() >= 1)
			bSkipMove = true;
	}
	if (!bSkipMove)
	{
		for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
		{
			if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
			{
				CUnit* pWorkUnit = CGameManager::GetInstance()->GetUnits()[i];
				int xDist = (pWorkUnit->GetPos().nPosX - pMoveUnit->GetPos().nPosX);
				int yDist = (pWorkUnit->GetPos().nPosY - pMoveUnit->GetPos().nPosY);
				int dist = (int)(abs((double)xDist) + abs((double)yDist));
				if (dist < lowestDistance)
				{
					lowestDistance = dist;
					pNearestEnemy = pWorkUnit;
				}
			}
		}
		if (pMoveUnit->GetType() != UT_HERO && pMoveUnit->GetFleeing() == true)
		{

			CUnit* pChampion = CGameManager::GetInstance()->GetChampion(pMoveUnit->GetPlayerID());
			if (pChampion != nullptr)
				pNearestEnemy = pChampion;
		}
		Vec2D nearest;
		int xDistance = pNearestEnemy->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		int yDistance = pNearestEnemy->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;
		if ((abs(double(xDistance)) + abs(double(yDistance))) == 1)
		{
			bSkipMove = false;
			m_vInputQueue.push_back(INPUT_AI_CLEAR);
			m_vInputQueue.push_back(INPUT_AI_MOVED);
			return;
		}
		if (pMoveUnit->GetType() == UT_ARCHER)
		{
			if (lowestDistance <= 3)
			{
				bSkipMove = false;
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_MOVED);
				return;
			}
			else
			{
				nearest = NearestOpen(pNearestEnemy->GetPos(), pMoveUnit->GetPos());
			}

		}
		else
			nearest = NearestOpen(pNearestEnemy->GetPos(), pMoveUnit->GetPos());

		int x = 9;
		xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;

		bSkipMove = false;
		m_vInputQueue.push_back(INPUT_AI_CLEAR);
		m_vInputQueue.push_back(INPUT_AI_MOVED);
		m_vInputQueue.push_back(INPUT_ACCEPT);

		if (xDistance > pMoveUnit->GetSpeed())
		{
			xDistance = pMoveUnit->GetSpeed();
		}
		if (yDistance > pMoveUnit->GetSpeed())
		{
			yDistance = pMoveUnit->GetSpeed();
		}
		for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
		{
			if (xDistance < 0)
				m_vInputQueue.push_back(INPUT_LEFT);
			if (xDistance > 0)
				m_vInputQueue.push_back(INPUT_RIGHT);
			else
				continue;
		}
		for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
		{
			if (yDistance < 0)
				m_vInputQueue.push_back(INPUT_UP);
			if (yDistance > 0)
				m_vInputQueue.push_back(INPUT_DOWN);
			else
				continue;
		}
		m_vInputQueue.push_back(INPUT_ACCEPT);
		m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_1);
		SelectUnit(pMoveUnit);
	}
	// These perform first.  
	if (pMoveUnit->GetType() == UT_HERO)
	{
		// hero stuff
		// Am I under 25% hp?
		int nFoundIndex = -1;

		if ((float)((float)(pMoveUnit->GetHP()) / (float)pMoveUnit->GetMaxHP()) <= 0.25f)
		{
			CHero* pHero = dynamic_cast<CHero*>(pMoveUnit);
			if (pHero != nullptr)
			{
				for (int i = 0; i < 4; ++i)
				{
					CAbility* pAbility = pHero->GetSpell(i);
					if (pAbility != nullptr)
					{
						if (pAbility->GetType() == SP_HEAL)
							nFoundIndex = i;
					}
				}
				if (nFoundIndex != -1) // we found the heal spell!
				{
					bSkipMove = false;
					m_vInputQueue.push_back(INPUT_AI_CLEAR);
					m_vInputQueue.push_back(INPUT_AI_MOVED);

					m_vInputQueue.push_back(INPUT_ACCEPT);
					m_vInputQueue.push_back(INPUT_ACCEPT);
					switch (nFoundIndex)
					{
					case 0:
						m_vInputQueue.push_back(INPUT_AI_SELECTSPELL1);
						break;
					case 1:
						m_vInputQueue.push_back(INPUT_AI_SELECTSPELL2);
						break;
					case 2:
						m_vInputQueue.push_back(INPUT_AI_SELECTSPELL3);

						break;
					case 3:
						m_vInputQueue.push_back(INPUT_AI_SELECTSPELL4);
						break;
					}
					m_vInputQueue.push_back(INPUT_ACCEPT);
					m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
					//m_vInputQueue.push_back(INPUT_ACCEPT);
					SelectUnit(pMoveUnit);

				}
			}
		}
		else
		{
			// Is anyone else under 25% hp?
			for (unsigned int i = 0; i < vUnitsUnder25.size(); ++i)
			{
				int xDistance = vUnitsUnder25[i]->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
				int yDistance = vUnitsUnder25[i]->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_MOVED);
				m_vInputQueue.push_back(INPUT_ACCEPT);

				for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
				{
					if (xDistance < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					if (xDistance > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
					else
						continue;
				}
				for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
				{
					if (yDistance < 0)
						m_vInputQueue.push_back(INPUT_UP);
					if (yDistance > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
					else
						continue;
				}
				CHero* pHero = dynamic_cast<CHero*>(pMoveUnit);
				if (pHero != nullptr)
				{
					for (int i = 0; i < 4; ++i)
					{
						CAbility* pAbility = pHero->GetSpell(i);
						if (pAbility != nullptr)
						{
							if (pAbility->GetType() == SP_HEAL)
								nFoundIndex = i;
						}
					}
				}

				bSkipMove = false;
				m_vInputQueue.push_back(INPUT_ACCEPT);
				switch (nFoundIndex)
				{
				case 0:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL1);
					break;
				case 1:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL2);
					break;
				case 2:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL3);

					break;
				case 3:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL4);
					break;
				}
				//m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_ACCEPT);

				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
				SelectUnit(pMoveUnit);
			}
		}

	}
}

void CAIManager::AttackUnit(CUnit* pAttackUnit)
{

	CUnit* pNearestEnemy;
	int lowestDistance = INT_MAX;
	int nNumToMove = INT_MAX;
	int nFoundIndex = -1;
	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() !=CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			CUnit* pWorkUnit = CGameManager::GetInstance()->GetUnits()[i];
			int xDist = (pWorkUnit->GetPos().nPosX - pAttackUnit->GetPos().nPosX);
			int yDist = (pWorkUnit->GetPos().nPosY - pAttackUnit->GetPos().nPosY);
			int dist = (int)(abs((double)xDist) + abs((double)yDist));
			if (dist < lowestDistance)
			{
				lowestDistance = dist;
				pNearestEnemy = pWorkUnit;
			}
		}
	}
	Vec2D nearest = pNearestEnemy->GetPos();

	// Calvary charge check
	bool bDoCharge = false;
	int chargeXDistance = pNearestEnemy->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
	int chargeYDistance = pNearestEnemy->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;

	if (chargeXDistance == 1)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX + 1, pNearestEnemy->GetPos().nPosY);
		if (pTestUnit != nullptr)
			bDoCharge = true;
	}
	else if (chargeXDistance == -1)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX - 1, pNearestEnemy->GetPos().nPosY);
		if (pTestUnit != nullptr)
			bDoCharge = true;
	}
	else if (chargeYDistance == 1)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX, pNearestEnemy->GetPos().nPosY + 1);
		if (pTestUnit != nullptr)
			bDoCharge = true;
	}
	else if (chargeYDistance == -1)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX, pNearestEnemy->GetPos().nPosY - 1);
		if (pTestUnit != nullptr)
			bDoCharge = true;
	}
	// calvary
	if (pAttackUnit->GetType() == UT_CAVALRY && bDoCharge == true)
	{
		// Get the facing from me to my nearest enemy
		int xDistance = pNearestEnemy->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		int yDistance = pNearestEnemy->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;

		if (xDistance == 1) // east, so check for another enemy 2 tiles out
		{
			CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX + 1, pNearestEnemy->GetPos().nPosY);
			if (pTestUnit != nullptr) // there is someone behind the enemy
			{
				// cast charge
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_RIGHT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_RIGHT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_RIGHT);
				m_vInputQueue.push_back(INPUT_RIGHT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_RIGHT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
			}
		}
		else if (xDistance == -1)
		{
			CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX - 1, pNearestEnemy->GetPos().nPosY);
			if (pTestUnit != nullptr) // there is someone behind the enemy
			{
				// cast charge
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_LEFT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_LEFT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_LEFT);
				m_vInputQueue.push_back(INPUT_LEFT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_LEFT);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
			}
		}
		else if (yDistance == 1)
		{
			CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX, pNearestEnemy->GetPos().nPosY + 1);
			if (pTestUnit != nullptr) // there is someone behind the enemy
			{
				// cast charge
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_DOWN);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_DOWN);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_DOWN);
				m_vInputQueue.push_back(INPUT_DOWN);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_DOWN);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
			}
		}
		else if (yDistance == -1)
		{
			CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pNearestEnemy->GetPos().nPosX, pNearestEnemy->GetPos().nPosY - 1);
			if (pTestUnit != nullptr) // there is someone behind the enemy
			{
				// cast charge
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_UP);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_UP);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_UP);
				m_vInputQueue.push_back(INPUT_UP);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_UP);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
			}
		}
	}
	// cast fireball on the nearest enemy if it's under 50% hp to try to burst it down
	else if (pAttackUnit->GetType() == UT_ARCHER && ((pAttackUnit->GetAttack() > 6) || (pNearestEnemy->GetHP() < 12)) )
	{
		int xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		int yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;


		if (abs(double(xDistance + yDistance)) > pAttackUnit->GetRange())
		{
			m_vInputQueue.push_back(INPUT_AI_CLEAR);

			m_vInputQueue.push_back(INPUT_AI_ATTACKED);
			return;
		}
		m_vInputQueue.push_back(INPUT_AI_CLEAR);
		m_vInputQueue.push_back(INPUT_AI_ATTACKED);
		m_vInputQueue.push_back(INPUT_ACCEPT);

		for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
		{
			if (xDistance < 0)
				m_vInputQueue.push_back(INPUT_LEFT);
			if (xDistance > 0)
				m_vInputQueue.push_back(INPUT_RIGHT);
			else
				continue;
		}
		for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
		{
			if (yDistance < 0)
				m_vInputQueue.push_back(INPUT_UP);
			if (yDistance > 0)
				m_vInputQueue.push_back(INPUT_DOWN);
			else
				continue;
		}
		m_vInputQueue.push_back(INPUT_ACCEPT);
		m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);

	}
	else if (pAttackUnit->GetType() == UT_HERO)
	{
		CHero* pHero = dynamic_cast<CHero*>(pAttackUnit);
		if (pHero != nullptr)
		{
			for (int i = 0; i < 4; ++i)
			{
				CAbility* pAbility = pHero->GetSpell(i);
				if (pAbility != nullptr)
				{
					if (pAbility->GetType() == SP_FIREBALL)
						nFoundIndex = i;
				}
			}
		}

		if ((float)((float)pNearestEnemy->GetHP() / (float)pNearestEnemy->GetMaxHP()) < 0.5f)
		{
			int xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
			int yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;


			if (abs(double(xDistance + yDistance)) < CAbilityManager::GetInstance()->GetAbility(SP_FIREBALL)->GetRange())
			{
				int xDistance = pNearestEnemy->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
				int yDistance = pNearestEnemy->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				m_vInputQueue.push_back(INPUT_ACCEPT);

				for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
				{
					if (xDistance < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					if (xDistance > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
					else
						continue;
				}
				for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
				{
					if (yDistance < 0)
						m_vInputQueue.push_back(INPUT_UP);
					if (yDistance > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
					else
						continue;
				}


				m_vInputQueue.push_back(INPUT_ACCEPT);
				switch (nFoundIndex)
				{
				case 0:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL1);
					break;
				case 1:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL2);
					break;
				case 2:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL3);

					break;
				case 3:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL4);
					break;
				}
				m_vInputQueue.push_back(INPUT_ACCEPT);

				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
				SelectUnit(pAttackUnit);
			}
		}
		else
		{

			int xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
			int yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;


			if (abs(double(xDistance + yDistance)) > pAttackUnit->GetRange())
			{
				m_vInputQueue.push_back(INPUT_AI_CLEAR);

				m_vInputQueue.push_back(INPUT_AI_ATTACKED);
				return;
			}
			m_vInputQueue.push_back(INPUT_AI_CLEAR);
			m_vInputQueue.push_back(INPUT_AI_ATTACKED);
			m_vInputQueue.push_back(INPUT_ACCEPT);

			for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
			{
				if (xDistance < 0)
					m_vInputQueue.push_back(INPUT_LEFT);
				if (xDistance > 0)
					m_vInputQueue.push_back(INPUT_RIGHT);
				else
					continue;
			}
			for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
			{
				if (yDistance < 0)
					m_vInputQueue.push_back(INPUT_UP);
				if (yDistance > 0)
					m_vInputQueue.push_back(INPUT_DOWN);
				else
					continue;
			}
			m_vInputQueue.push_back(INPUT_ACCEPT);
			m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_2);
		}
	}
	else
	{

		int xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		int yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;


		if (abs(double(xDistance + yDistance)) > pAttackUnit->GetRange())
		{
			m_vInputQueue.push_back(INPUT_AI_CLEAR);

			m_vInputQueue.push_back(INPUT_AI_ATTACKED);
			return;
		}
		m_vInputQueue.push_back(INPUT_AI_CLEAR);
		m_vInputQueue.push_back(INPUT_AI_ATTACKED);
		m_vInputQueue.push_back(INPUT_ACCEPT);

		for (int i = 0; i < (int)(abs(double(xDistance))); ++i)
		{
			if (xDistance < 0)
				m_vInputQueue.push_back(INPUT_LEFT);
			if (xDistance > 0)
				m_vInputQueue.push_back(INPUT_RIGHT);
			else
				continue;
		}
		for (int i = 0; i < (int)(abs(double(yDistance))); ++i)
		{
			if (yDistance < 0)
				m_vInputQueue.push_back(INPUT_UP);
			if (yDistance > 0)
				m_vInputQueue.push_back(INPUT_DOWN);
			else
				continue;
		}
		m_vInputQueue.push_back(INPUT_ACCEPT);
		m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_2);

	}

}
bool CAIManager::CheckOrderQueue(float fElapsedTime)
{
	if (m_vOrderQueue.size() != 0)
	{
		// We have orders. Let's process them. 
		AIOrder order = m_vOrderQueue.front();

		// What type of order is it?
		switch (order.second)
		{
		case AIO_DESELECTALL: // Deselect everything
			{
				m_vInputQueue.push_back(INPUT_AI_CLEAR);
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_SELECTTILE:
			{
				Vec2D* pTileToSelect = (Vec2D*)order.first;
				Vec2D vCursorPosition = CGameplayState::GetInstance()->GetSelectionPos();
				Vec2D vTileToSelect = *pTileToSelect;
				delete pTileToSelect;
				// Find out how much we have to move the selection cursor to get to our intended unit
				int xDelta = vTileToSelect.nPosX - vCursorPosition.nPosX;
				int yDelta = vTileToSelect.nPosY - vCursorPosition.nPosY;

				// Move it over to the unit!
				for (int xD = 0; xD < (int)(abs(double(xDelta))); ++xD)
				{
					if (xDelta < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					else if (xDelta > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
					else
						continue;
				}
				for (int yD = 0; yD < (int)(abs(double(yDelta))); ++yD)
				{
					if (yDelta < 0)
						m_vInputQueue.push_back(INPUT_UP);
					else if (yDelta > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
					else
						continue;
				}
				// Press enter to select him
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// At this point the intended unit should be targeted and we hit enter on him to select him.
				// We can use this for attacking as well, since we could in theory call to use the attack ability
				// and then move this cursor to the intended target

				// This lets the input queue know we are finshed issueing commands and to release the UpdateAI to allow for the
				// next order to be processed
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_SELECT: // Select a unit. The unit will be specified in the Void*
			{
				CUnit* pUnitToSelect = (CUnit*)order.first;
				Vec2D vCursorPosition = CGameplayState::GetInstance()->GetSelectionPos();
				Vec2D vUnitPosition = pUnitToSelect->GetPos();


				// Find out how much we have to move the selection cursor to get to our intended unit
				int xDelta = vUnitPosition.nPosX - vCursorPosition.nPosX;
				int yDelta = vUnitPosition.nPosY - vCursorPosition.nPosY;

				// Move it over to the unit!
				for (int xD = 0; xD < (int)(abs(double(xDelta))); ++xD)
				{
					if (xDelta < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					else if (xDelta > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
					else
						continue;
				}
				for (int yD = 0; yD < (int)(abs(double(yDelta))); ++yD)
				{
					if (yDelta < 0)
						m_vInputQueue.push_back(INPUT_UP);
					else if (yDelta > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
					else
						continue;
				}
				// Press enter to select him
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// At this point the intended unit should be targeted and we hit enter on him to select him.
				// We can use this for attacking as well, since we could in theory call to use the attack ability
				// and then move this cursor to the intended target

				// This lets the input queue know we are finshed issueing commands and to release the UpdateAI to allow for the
				// next order to be processed
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_SKIRMISH: 
			// Immediately scatter the unit into a semi-random direction 1 tile. We don't care where, we just
			// need to get out of here quick!
			{
				CUnit* pUnit = (CUnit*)order.first;
				Vec2D vCursorPosition = CGameplayState::GetInstance()->GetSelectionPos();
				Vec2D vUnitPosition = pUnit->GetPos();

				// First lets make sure all of our adjacents are not full, otherwise we're stuck and will just do nothing
				int nFoundUnits = 0;
				Vec2D vRunToPosition;
				CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(vUnitPosition.nPosX - 1, vUnitPosition.nPosY));
				if (pTestUnit == nullptr)
				{
					vRunToPosition = Vec2D(vUnitPosition.nPosX - 1, vUnitPosition.nPosY);
				}
				else
				{
					pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(vUnitPosition.nPosX + 1, vUnitPosition.nPosY));
					if (pTestUnit == nullptr)
					{
						vRunToPosition = Vec2D(vUnitPosition.nPosX + 1, vUnitPosition.nPosY);
					}
					else
					{
						pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(vUnitPosition.nPosX, vUnitPosition.nPosY + 1));
						if (pTestUnit == nullptr)
						{
							vRunToPosition = Vec2D(vUnitPosition.nPosX, vUnitPosition.nPosY + 1);
						}
						else
						{
							pTestUnit = CGameManager::GetInstance()->FindUnit(Vec2D(vUnitPosition.nPosX, vUnitPosition.nPosY - 1));
							if (pTestUnit == nullptr)
							{
								vRunToPosition = Vec2D(vUnitPosition.nPosX, vUnitPosition.nPosY - 1);
							}
							else
							{
								 // Whelp, we're surrounded. Better accept our fate
								m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
								break;
							}
						}
					}
				}
				// If there aren't 4 guys around us, we have an out! START RUNNIN
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_1);
				m_vInputQueue.push_back(INPUT_ACCEPT);
				
				// This code copied from AIO_MOVE, should function the same. Could probably call it instead but, whatever. 
				int xDelta = vRunToPosition.nPosX - vCursorPosition.nPosX;
				int yDelta = vRunToPosition.nPosY - vCursorPosition.nPosY;

				for (int dX = 0; dX < (int)(abs((float)(xDelta))); ++dX)
				{
					if (xDelta < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					else if (xDelta > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
				}
				for (int dY = 0; dY < (int)(abs((float)(yDelta))); ++dY)
				{
					if (yDelta < 0)
						m_vInputQueue.push_back(INPUT_UP);
					else if (yDelta > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
				}

				// And hit enter to begin the move
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// The order is finished at this point, so let's tell the input stack we're done
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_MOVE:
			{
				Vec2D* pTargetPosition = (Vec2D*)order.first;
				Vec2D vCursorPosition = CGameplayState::GetInstance()->GetSelectionPos();
				Vec2D vUnitPosition = *pTargetPosition;
				delete pTargetPosition;

				// We assume that the unit is selected at this point, so let's select ability 1 (move)
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_1);
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// At this point we have the movement spell selected, hit enter and should now be in movement reticle mode
				// Now we move the cursor to the nearestOpen to the target position;
				Vec2D nearest = NearestOpen(vUnitPosition, vCursorPosition);

				// Nearest is assumed to be the closest open position to where we want in preference to the direction we are coming from


				// Lets find out how much we have to move the cursor to get there
				int xDelta = nearest.nPosX - vCursorPosition.nPosX;
				int yDelta = nearest.nPosY - vCursorPosition.nPosY;

				// And move the cursor to that position

				// Let's limit the amount of tiles it'll try to move... no point moving the cursor 30 tiles across
				// the map since the unit wont go that far. Fastest unit would be a cavalry at 5 speed, let's assume
				// the stars align and he gets sped up to 8. No one should ever be able to move more than 8 tiles
				// so lets make it 10 to be safe;
				int nMovesRemaining = 7;
				int nXChanged = 0;
				int nYChanged = 0;


				// First lets find out where we end up with the tile movement limitation
				while (nMovesRemaining > 0)
				{
					if (xDelta < 0)
					{
						xDelta++;
						nXChanged--;
					}
					else if (xDelta > 0)
					{
						xDelta--;
						nXChanged++;
					}
					nMovesRemaining--;
					if (nMovesRemaining <= 0)
						break;

					if (yDelta < 0)
					{
						yDelta++;
						nYChanged--;
					}
					else if (yDelta > 0)
					{
						yDelta--;
						nYChanged++;
					}

					nMovesRemaining--;
				}

				Vec2D vFinalTarget = Vec2D(vCursorPosition.nPosX + nXChanged , vCursorPosition.nPosY + nYChanged);

				// So now we know how far our cursor will move and where it will end up
				// Lets make sure no one is on that tile
				Vec2D nearestToFinal = NearestOpen(vFinalTarget, vCursorPosition);

				// If our final is empty, we'll end up on it. If not, we'll end up on the closest we can get to it;

				// This is how much our cursor needs to change from its relative position to get to our final destination
				int xDeltaF = nearestToFinal.nPosX - vCursorPosition.nPosX;
				int yDeltaF = nearestToFinal.nPosY - vCursorPosition.nPosY;

				// Move the cursor
				for (int dX = 0; dX < (int)(abs((float)(xDeltaF))); ++dX)
				{
					if (xDeltaF < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					else if (xDeltaF > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
				}
				for (int dY = 0; dY < (int)(abs((float)(yDeltaF))); ++dY)
				{
					if (yDeltaF < 0)
						m_vInputQueue.push_back(INPUT_UP);
					else if (yDeltaF > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
				}
				// And hit enter to begin the move
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// The order is finished at this point, so let's tell the input stack we're done
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_MOVECURSOR:
			{
				Vec2D* pTargetPos = (Vec2D*)order.first;
				Vec2D vCursorPosition = CGameplayState::GetInstance()->GetSelectionPos();
				Vec2D vTargetPosition = *pTargetPos;
				delete pTargetPos;


				// Find out how much we have to move the selection cursor to get to our intended location
				int xDelta = vTargetPosition.nPosX - vCursorPosition.nPosX;
				int yDelta = vTargetPosition.nPosY - vCursorPosition.nPosY;

				// Move it over to the target position
				for (int xD = 0; xD < (int)(abs(double(xDelta))); ++xD)
				{
					if (xDelta < 0)
						m_vInputQueue.push_back(INPUT_LEFT);
					else if (xDelta > 0)
						m_vInputQueue.push_back(INPUT_RIGHT);
					else
						continue;
				}
				for (int yD = 0; yD < (int)(abs(double(yDelta))); ++yD)
				{
					if (yDelta < 0)
						m_vInputQueue.push_back(INPUT_UP);
					else if (yDelta > 0)
						m_vInputQueue.push_back(INPUT_DOWN);
					else
						continue;
				}

				// At this point it should be where we want, finish the order
				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_PICKABILITY:
			{
				int* pAbilityNum = (int*)order.first;
				int abilSlot = *pAbilityNum;
				delete pAbilityNum;

				// Now we know what ability we want to get and accept on, let's go ahead and find it
				switch (abilSlot)
				{
				case 1:
					m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_1);
					break;
				case 2:
					m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_2);
					break;
				case 3:
					m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
					break;
				}

				// So now we have it highlighted with our cursor, lets hit enter to pick it
				m_vInputQueue.push_back(INPUT_ACCEPT);

				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		case AIO_PICKSPELL:
			{
				int* pSpellNum = (int*)order.first;
				int pSpellSlot = *pSpellNum;
				delete pSpellNum;

				// Since we want a spell, we need to pick ability 3 and press accept to go into the spell panel
				m_vInputQueue.push_back(INPUT_AI_SELECTABILITY_3);
				m_vInputQueue.push_back(INPUT_ACCEPT);

				// Now we're in the spell panel, pick the ability you want
				switch (pSpellSlot)
				{
				case 1:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL1);
					break;
				case 2:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL2);
					break;
				case 3:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL3);
					break;
				case 4:
					m_vInputQueue.push_back(INPUT_AI_SELECTSPELL4);
					break;
				}

				// Spell is highlighted, lets push enter to begin it's mode
				m_vInputQueue.push_back(INPUT_ACCEPT);

				m_vInputQueue.push_back(INPUT_AI_ORDERFINISHED);
			}
			break;
		}
		// Remove the order from the queue, we should be done at this point
		m_vOrderQueue.erase(m_vOrderQueue.begin());

		return true;
	}

	return false;
}
void CAIManager::UpdateAI(float fElapsedTime)
{
	bool bAITurn = false;
	for (unsigned int i = 0; i < m_vPlayerIDs.size(); ++i)
	{
		if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() == m_vPlayerIDs[i])
			bAITurn = true;
	}
	if (!bAITurn)
		return;
	if (bAITurn)
	{
		//if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() ==CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		//{
		if (CheckInputQueue(fElapsedTime))
			return;

		if (CheckOrderQueue(fElapsedTime))
			return;

		if (m_vUnitsToHandle.size() != 0)
		{
				RunAIScript(m_vUnitsToHandle.front());
		}
		else
			m_vInputQueue.push_back(INPUT_START);

		//if (m_vUnitsToHandle.size() == 0)
		//{
		//	// im done all my stuff this phase, move onto next phase!
		//	m_vInputQueue.push_back(INPUT_START);
		//}

		//if (CGameManager::GetInstance()->GetCurrentPhase() == GP_ATTACK)
		//{
		//	if (m_bDone == true)
		//	{
		//		if (m_bSelected)
		//		{
		//			if (m_bAttacked )
		//			{
		//				AttackUnit(m_pFocusUnit);
		//				m_bSelected = false;
		//				m_bAttacked = false;
		//			}

		//		}
		//		else if (m_bSelected == false)
		//		{
		//			if (m_vUnitsToHandle.size() != 0)
		//			{
		//				m_pFocusUnit = m_vUnitsToHandle.back();
		//				m_bSelected = false;
		//				m_vUnitsToHandle.pop_back();
		//			}
		//			else
		//				m_pFocusUnit = nullptr;

		//			if (m_pFocusUnit != nullptr)
		//				SelectUnit(m_pFocusUnit);
		//		}
		//	}


		//}
		//else if (CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
		//{
		//	if (m_bDone == true)
		//	{
		//		if (m_bSelected == true)
		//		{
		//			if (m_bMoved == true)
		//			{
		//				MoveUnit(m_pFocusUnit);
		//				m_bSelected = false;
		//				m_bMoved = false;
		//			}
		//		}
		//		else if (m_bSelected == false)
		//		{
		//			if (m_vUnitsToHandle.size() != 0)
		//			{
		//				m_pFocusUnit = m_vUnitsToHandle.back();
		//				m_bSelected = false;
		//				m_vUnitsToHandle.pop_back();
		//			}
		//			else
		//				m_pFocusUnit = nullptr;

		//			if (m_pFocusUnit != nullptr)
		//				SelectUnit(m_pFocusUnit);
		//		}
		//	}
		//}
	}

}

// ISSUE ORDER takes in a few different things depending on the order you are issueing.
// The first variable is the order type. Orders are case sensitive, so dont capitalize
// The next variables depend on the order type
int CAIManager::IssueOrder(lua_State* L)
{
	std::string orderString = lua_tostring(L, 1);
	CAIManager* pAIM = CAIManager::GetInstance();
	if (orderString.compare("deselectall") == 0)
	{
		AIOrder order;
		order.second = AIO_DESELECTALL;
		pAIM->m_vOrderQueue.push_back(order);

	}
	else if (orderString.compare("selectunit") == 0)
	{
		// The order was select unit. In this case, we are selecting via uniqueID
		CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID((int)lua_tointeger(L, 2));
		if (pUnit == nullptr)
			return 0;

		AIOrder order;
		order.first = pUnit;
		order.second = AIO_SELECT;
		pAIM->m_vOrderQueue.push_back(order);
	}
	else if (orderString.compare("move") == 0)
	{
		int nposX = lua_tointeger(L, 2);
		int nposY = lua_tointeger(L, 3);

		AIOrder order;
		order.first = new Vec2D(nposX, nposY);
		order.second = AIO_MOVE;
		pAIM->m_vOrderQueue.push_back(order);
	}
	else if (orderString.compare("selecttile") == 0)
	{
		int nposX = lua_tointeger(L, 2);
		int nposY = lua_tointeger(L, 3);

		AIOrder order;
		order.first = new Vec2D(nposX, nposY);
		order.second = AIO_SELECTTILE;
		pAIM->m_vOrderQueue.push_back(order);

	}
	else if (orderString.compare("skirmish") == 0)
	{
		// Scatter the unit in any direction as long as it's not right where we are!
		int nUnitID = lua_tointeger(L, 2);
		AIOrder order;
		order.first = CGameManager::GetInstance()->GetUnitByID(nUnitID);
		order.second = AIO_SKIRMISH;
		pAIM->m_vOrderQueue.push_back(order);

	}
	else if (orderString.compare("selectability") == 0)
	{
		int nAbilityID = lua_tointeger(L, 2);
		AIOrder order;
		order.first = new int(nAbilityID);
		order.second = AIO_PICKABILITY;
		pAIM->m_vOrderQueue.push_back(order);
	}
	else if (orderString.compare("selectspell") == 0)
	{
		int nSpellID = lua_tointeger(L, 2);
		AIOrder order;
		order.first = new int(nSpellID);
		order.second = AIO_PICKSPELL;
		pAIM->m_vOrderQueue.push_back(order);
	}
	return 0;
}

void CAIManager::RunAIScript(CUnit* pUnit)
{
	lua_State* L = AIL;
	lua_settop(L, 0);
	lua_pushinteger(L, pUnit->GetUniqueID());
	lua_setglobal(L, "unitID");

	std::string path;
	switch (pUnit->GetType())
	{
	case UT_ARCHER:
		path = "Assets/Scripts/ai_archer.lua";
		break;
	case UT_CASTLE:
		path = "Assets/Scripts/ai_castle.lua";
		break;
	case UT_HERO:
		path = "Assets/Scripts/ai_hero.lua";
		break;
	case UT_CAVALRY:
		path = "Assets/Scripts/ai_cavalry.lua";
		break;
	case UT_SWORDSMAN:
		path = "Assets/Scripts/ai_swordsman.lua";
		break;
	case UT_SKELETON:
		path = "Assets/Scripts/ai_skeleton.lua";
		break;
	case UT_ICEBLOCK:
		path = "Assets/Scripts/ai_iceblock.lua";
		break;
	}

	luaL_dofile(L, path.c_str());

	if (CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
	{
		lua_getglobal(L, "Move");
	}
	else if (CGameManager::GetInstance()->GetCurrentPhase() == GP_ATTACK)
	{
		lua_getglobal(L, "Attack");
	}
	lua_pcall(L, 0, 0, 0);



	// By here we've run the LUA script and we should be done with the unit, so pop him off the list of guys to handle
	m_vUnitsToHandle.erase(m_vUnitsToHandle.begin());
}
int CAIManager::FindNearest(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);
	CUnit* pSelectUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	int nLowestDistance = INT_MAX;
	CUnit* pNearestEnemy;

	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() != CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			CUnit* pWorkUnit = CGameManager::GetInstance()->GetUnits()[i];
			int xDist = (pWorkUnit->GetPos().nPosX - pSelectUnit->GetPos().nPosX);
			int yDist = (pWorkUnit->GetPos().nPosY - pSelectUnit->GetPos().nPosY);
			int dist = (int)(abs((double)xDist) + abs((double)yDist));
			if (dist < nLowestDistance)
			{
				nLowestDistance = dist;
				pNearestEnemy = pWorkUnit;
			}
		}
	}

	if (pNearestEnemy->GetPos().nPosX < 0 || pNearestEnemy->GetPos().nPosY < 0 || pNearestEnemy->GetPos().nPosX > 5000 ||
		pNearestEnemy->GetPos().nPosY > 5000)
	{
		int x  = 9;

	}
	if (pNearestEnemy == nullptr)
		return 0;

	lua_pushinteger(L, pNearestEnemy->GetUniqueID());
	return 1;
}

int CAIManager::FindChampion(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);
	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	
	CUnit* pChampion = CGameManager::GetInstance()->GetChampion(pUnit->GetPlayerID());

	lua_pushinteger(L, pChampion->GetUniqueID());
	return 1;
}
int CAIManager::FindUnitByTile(lua_State* L)
{
	int nPosX = lua_tointeger(L, 1);
	int nPosY = lua_tointeger(L, 2);

	CUnit* pUnit = CGameManager::GetInstance()->FindUnit(nPosX, nPosY);

	if (pUnit == nullptr)
		lua_pushinteger(L, -1);
	else
		lua_pushinteger(L, pUnit->GetUniqueID());


	return 1;
}

int CAIManager::GetFriendlyUnitsInRange(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);
	int nRange = lua_tointeger(L, 2);

	std::vector< Vec2D > pattern;

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	pattern = CAbilityManager::GetInstance()->GetRange(nRange);


	lua_newtable(L);
	int nCount = 0;
	for (unsigned int i = 0; i < pattern.size(); ++i)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pUnit->GetPos().nPosX + pattern[i].nPosX, 
			pUnit->GetPos().nPosY + pattern[i].nPosY);

		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() == pUnit->GetPlayerID() && pTestUnit->GetType() != UT_CASTLE)
			{
				lua_newtable(L);
				lua_pushstring(L, "uniqueID");
				lua_pushinteger(L, pTestUnit->GetUniqueID());
				lua_settable(L, -3);
				lua_pushinteger(L, nCount+1);
				lua_insert(L, -2);
				lua_settable(L, -3);
				nCount++;
			}
		}
	}
	lua_setglobal(L, "unitData");
	return 0;
}

int CAIManager::GetEnemyUnitsInRange(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);
	int nRange = lua_tointeger(L, 2);

	std::vector< Vec2D > pattern;

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	pattern = CAbilityManager::GetInstance()->GetRange(nRange);


	lua_newtable(L);
	int nCount = 0;
	for (unsigned int i = 0; i < pattern.size(); ++i)
	{
		CUnit* pTestUnit = CGameManager::GetInstance()->FindUnit(pUnit->GetPos().nPosX + pattern[i].nPosX, 
			pUnit->GetPos().nPosY + pattern[i].nPosY);

		if (pTestUnit != nullptr)
		{
			if (pTestUnit->GetPlayerID() != pUnit->GetPlayerID()  && pTestUnit->GetType() != UT_CASTLE)
			{
				lua_newtable(L);
				lua_pushstring(L, "uniqueID");
				lua_pushinteger(L, pTestUnit->GetUniqueID());
				lua_settable(L, -3);
				lua_pushinteger(L, nCount+1);
				lua_insert(L, -2);
				lua_settable(L, -3);
				nCount++;
			}
		}
	}

	lua_setglobal(L, "enemyUnitData");
	return 0;
}

// resoucetype 1 == mill, 2 == mine
int CAIManager::FindNearestResource(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);
	int nResourceType = lua_tointeger(L, 2);

	CUnit* pUnit = CGameManager::GetInstance()->GetUnitByID(nUnitID);
	TILE_TYPE desiredType;
	if (nResourceType == 1)
		desiredType = TT_MILL;
	else if (nResourceType == 2)
		desiredType = TT_MINE;

	Vec2D vec = pUnit->GetPos();
	Vec2D foundTile;
	int maxDistance = 99999;

	for (int x = 0; x < CTileManager::GetInstance()->GetNumRows(); ++x)
		for (int y = 0; y < CTileManager::GetInstance()->GetNumColumns(); ++y)
		{
			if (CTileManager::GetInstance()->GetTile(x, y)->GetTileType() == desiredType)
			{
				int totalDistance = int(((abs((float)(x - vec.nPosX))) + (abs((float)(y - vec.nPosY)))));
				if (totalDistance < maxDistance)
				{
					maxDistance = totalDistance;
					foundTile.nPosX = x;
					foundTile.nPosY = y;
				}
			}
		}

	lua_pushinteger(L, foundTile.nPosX);
	lua_pushinteger(L, foundTile.nPosY);
	return 2;
}
CAIManager::CAIManager(void)
{
}
CAIManager::~CAIManager(void)
{
}

