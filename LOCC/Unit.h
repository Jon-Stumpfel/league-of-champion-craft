#pragma once
#include "StdAfx.h"
#include "gameobject.h"
#include "Ability.h"
class CTile;
class CUnit : public CGameObject
{
	enum UNIT_TYPE { };

	int m_nHP;
	int m_nAttack;
	int m_nSpeed;
	int m_nFacing; 
	int m_nUniqueID;
	int m_nPlayerID;

	Vec2D m_sGamePos;

	bool m_bHasAttacked;
	bool m_bShielded;
	bool m_bIsMoving;

	UNIT_TYPE m_eType;

	std::vector<CAbility*> m_vAbilities;
	std::vector<CTile*> m_vWaypoints;
public:
	CUnit(void);
	~CUnit(void);

	CAbility* GetAbility(int index);
	
	void SetPos(int posX, int posY);
};

