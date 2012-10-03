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