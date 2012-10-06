#pragma once

enum TILE_TYPE		{ PLAINS, FOREST, MOUNTAINS, FARM, MILL, MINE, WATER };
enum TILE_STATUS	{ FROZEN, RESOURCETILE, OCCUPIED, CAPTURING, CAPTURED, IS_DEAD, ISPASSABLE};

class CTile
{
public:

	CTile(void);
	CTile( int eTile, bool bResouceTile, Vec2D sPos );
	~CTile(void);
	
	void SetStatus	( unsigned char TileStatus, bool On_or_Off);
	bool IsStatus	( unsigned char TileStatus, bool On_or_Off);
	
	void GetIfFrozen	(void);
	bool SetIfFrozen	(bool OnOff);

	void GetIfResoruce	(void);
	bool SetIfResoruce	(bool OnOff);

	void GetIfOccupied	(void);
	bool SetIfOccupied	(bool OnOff);

	void GetIfCaputring	(void);
	bool SetIfCaputring	(bool OnOff);

	

private:

	int					m_eTType;
	unsigned char		m_ucStatus;
	int					m_nPlayerID;
	Vec2D				m_sPos;
	unsigned int		m_pixWidth;
	unsigned int		m_pixHieght;
};

