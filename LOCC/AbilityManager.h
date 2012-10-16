#pragma once

#include "StdAfx.h"
#include "Ability.h"
#include "Unit.h"

#define NUMSPELLS 2;

class CAbilityManager
{
public:

	static CAbilityManager* GetInstance(void);
	static void DeleteInstance(void);	

	void UseAbility(CAbility* pToUse, CTile* pTargetTile, CUnit* pCaster);	
	void LoadAbilities( void );
	CAbility* GetAbility( SPELL_TYPE type );

	std::vector< Vec2D > GetRange( int range );

	std::vector< Vec2D > GetProperFacing( int face, CAbility* pAbility, CTile* pTile );

	void Initialize(void);
	void Shutdown(void);

private:

	CAbilityManager(void);
	~CAbilityManager(void);
	CAbilityManager(const CAbilityManager&);
	CAbilityManager& operator=(const CAbilityManager&);

	void SetRanges( void );

	static CAbilityManager* s_Instance;

	std::vector<std::pair<SPELL_TYPE, CAbility*>> m_vAbilities;
	std::vector< Vec2D > m_vRange1;	
	std::vector< Vec2D > m_vRange2;
	std::vector< Vec2D > m_vRange3;
	std::vector< Vec2D > m_vRange4;

};

