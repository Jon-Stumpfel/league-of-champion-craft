#pragma once

#include "StdAfx.h"

class CTile;

class CTileManager
{

public:

	CTileManager( void );
	~CTileManager( void );
	void LoadSave( std::string sFilename );
	void Update( float fElapsedTime );
	void Render( void );
	CTile* GetTile( int x, int y );
	CUnit* GetUnit( int x, int y );
	CUnit* GetUnit( CTile* pTile );

private:

	CTile* m_pTileMap;

};

