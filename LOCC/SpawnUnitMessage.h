#pragma once

#include "StdAfx.h"
#include "Message.h"
#include "Unit.h"

class CSpawnUnitMessage : public CMessage
{

private:

	int m_nPlayerID;
	Vec2D m_sPos;
	UNIT_TYPE m_eType;

public:

	int GetPlayerID(void) { return m_nPlayerID;}
	Vec2D GetPos(void) { return m_sPos;}
	UNIT_TYPE GetUnitType(void) { return m_eType;}

	~CSpawnUnitMessage(void);
	CSpawnUnitMessage(Vec2D sPos, int nPlayerID, UNIT_TYPE eTypeToSpawn);

};

