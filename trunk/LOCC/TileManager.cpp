#include "StdAfx.h"
#include "TileManager.h"
#include "Unit.h"
#include "Tile.h"
#include "GraphicsManager.h"

CTileManager* CTileManager::s_Instance = nullptr;

CTileManager::CTileManager(void)
{
	m_pTileMap=nullptr;
	m_nTextureImageID=0;
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

bool CTileManager::LoadSave( std::string sFilename )
{
	TiXmlDocument doc;

	if( doc.LoadFile( sFilename.c_str() ) == false )
		return false;
	
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;

	int tempRows=0, tempCols=0;
	const char* texturefile;

	pRoot->Attribute("Rows",&tempRows);
	pRoot->Attribute("Columns", &tempCols);
	texturefile= pRoot->Attribute("FileName");

	TiXmlElement* pTiles = pRoot->FirstChildElement("Tiles");
	TiXmlElement* pTile = pRoot->FirstChildElement("Tile");

	for (int x = 0; x< tempRows; ++x)
	{
		m_pTileMap[x]= new CTile[tempCols];
	}

	for (int x=0; x<tempRows; ++x)
	{
		for(int y=0;y<tempCols;++y)
		{
			//pTile->Attribute("PosX",&m_pTileMap[x][y].m_sPos.nPosX);
			//pTile->Attribute("PosY",&m_pTileMap[x][y].m_sPos.nPosY);
		}
	}


	
	return true;
}

void CTileManager::Update( float fElapsedTime )
{

}

void CTileManager::Render( void )
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	
	//int x = (minimapWidth / 2 * i) - (minimapHeight / 2 * j);
	//int y = (minimapWidth / 2 * i) + (minimapHeight / 2 * j);
	//pTM->Draw(m_nTextureImageID, new Point(x + minimapOffsetX, y + minimapOffsetY));
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