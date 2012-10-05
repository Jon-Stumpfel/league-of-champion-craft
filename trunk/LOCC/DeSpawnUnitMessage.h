#pragma once
#include "imessage.h"

class DeSpawnUnitMessage : public IMessage
{

private:

	Vec2D m_sPos;
	int m_nPlayerID;

public:

	DeSpawnUnitMessage(void);
	DeSpawnUnitMessage( Vec2D sPos, int nPlayerID );
	~DeSpawnUnitMessage(void);

};