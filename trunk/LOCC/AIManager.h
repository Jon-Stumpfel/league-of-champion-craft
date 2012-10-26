#pragma once

#include "StdAfx.h"
#include "Unit.h"

class CAIManager
{

public:

	static CAIManager* GetInstance(void);
	static void DeleteInstance(void);	

	void RemoveObject(CUnit* obj);
	void RemoveAllObjects(void);
	void UpdateAI(float fElapsedTime);
	void AddObject(CUnit* obj);

	void BeginMovement(void);
	void BeginAttack(void);

	void Initialize(void);
	void Shutdown(void);
	void PushPlayerID(int nPlayerID) { m_vPlayerIDs.push_back(nPlayerID);}

	Vec2D NearestOpen(CUnit* pTargetUnit, Vec2D pSelectedUnit);

private:

	CAIManager(void);
	~CAIManager(void);
	CAIManager(const CAIManager&);
	CAIManager& operator=(const CAIManager&);

	bool CheckInputQueue(float fElapsedTime);
	void SelectUnit(CUnit* pToSelect);
	void MoveUnit(CUnit* pMoveUnit);
	void AttackUnit(CUnit* pAttackUnit);
	static CAIManager* s_Instance;

	std::vector<int> m_vPlayerIDs;
public:std::vector<INPUT_ENUM> m_vInputQueue;
private:std::vector<CUnit*> m_vUnitsToHandle;
	bool m_bHandlingUnits;
	bool m_bHandled;

	CUnit* m_pFocusUnit;
	bool m_bDone;
	bool m_bSelected;
	bool m_bMoved;
	bool m_bAttacked;
};

