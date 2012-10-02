#pragma once
#include "basemessage.h"
class AddResourceMessage :
	public BaseMessage
{
	enum TileType{};
private:
	TileType tile;
	int playerID;
public:
	AddResourceMessage(void);
	AddResourceMessage(TileType tile, int playerID);
	~AddResourceMessage(void);
};

