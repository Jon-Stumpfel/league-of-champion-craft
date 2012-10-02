#pragma once
#include "StdAfx.h"
#include "basemessage.h"
struct Vec2D
{
	int nPosX;
	int nPosY;
};
class SpawnUnitMessage :
	public BaseMessage
{
	enum UnitType{ARCHER, FOOTMAN, CALVARY, CHAMPION};
private:
	int playerID;
	Vec2D pos;
	UnitType type;
public:
	SpawnUnitMessage(void);
	~SpawnUnitMessage(void);
	SpawnUnitMessage(int posx, int posy, int playerID);
};

