#pragma once


class CTile;
class CUnit;

class CTileManager
{

public:
	void Init();
	void ShutDown();
	bool LoadSave( std::string sFilename );
	void Update( float fElapsedTime );
	void Render( void );
	CTile* GetTile( int x, int y );
	CUnit* GetUnit( int x, int y );
	CUnit* GetUnit( CTile* pTile );

	static CTileManager* GetInstance( void );
	static void DeleteInstance(void);

	int GetNumRows (void)		{return m_nRows;};
	int GetNumColumns (void)	{return m_nColumns;};
	void EvaluateResources( int nPlayerID);

	static int GetSelectedTile(lua_State* L);
	static int DestroyForest(lua_State* L);
	static int RaiseMountain(lua_State* L);
private:

	RECT CTileManager::CellAlgorithm( int id )
	{
		assert( id >= 0 && id < m_nColumns * m_nRows && "CellAlgorithm - id out of range!" );

		// quick fix for rendering the wrong tiles
		//if (id == 1)
		//	id = 2;
		//else if (id == 2)
		//	id = 1;
		RECT rSource;

		rSource.left	= (id % 4) * m_nTileWidth;
		rSource.top		= (id / 4) * m_nTileHeight;

		rSource.right	= rSource.left	+ m_nTileWidth;
		rSource.bottom	= rSource.top	+ m_nTileHeight;

		return rSource;

	}
	RECT CTileManager::GetFlag( int id )
	{
		RECT flag;
	switch(id)
	{
		case F_RED_CAPTURED:
		{
			flag.top=0;
			flag.left=0;
			flag.right=64;
			flag.bottom=64;
			return flag;
		}
		case F_RED_CAPTURING:
		{
			flag.top=64;
			flag.left=0;
			flag.right=64;
			flag.bottom=128;
			return flag;
		}
		case F_BLUE_CAPTURED:
		{
			flag.top=0;
			flag.left=64;
			flag.right=128;
			flag.bottom=64;
			return flag;
		}
		case F_BLUE_CAPTURING:
		{
			flag.top=64;
			flag.left=64;
			flag.right=128;
			flag.bottom=128;
			return flag;
		}
		default:
		{
			flag.top=0;
			flag.left=0;
			flag.right=0;
			flag.bottom=0;
			return flag;
		}
	}

	}
	void SetTileWidth(int wTile)	{m_nTileWidth=wTile; };
	void SetTileHieght(int HTile)	{m_nTileHeight=HTile;};

	CTileManager(void);
	~CTileManager(void);
	CTileManager(const CTileManager&);
	CTileManager& operator=(const CTileManager&);

	static CTileManager* s_Instance;

	int	m_nTextureImageID;
	int	m_nFrozenTextureImageID;
	int m_nFlagID;
	CTile**	m_pTileMap;
	int m_nRows;
	int m_nColumns;

	int m_nTileWidth;
	int m_nTileHeight;

};

