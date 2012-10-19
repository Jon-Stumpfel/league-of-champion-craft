#pragma once
#include "Ability.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "Tile.h"
class CUnit : public CGameObject
{
	int m_nHP;
	int m_nMaxHP;
	int m_nAttack;
	int m_nSpeed;
	int m_nTilesMoved;
	int m_nFacing; 
	int m_nUniqueID;
	int m_nPlayerID;
	int m_nRange;

	int m_nExpValue;

	Vec2D m_sGamePos;

	bool m_bHasAttacked;
	bool m_bShielded;
	bool m_bIsMoving;
	bool m_bIsFleeing;

	float m_fDodgeChance;


	UNIT_TYPE m_eType;

	std::vector<CAbility*> m_vAbilities;
	std::vector< CAbility* > m_vDebuffs;
	std::vector<CTile*> m_vWaypoints;
	
public:
	CUnit(UNIT_TYPE type);
	~CUnit(void);

	bool GetFleeing(void){ return m_bIsFleeing;}
	void SetFleeing(bool b) { m_bIsFleeing = b;}
	bool CheckDodged(void);
	float GetDodgeChance(void) { return m_fDodgeChance;}
	int GetNumWaypoints(void) { return m_vWaypoints.size();};
	Vec2D GetLastWaypoint(void) { return m_vWaypoints.front()->GetPosition();};

	int GetPortraitID(void);

	void AddWaypoint(CTile* pTile);

	void Update(float fElapsedTime);
	void Render(void);

	CAbility* GetAbility(int index);
	void PushDebuff(CAbility* debuff) { m_vDebuffs.push_back(debuff);}
	CAbility* GetDebuff(int i) { return m_vDebuffs[i];}
	int GetNumDebuffs(void) { return m_vDebuffs.size();}

	void SetPos(int posX, int posY);
	void SetPos(Vec2D pos);
	Vec2D GetPos(void) { return m_sGamePos;}



	void SetTilesMoved(int t) { m_nTilesMoved = t;}
	int GetTilesMoved(void) { return m_nTilesMoved;}

	void SetHP(int h) { m_nHP = h ;}
	int GetHP(void) { return m_nHP;}

	void SetMaxHP(int mh) { m_nMaxHP = mh;}
	int GetMaxHP(void) { return m_nMaxHP;}

	void SetAttack(int a) { m_nAttack = a;}
	int GetAttack(void) { return m_nAttack;}

	void SetSpeed(int s) { m_nSpeed = s;}
	int GetSpeed(void) { return m_nSpeed;}

	void SetRange(int r) { m_nRange = r;}
	int GetRange(void) { return m_nRange;}

	void SetEXPValue(int e) { m_nExpValue = e;}
	int GetEXPValue(void) { return m_nExpValue;}

	void SetFacing(int f) { m_nFacing = f;}
	int GetFacing(void) { return m_nFacing;}

	void SetUniqueID(int uID) { m_nUniqueID = uID;}
	int GetUniqueID(void) { return m_nUniqueID;}

	void SetPlayerID(int pID) {  m_nPlayerID = pID;}
	int GetPlayerID(void) { return m_nPlayerID;}

	void SetHasAttacked(bool b) { m_bHasAttacked = b;}
	bool GetHasAttacked(void) { return m_bHasAttacked;}

	void SetShielded(int b) {m_bShielded = (b == 0 ? false : true);}
	bool GetShielded(void) { return m_bShielded;}

	void SetIsMoving(bool b) { m_bIsMoving = b;}
	bool GetIsMoving(void) { return m_bIsMoving;}

	UNIT_TYPE GetType(void) { return m_eType;}
	UnitAnimation* m_sAnimStruct;
};

