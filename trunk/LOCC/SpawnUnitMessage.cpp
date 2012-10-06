#include "StdAfx.h"
#include "SpawnUnitMessage.h"



CSpawnUnitMessage::CSpawnUnitMessage(Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn) : CMessage(MSG_SPAWNUNIT)
{
	m_sPos = sPos;
	m_nPlayerID = nPlayerID;
	m_eType = eTypeToSpawn;
}

CSpawnUnitMessage::~CSpawnUnitMessage(void)
{
}
