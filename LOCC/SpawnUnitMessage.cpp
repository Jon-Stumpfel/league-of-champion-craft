#include "StdAfx.h"
#include "SpawnUnitMessage.h"



CSpawnUnitMessage::CSpawnUnitMessage(Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded, 
		int nHealth, int nTilesMoved, bool bHasAttacked) : CMessage(MSG_SPAWNUNIT)
{
	m_sPos = sPos;
	m_nPlayerID = nPlayerID;
	m_eType = eTypeToSpawn;
	m_nFacing = nFacing;
	m_nHealth = nHealth;
	m_bLoaded = Loaded;
	m_bHasAttacked = bHasAttacked;
	m_nTilesMoved = nTilesMoved;
}
CSpawnUnitMessage::CSpawnUnitMessage(std::vector<SPELL_TYPE> spells, std::vector<SPELL_TYPE> effects, std::vector<SPELL_TYPE> bought, Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded, 
		int nHealth, int nTilesMoved, bool bHasAttacked) : CMessage(MSG_SPAWNUNIT)
{
	m_sPos = sPos;
	m_nPlayerID = nPlayerID;
	m_eType = eTypeToSpawn;
	m_nFacing = nFacing;
	m_nHealth = nHealth;
	m_bLoaded = Loaded;
	m_bHasAttacked = bHasAttacked;
	m_nTilesMoved = nTilesMoved;
	m_vSpells = spells;
	m_vEffects = effects;
	m_vBought = bought;
}

CSpawnUnitMessage::CSpawnUnitMessage(std::vector<SPELL_TYPE> spells, std::vector<SPELL_TYPE> effects, Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing, bool Loaded, 
		int nHealth, int nTilesMoved, bool bHasAttacked) : CMessage(MSG_SPAWNUNIT)
{
	m_sPos = sPos;
	m_nPlayerID = nPlayerID;
	m_eType = eTypeToSpawn;
	m_nFacing = nFacing;
	m_nHealth = nHealth;
	m_bLoaded = Loaded;
	m_bHasAttacked = bHasAttacked;
	m_nTilesMoved = nTilesMoved;
	m_vSpells = spells;
	m_vEffects = effects;
}

CSpawnUnitMessage::~CSpawnUnitMessage(void)
{
}
