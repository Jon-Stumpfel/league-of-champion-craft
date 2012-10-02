#pragma once

#include "GameObject.h"

enum TileType { PLAINS, FOREST, MOUNTAINS, FARM, MILL, MINE, WATER };

class CTile
{
public:

	CTile(void);
	CTile( TileType eTile, bool bResouceTile );
	~CTile(void);

private:

	char m_cStatus;
	int m_nPlayerID;
	Vec2D m_sPos;

};

