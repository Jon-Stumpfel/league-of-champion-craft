#include "StdAfx.h"
#include "TileManager.h"
#include "Unit.h"
#include "Tile.h"

CTileManager* CTileManager::s_Instance = nullptr;

CTileManager::CTileManager(void)
{

}


CTileManager::~CTileManager(void)
{

}

CTileManager* CTileManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CTileManager;

	return s_Instance;
}

void CTileManager::LoadSave( std::string sFilename )
{

}

void CTileManager::Update( float fElapsedTime )
{

}

void CTileManager::Render( void )
{
	//int x = (minimapWidth / 2 * i) - (minimapHeight / 2 * j);
 //   int y = (minimapWidth / 2 * i) + (minimapHeight / 2 * j);
 //   e.Graphics.DrawImage(tileImg, new Point(x + minimapOffsetX, y + minimapOffsetY));
}

CTile* CTileManager::GetTile( int x, int y )
{
	return nullptr;
}

CUnit* CTileManager::GetUnit( int x, int y )
{
	return nullptr;
}

CUnit* CTileManager::GetUnit( CTile* Tile )
{
	return nullptr;
}