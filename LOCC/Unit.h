#pragma once
#include "StdAfx.h"
#include "Ability.h"
#include "GameObject.h"


struct UnitAnimation
{
	UNIT_TYPE unitType;
	ANIM_TYPE animationType;
	int nCurrentFrame;
	float fCurrentTime;
};
class CUnit : public CGameObject
{
	int m_nHP;
	int m_nAttack;
	int m_nSpeed;
	int m_nFacing; 
	int m_nUniqueID;
	int m_nPlayerID;
	int m_nRange;

	int m_nExpValue;

	Vec2D m_sGamePos;

	bool m_bHasAttacked;
	bool m_bShielded;
	bool m_bIsMoving;

	UNIT_TYPE m_eType;

	std::vector<CAbility*> m_vAbilities;
	std::vector< CAbility* > m_vDebuffs;
	std::vector<CTile*> m_vWaypoints;

	UnitAnimation* m_pMyAnimation;

public:
	CUnit(UNIT_TYPE type);
	~CUnit(void);

	void Update(float fElapsedTime);
	void Render(void);

	CAbility* GetAbility(int index) { return m_vAbilities[index];}
	
	void SetPos(int posX, int posY) { m_sGamePos.nPosX = posX; m_sGamePos.nPosY = posY;}
	void SetPos(Vec2D pos) { m_sGamePos = pos;}
	Vec2D GetPos(void) { return m_sGamePos;}

	void SetHP(int h) { m_nHP = h ;}
	int GetHP(void) { return m_nHP;}

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

	void SetShielded(bool b) {m_bShielded = b;}
	bool GetShielded(void) { return m_bShielded;}

	void SetIsMoving(bool b) { m_bIsMoving = b;}
	bool GetIsMoving(void) { return m_bIsMoving;}

	UNIT_TYPE GetType(void) { return m_eType;}
};

