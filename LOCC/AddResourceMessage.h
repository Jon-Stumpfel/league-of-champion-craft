#pragma once

#include "imessage.h"

class AddResourceMessage : public IMessage
{
	enum TileType{};

private:

	TileType m_eTile;
	int m_nPlayerID;

public:

	AddResourceMessage(void);
	AddResourceMessage(TileType eTile, int nPlayerID);
	~AddResourceMessage(void);
};

