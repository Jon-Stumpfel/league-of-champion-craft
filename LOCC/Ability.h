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

	int GetApCost( void ) const { return m_nAPCost; }
	int GetCoolDown( void ) const { return m_nCooldown; }
	int GetRange( void ) const { return m_nRange; }
	int GetTargets( void ) const { return m_nNumTargets; }
	GAME_PHASE GetPhase( void ) const { return m_nPhase; }
	TSTRING GetIcon( void ) const { return m_szInterfaceIcon; }
	bool GetIfAttack( void ) const { return m_bIsAttack; }
	bool GetIfMove( void ) const { return m_bIsMove; }
	std::vector< Vec2D > GetPattern( void ) const { return m_vPattern; }
	std::string GetName( void ) const { return m_strName; }
	std::string GetLua( void ) const { return m_strLuaFile; }
	std::string GetParticle( void ) const { return m_strParticleFile; }

	void SetIcon( TSTRING icon ) { m_szInterfaceIcon = icon; }
	void SetIsMove( bool bMove ) { m_bIsMove = bMove; }
};

