#pragma once

#include "message.h"

class CAddResourceMessage : public CMessage
{
private:

	TILE_TYPE m_eTile;
	int m_nPlayerID;

public:
	TILE_TYPE GetTileType(void) { return m_eTile;}
	int GetPlayerID(void) { return m_nPlayerID;}
	CAddResourceMessage(TILE_TYPE eTile, int nPlayerID);
	~CAddResourceMessage(void);
};

