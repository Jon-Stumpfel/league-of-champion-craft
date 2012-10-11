#include "StdAfx.h"
#include "SpawnUnitMessage.h"



CSpawnUnitMessage::CSpawnUnitMessage(Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn, int nFacing) : CMessage(MSG_SPAWNUNIT)
{
	m_sPos = sPos;
	m_nPlayerID = nPlayerID;
	m_eType = eTypeToSpawn;
	m_nFacing = nFacing;
}

CSpawnUnitMessage::~CSpawnUnitMessage(void)
{
}
