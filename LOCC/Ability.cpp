#include "StdAfx.h"
#include "Ability.h"


CAbility::CAbility(void)
{
	m_szInterfaceIcon = TSTRING(_T("lol"));
}


CAbility::~CAbility(void)
{
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
