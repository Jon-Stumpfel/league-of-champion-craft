#pragma once

#include "StdAfx.h"
#include "Ability.h"

class CAbilityManager
{
	static CAbilityManager* GetInstance(void);
	static void DeleteInstance(void);	

	bool UseAbility(CAbility* pToUse, CTile* pTargetTile);	

	void Execute(CAbility* pToUse);
	void Execute(CAbility* pToUse, CUnit* pTargetUnit);
	void Execute(CAbility* pToUse, CTile* pTile);

	void Initialize(void);
	void Shutdown(void);
private:
	CAbilityManager(void);
	~CAbilityManager(void);
	CAbilityManager(const CAbilityManager&);
	CAbilityManager& operator=(const CAbilityManager&);

	static CAbilityManager* s_Instance;

	std::vector<CAbility> m_vAbilities;
	lua_State* m_pLuaState;


};

