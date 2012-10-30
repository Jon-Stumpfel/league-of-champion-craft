#include "StdAfx.h"
#include "Player.h"
#include "GameManager.h"

CPlayer::CPlayer(int nPlayerID)
{
	m_nPlayerID = nPlayerID;
	SetAP(nStartingAP);
	SetMetal(20);
	SetWood(20);
	SetPopCap(0);
	SetMaxPopCap(12);
	SetExp(1100);

	m_nMillsOwned = 0;
	m_nMinesOwned = 0;
	// STATS RECORDING
	m_tStats.nChampionDamageDone	 = 0;
	m_tStats.nChampionHealingDone	 = 0;
	m_tStats.nPlayerEXPEarned		 = 0;
	m_tStats.nPlayerWoodEarned		 = 0;
	m_tStats.nPlayerMetalEarned		 = 0;
	m_tStats.nPlayerWoodSpent		 = 0;
	m_tStats.nPlayerMetalSpent		 = 0;
	m_tStats.nPlayerAPSpent			 = 0;
	m_tStats.nSwordsmanCreated		 = 0;	
	m_tStats.nArcherCreated			 = 0;
	m_tStats.nCalvaryCreated		 = 0;
	m_tStats.nSwordsmanDamageDone	 = 0;
	m_tStats.nArcherDamageDone		 = 0;
	m_tStats.nCalvaryDamageDone		 = 0;
	m_tStats.nSwordsmanKilled		 = 0;
	m_tStats.nArcherKilled			 = 0;
	m_tStats.nCavalryKilled			 = 0;
}


CPlayer::~CPlayer(void)
{
}


int CPlayer::GetMillsOwned(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer(CGameManager::GetInstance()->GetUnitByID(nUnitID)->GetPlayerID());

	lua_pushinteger(L, pPlayer->GetMillsOwned());

	return 1;
}

int CPlayer::GetMinesOwned(lua_State* L)
{
	int nUnitID = lua_tointeger(L, 1);

	CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer(CGameManager::GetInstance()->GetUnitByID(nUnitID)->GetPlayerID());

	lua_pushinteger(L, pPlayer->GetMinesOwned());

	return 1;
}