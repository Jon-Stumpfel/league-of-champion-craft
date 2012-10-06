#pragma once

#include "message.h"

class CAddResourceMessage : public CMessage
{
private:

	TILE_TYPE m_eTile;
	int m_nPlayerID;

public:

	CAddResourceMessage(TILE_TYPE eTile, int nPlayerID);
	~CAddResourceMessage(void);
};

