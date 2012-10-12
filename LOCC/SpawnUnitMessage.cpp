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

CSpawnUnitMessage::~CSpawnUnitMessage(void)
{
}
