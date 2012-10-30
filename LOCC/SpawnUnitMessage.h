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
	std::vector<std::pair<SPELL_TYPE, int>> m_vSpells;
	std::vector<SPELL_TYPE> m_vEffects;
	std::vector<SPELL_TYPE> m_vBought;

public:

	SPELL_TYPE GetSpells(int i) { return m_vSpells[i].first; }
	int GetCooldown(int i) { return m_vSpells[i].second; }
	int GetSpellSize( void ) { return m_vSpells.size(); }
	std::vector<SPELL_TYPE> GetEffects(void) { return m_vEffects;}
	std::vector<SPELL_TYPE> GetBought(void) { return m_vBought; }
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
	CSpawnUnitMessage(std::vector<std::pair<SPELL_TYPE, int>> spells, std::vector<SPELL_TYPE> effects, Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded = false, 
		int nHealth = 0, int nTilesMoved = 0, bool bHasAttacked = false);
	CSpawnUnitMessage(std::vector<std::pair<SPELL_TYPE, int>> spells, std::vector<SPELL_TYPE> effects, std::vector<SPELL_TYPE> bought, Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded = false, 
		int nHealth = 0, int nTilesMoved = 0, bool bHasAttacked = false);
};

