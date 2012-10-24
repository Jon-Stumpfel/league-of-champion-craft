
#pragma once

class CTile
{
public:

	CTile(void);
	CTile( int eTile, bool bResouceTile, Vec2D sPos );
	~CTile(void);
	
	void	SetStatus	( unsigned char TileStatus, bool On_or_Off);
	bool	IsStatus	( unsigned char TileStatus, bool On_or_Off);
	
	bool	GetIfFrozen			(void);
	void	SetIfFrozen			(bool OnOff);

	bool	GetIfOccupied		(void);
	void	SetIfOccupied		(bool OnOff);

	bool	GetIfCapturing		(void);
	void	SetIfCapturing		(bool OnOff);
											
	bool	GetIfCaptured		(void);
	void	SetIfCaptured		(bool OnOff);

	bool	GetIfResourceTile	(void);
	void	SetIfResourceTile	(bool OnOff);

	bool	GetIfDeadTile		(void);
	void	SetIfDeadTile		(bool OnOff);

	bool	GetIfPassable		(void);
	void	SetIfPassable		(bool OnOff);

	int		GetAPCost			(void );

	int		GetTileType			(void)				{return m_eTType;};
	void	SetTileType			(int eTileType)		{m_eTType=eTileType;};

	int		GetPlayerID			(void)				{return m_nPlayerID;};	
	void	SetPlayerID			(int nPlayerID)		{m_nPlayerID=nPlayerID;};

	Vec2D	GetPosition			(void)				{return m_sPos;};
	void	SetPosition			(Vec2D sPos)		{m_sPos=sPos;};
	void 	SetPosition			(int X, int Y)		{m_sPos.nPosX=X; m_sPos.nPosY=Y;};

	int		GetPixWidth			(void)				{return m_nPixWidth;};	
	void	SetPixWidth			(int nPixWidth)		{m_nPixWidth=nPixWidth;};

	int		GetPixHeight		(void)				{return m_nPixHeight;};	
	void	SetPixHeight		(int nPixHeight)	{m_nPixHeight=nPixHeight;};

	int		GetTileWidth		(void)				{return m_nTileWidth;};	
	void	SetTileWidth		(int nTileWidth)	{m_nTileWidth=nTileWidth;};

	int		GetTileHeight		(void)				{return m_nTileHeight;};		
	void	SetTileHeight		(int nTileHeight)	{m_nTileHeight=nTileHeight;};

	// **USED TO LOAD FROM FILE; NOT TO BE PLAYED WITH**!!!
	void  SetStatus        (unsigned char ucStatus )		{m_ucStatus=ucStatus;};

	bool operator==(const CTile& rhs);
private:
	int					m_eTType;
	unsigned char		m_ucStatus;
	//quick view of status
	//TS_FROZEN			=1
	//TS_RESOURCETILE	=2
	//TS_OCCUPIED		=8
	//TS_CAPTURED		=16
	//TS_IS_DEAD		=32
	//TS_ISPASSABLE		=64
	//

	int					m_nPlayerID;
	Vec2D				m_sPos;
	int					m_nPixWidth;
	int					m_nPixHeight;
	int					m_nTileWidth;
	int					m_nTileHeight;

};

