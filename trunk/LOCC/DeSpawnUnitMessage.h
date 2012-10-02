#pragma once
#include "basemessage.h"
struct Vec2D
{
	int nPosX;
	int nPosY;
};
class DeSpawnUnitMessage :
	public BaseMessage
{
private:
	Vec2D pos;
public:
	DeSpawnUnitMessage(void);
	DeSpawnUnitMessage(Vec2D pos);
	~DeSpawnUnitMessage(void);
};

