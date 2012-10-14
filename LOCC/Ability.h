#pragma once
#include "StdAfx.h"

class CTile;

class CAbility
{

private:
public:
	std::string m_strLuaFile;
	std::string m_strParticleFile;
	std::string m_strName;

	std::vector< Vec2D > m_vPattern;

	int m_nAPCost;
	int m_nCooldown;
	int m_nRange;
	int m_nNumTargets;
	GAME_PHASE m_nPhase;

	TSTRING m_szInterfaceIcon;

	bool m_bIsAttack;
	bool m_bIsMove; // SPECIFICALLY if this is the Move "spell"

public:

	CAbility(void);
	CAbility(vector<Vec2D> vPattern, int nAP, int nCD, int nRange,
				int nTarget, GAME_PHASE Phase, bool bAttack, string luaFile, string particleFile, string name);
	~CAbility(void);

};

