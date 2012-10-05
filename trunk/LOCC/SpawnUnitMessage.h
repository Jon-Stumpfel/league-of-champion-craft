#pragma once

#include "StdAfx.h"
#include "imessage.h"
#include "Unit.h"

class SpawnUnitMessage : public IMessage
{

private:

	int m_nPlayerID;
	Vec2D m_sPos;
	UNIT_TYPE eType;

public:

	SpawnUnitMessage(void);
	~SpawnUnitMessage(void);
	SpawnUnitMessage(Vec2D sPos, int nPlayerID);

};

