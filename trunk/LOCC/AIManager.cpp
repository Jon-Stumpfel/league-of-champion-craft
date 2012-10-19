#include "StdAfx.h"
#include "AIManager.h"
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
		if (fTimeToPop > 0.1f)
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

	if (pMoveUnit->GetType() == UT_HERO)
	{
		// hero stuff
		// Am I under 25% hp?
		if (pMoveUnit->GetHP() / pMoveUnit->GetMaxHP() < 0.25f)
		{
			CHero* pHero = dynamic_cast<CHero*>(pMoveUnit);
			if (pHero != nullptr)
			{
				int nFoundIndex = -1;
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
				//	m_vInputQueue.push_back(INPUT_AI_CHAMPSPELL);

				}

			}
			
		}

	}
	CUnit* pNearestEnemy;
	int lowestDistance = INT_MAX;
	int nNumToMove = INT_MAX;
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
	Vec2D nearest;
	int xDistance = pNearestEnemy->GetPos().nPosX - CGameplayState::GetInstance()->GetSelectionPos().nPosX;
	int yDistance = pNearestEnemy->GetPos().nPosY - CGameplayState::GetInstance()->GetSelectionPos().nPosY;
	if ((abs(double(xDistance)) + abs(double(yDistance))) == 1)
	{
		m_vInputQueue.push_back(INPUT_AI_CLEAR);
		m_vInputQueue.push_back(INPUT_AI_MOVED);
		return;
	}
	if (pMoveUnit->GetType() == UT_ARCHER)
	{
		if (lowestDistance <= 3)
		{
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

	//if ((abs(double(xDistance)) + abs(double(yDistance))) == 1)
	//{
	//	m_vInputQueue.push_back(INPUT_AI_CLEAR);
	//	m_vInputQueue.push_back(INPUT_AI_MOVED);
	//	return;
	//}
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
}

void CAIManager::AttackUnit(CUnit* pAttackUnit)
{

	if (pAttackUnit->GetType() == UT_HERO)
	{
		// hero stuff
		// Am I under 25% hp?
		if (pAttackUnit->GetHP() / pAttackUnit->GetMaxHP() < 0.25f)
		{

		}

	}
	CUnit* pNearestEnemy;
	int lowestDistance = INT_MAX;
	int nNumToMove = INT_MAX;
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
