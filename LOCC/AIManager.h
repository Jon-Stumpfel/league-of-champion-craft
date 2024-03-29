#pragma once

#include "StdAfx.h"
#include "Unit.h"

enum AI_ORDER { AIO_MOVE, AIO_SELECT, AIO_PICKABILITY, AIO_PICKSPELL, AIO_MOVECURSOR, AIO_DESELECTALL, AIO_SKIRMISH, AIO_SELECTTILE };

typedef std::pair<void*, AI_ORDER> AIOrder;

class CAIManager
{

public:

	static CAIManager* GetInstance(void);
	static void DeleteInstance(void);	

	void UpdateAI(float fElapsedTime);

	void BeginMovement(void);
	void BeginAttack(void);

	void Initialize(void);
	void Shutdown(void);
	void PushPlayerID(int nPlayerID) { m_vPlayerIDs.push_back(nPlayerID);}

	Vec2D NearestOpen(Vec2D pTargetUnit, Vec2D pSelectedUnit);

	void SetActionSpeed(float speed)		{m_fActionSpeed=speed;};
	float  GetActionSpeed(float speed)		{return m_fActionSpeed;};

private:
	float m_fActionSpeed;

	CAIManager(void);
	~CAIManager(void);
	CAIManager(const CAIManager&);
	CAIManager& operator=(const CAIManager&);

	bool CheckInputQueue(float fElapsedTime);
	bool CheckOrderQueue(float fElapsedTime);

	void SelectUnit(CUnit* pToSelect);
	void MoveUnit(CUnit* pMoveUnit);
	void AttackUnit(CUnit* pAttackUnit);
	static CAIManager* s_Instance;
public:
	typedef std::pair<int, TILE_TYPE> ResRegistry;
	std::vector<ResRegistry> m_vResourceRegistrations;

	void RunAIScript(CUnit* pUnit);

std::vector<AIOrder> m_vOrderQueue;

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

	bool m_bOrderFinished;

	lua_State* AIL;

public:
	// lua help functions
	static int IssueOrder(lua_State* L);
	static int FindNearest(lua_State* L);
	static int FindChampion(lua_State* L);
	static int FindUnitByTile(lua_State* L);
	static int GetFriendlyUnitsInRange(lua_State* L);
	static int GetEnemyUnitsInRange(lua_State* L);
	static int FindNearestResource(lua_State* L);
	static int GetNumUnitsCapturingResource(lua_State* L);
	static int IsUnitCapturingResource(lua_State* L);
	static int RegisterMeCapturingResource(lua_State* L);
};

