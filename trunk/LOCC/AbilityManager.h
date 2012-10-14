#pragma once

#include "StdAfx.h"
#include "Ability.h"
#include "Unit.h"

#define NUMSPELLS 1;

class CAbilityManager
{
public:

	static CAbilityManager* GetInstance(void);
	static void DeleteInstance(void);	

	bool UseAbility(CAbility* pToUse, CTile* pTargetTile);	

	void LoadAbilities( void );

	void CastSpell( SPELL_TYPE );

	void Initialize(void);
	void Shutdown(void);

private:

	CAbilityManager(void);
	~CAbilityManager(void);
	CAbilityManager(const CAbilityManager&);
	CAbilityManager& operator=(const CAbilityManager&);

	static CAbilityManager* s_Instance;

	std::vector<std::pair<SPELL_TYPE, CAbility*>> m_vAbilities;
};

