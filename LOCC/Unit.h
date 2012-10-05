#pragma once
#include "StdAfx.h"
#include "Ability.h"
#include "GameObject.h"

class CTile;

enum UNIT_TYPE {  }; 

class CUnit : public CGameObject
{
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
	std::vector< CAbility* > m_vDebuffs;
	std::vector<CTile*> m_vWaypoints;

public:
	CUnit(void);
	~CUnit(void);

	CAbility* GetAbility(int index);
	
	void SetPos(int posX, int posY);
};

