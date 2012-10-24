#include "StdAfx.h"
#include "AIManager.h"
#include "AbilityManager.h"
#include "StateStack.h"
#include "Player.h"
#include "GameManager.h"
#include "GameplayState.h"
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
}
void CAIManager::Shutdown(void)
{

}

void CAIManager::RemoveObject(CUnit* obj)
{
}
void CAIManager::RemoveAllObjects(void)
{
}

bool CAIManager::CheckInputQueue(float fElapsedTime)
{
	static float fTimeToPop = 0.0f;
	if (m_vInputQueue.size() != 0)
	{
		fTimeToPop += fElapsedTime;
		if (fTimeToPop > 0.8f)
		{
			if (m_vInputQueue.back() == INPUT_AI_ATTACKED)
			{
				m_bAttacked = true;
			}
			if (m_vInputQueue.back() == INPUT_AI_SELECTED)
			{
				m_bSelected = true;
			}
			if (m_vInputQueue.back() == INPUT_AI_MOVED)
			{
				m_bMoved = true;
				m_bSelected = false;
			}
			CStateStack::GetInstance()->GetTop()->Input(m_vInputQueue.back());
			if (m_vInputQueue.size() != 0)
				m_vInputQueue.pop_back();
			fTimeToPop = 0.0f;
			if (m_vInputQueue.size() == 0)
				m_bDone = true;
		}
	}

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
	m_bMoved = true;
	m_bDone = true;
	m_bSelected = false;
	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			if (CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_CASTLE)
				continue;
			m_vUnitsToHandle.push_back(CGameManager::GetInstance()->GetUnits()[i]);
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
	m_bMoved = true;
	m_bDone = true;
	m_bSelected = false;
	for (unsigned int i = 0; i < CGameManager::GetInstance()->GetUnits().size(); ++i)
	{
		if (CGameManager::GetInstance()->GetUnits()[i]->GetPlayerID() ==CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID())
		{
			if (CGameManager::GetInstance()->GetUnits()[i]->GetType() == UT_CASTLE)
				continue;
			m_vUnitsToHandle.push_back(CGameManager::GetInstance()->GetUnits()[i]);
		}
	}
}

Vec2D CAIManager::NearestOpen(CUnit* pTargetUnit, CUnit* pSelectedUnit)
{
	int xDistance = pTargetUnit->GetPos().nPosX - pSelectedUnit->GetPos().nPosX;
	int yDistance = pTargetUnit->GetPos().nPosY - pSelectedUnit->GetPos().nPosY;
	Vec2D vTarget = pTargetUnit->GetPos();
	std::list<std::pair<int, Vec2D>> vTargets;
	int nPreference = 1;
	while (CTileManager::GetInstance()->GetTile(vTarget.nPosX, vTarget.nPosY)->GetIfOccupied())
	{
		Vec2D AdjacentWest = Vec2D(vTarget.nPosX - 1, vTarget.nPosY);
		Vec2D AdjacentEast = Vec2D(vTarget.nPosX + 1, vTarget.nPosY);
		Vec2D AdjacentNorth = Vec2D(vTarget.nPosX, vTarget.nPosY - 1);
		Vec2D AdjacentSouth = Vec2D(vTarget.nPosX, vTarget.nPosY + 1);
		int Direction = -1;
		if (pTargetUnit->GetPos().nPosX < pSelectedUnit->GetPos().nPosX) // west
		{
			if (pTargetUnit->GetPos().nPosY < pSelectedUnit->GetPos().nPosY)
				Direction = 0; // Northwest
			else if (pTargetUnit->GetPos().nPosY > pSelectedUnit->GetPos().nPosY)
				Direction = 1; // Southwest;
			else
				Direction = 2; // West
		}
		else if (pTargetUnit->GetPos().nPosX > pSelectedUnit->GetPos().nPosX) // east
		{
			if (pTargetUnit->GetPos().nPosY < pSelectedUnit->GetPos().nPosY)
				Direction = 3; // Northeast
			else if (pTargetUnit->GetPos().nPosY > pSelectedUnit->GetPos().nPosY)
				Direction = 4; // Southeast;
			else
				Direction = 5; // east
		}
		else
		{
			if (pTargetUnit->GetPos().nPosY < pSelectedUnit->GetPos().nPosY)
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
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 1:
			tmp.first = nPreference + 1;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 2:
			tmp.first = nPreference + 1;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 3:
			tmp.first = nPreference;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 4:
			tmp.first = nPreference + 1;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 5:
			tmp.first = nPreference + 1;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 6:
			tmp.first = nPreference;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
		case 7:
			tmp.first = nPreference + 1;
			tmp.second = AdjacentSouth;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentWest;
			vTargets.push_back(tmp);
			tmp.first = nPreference + 1;
			tmp.second = AdjacentEast;
			vTargets.push_back(tmp);
			tmp.first = nPreference;
			tmp.second = AdjacentNorth;
			vTargets.push_back(tmp);
			break;
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
				nearest = NearestOpen(pNearestEnemy, pMoveUnit);
			}

		}
		else
			nearest = NearestOpen(pNearestEnemy, pMoveUnit);

		int x = 9;
		xDistance = nearest.nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
		yDistance = nearest.nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;

		bSkipMove = false;
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
	// cast fireball on the nearest enemy if it's under 50% hp to try to burst it down
	if (pAttackUnit->GetType() == UT_ARCHER && ((pAttackUnit->GetAttack() > 6) || (pNearestEnemy->GetHP() < 12)) )
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

		if (m_vUnitsToHandle.size() == 0)
		{
			// im done all my stuff this phase, move onto next phase!
			m_vInputQueue.push_back(INPUT_START);
		}

		if (CGameManager::GetInstance()->GetCurrentPhase() == GP_ATTACK)
		{
			if (m_bDone == true)
			{
				if (m_bSelected)
				{
					if (m_bAttacked )
					{
						AttackUnit(m_pFocusUnit);
						m_bSelected = false;
						m_bAttacked = false;
					}

				}
				else if (m_bSelected == false)
				{
					if (m_vUnitsToHandle.size() != 0)
					{
						m_pFocusUnit = m_vUnitsToHandle.back();
						m_bSelected = false;
						m_vUnitsToHandle.pop_back();
					}
					else
						m_pFocusUnit = nullptr;

					if (m_pFocusUnit != nullptr)
						SelectUnit(m_pFocusUnit);
				}
			}


		}
		else if (CGameManager::GetInstance()->GetCurrentPhase() == GP_MOVE)
		{
			if (m_bDone == true)
			{
				if (m_bSelected == true)
				{
					if (m_bMoved == true)
					{
						MoveUnit(m_pFocusUnit);
						m_bSelected = false;
						m_bMoved = false;
					}
				}
				else if (m_bSelected == false)
				{
					if (m_vUnitsToHandle.size() != 0)
					{
						m_pFocusUnit = m_vUnitsToHandle.back();
						m_bSelected = false;
						m_vUnitsToHandle.pop_back();
					}
					else
						m_pFocusUnit = nullptr;

					if (m_pFocusUnit != nullptr)
						SelectUnit(m_pFocusUnit);
				}
			}
		}
	}

}
void CAIManager::AddObject(CUnit* obj)
{
}


CAIManager::CAIManager(void)
{
}
CAIManager::~CAIManager(void)
{
}
