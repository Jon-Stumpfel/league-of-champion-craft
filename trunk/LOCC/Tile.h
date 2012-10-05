#pragma once

enum TILE_TYPE { PLAINS, FOREST, MOUNTAINS, FARM, MILL, MINE, WATER };

class CTile
{
public:

	CTile(void);
	CTile( TILE_TYPE eTile, bool bResouceTile );
	~CTile(void);

private:

	char m_cStatus;
	int m_nPlayerID;
	Vec2D m_sPos;

};

