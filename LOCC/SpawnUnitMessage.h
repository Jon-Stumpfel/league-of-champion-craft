#pragma once

#include "Message.h"
#include "Unit.h"

class CSpawnUnitMessage : public CMessage
{

private:

	int m_nPlayerID;
	Vec2D m_sPos;
	UNIT_TYPE m_eType;
	int m_nFacing;
	bool m_bLoaded;
	bool m_bHasAttacked;
	int m_nTilesMoved;
	int m_nHealth;
	std::vector<SPELL_TYPE> m_vSpells;
public:

	std::vector<SPELL_TYPE> GetSpells(void) { return m_vSpells;}
	int GetPlayerID(void) { return m_nPlayerID;}
	Vec2D GetPos(void) { return m_sPos;}
	UNIT_TYPE GetUnitType(void) { return m_eType;}
	int GetFacing(void) { return m_nFacing;}
	int GetHealth(void) { return m_nHealth;}
	bool GetLoaded(void) { return m_bLoaded;}
	bool GetHasAttacked(void) { return m_bHasAttacked;}
	int GetTilesMoved(void) { return m_nTilesMoved;}
	~CSpawnUnitMessage(void);
	CSpawnUnitMessage(Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded = false, 
		int nHealth = 0, int nTilesMoved = 0, bool bHasAttacked = false);
	CSpawnUnitMessage(std::vector<SPELL_TYPE> spells, Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded = false, 
		int nHealth = 0, int nTilesMoved = 0, bool bHasAttacked = false);

};

