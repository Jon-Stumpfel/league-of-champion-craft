#pragma once

#include "StdAfx.h"

class CTile;
class CUnit;

class CTileManager
{

public:

	bool LoadSave( std::string sFilename );
	void Update( float fElapsedTime );
	void Render( void );
	CTile* GetTile( int x, int y );
	CUnit* GetUnit( int x, int y );
	CUnit* GetUnit( CTile* pTile );

	static CTileManager* GetInstance( void );

private:
	
	CTileManager(void);
	~CTileManager(void);
	CTileManager(const CTileManager&);
	CTileManager& operator=(const CTileManager&);

	static CTileManager* s_Instance;

	int	m_nTextureImageID;
	CTile**	m_pTileMap;
	int m_nRows;
	int m_nColumns;
};
