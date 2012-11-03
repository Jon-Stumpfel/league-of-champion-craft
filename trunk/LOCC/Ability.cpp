#include "StdAfx.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "GameplayState.h"

CAbility::CAbility(void)
{
	m_szInterfaceIcon = TSTRING(_T("lol"));
}


CAbility::~CAbility(void)
{
}

int CAbility::GetAbilityPattern( lua_State* L )
{
	lua_newtable(L);
	int nCount = 0;
	vector< Vec2D > pat = CAbilityManager::GetInstance()->GetAbility(SP_MASSRAISE)->GetPattern();
	CUnit* tmp = CGameplayState::GetInstance()->GetSelectedUnit();
	for( unsigned int i = 0; i < pat.size(); i++ )
	{
		lua_newtable(L);
		lua_pushstring(L, "posX");
		lua_pushnumber(L, tmp->GetPos().nPosX + pat[i].nPosX);
		lua_settable(L, -3);
		lua_pushstring(L, "posY");
		lua_pushnumber(L, tmp->GetPos().nPosY + pat[i].nPosY);
		lua_settable(L, -3);
		lua_pushnumber(L, nCount+1);
		nCount++;
		lua_insert(L, -2);
		lua_settable(L, -3);
	}

	lua_setglobal(L, "tPattern");
	return pat.size();
}

CAbility::CAbility(vector<Vec2D> vPattern, int nAP, int nCD, int nRange,
				int nTarget, GAME_PHASE Phase, bool bAttack, string luaFile, string particleFile, string name, int ID)
{
	m_vPattern = vPattern;
	m_nAPCost = nAP;
	m_nCooldown = nCD;
	m_nRange = nRange;
	m_nNumTargets = nTarget;
	m_nPhase = Phase;
	m_bIsAttack = bAttack;
	m_strLuaFile = luaFile;
	m_strParticleFile = particleFile;
	m_strName = name;
	m_nIconID = ID;
}
