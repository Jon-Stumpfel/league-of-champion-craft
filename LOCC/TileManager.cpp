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
	TiXmlElement* pTile = pTiles->FirstChildElement("Tile");

	m_pTileMap= new CTile*[tempRows];

	for (int x = 0; x< tempRows; ++x)
	{
		m_pTileMap[x]= new CTile[tempCols];
	}
	int tempdata1=0,tempdata2=0;

	for (int x=0; x<tempRows; ++x)
	{
		for(int y=0;y<tempCols;++y)
		{
			pTile->Attribute("PosX",&tempdata1);
			pTile->Attribute("PosY",&tempdata2);
			m_pTileMap[x][y].SetPosition(tempdata1,tempdata2);
			
			pTile->Attribute("PixWidth",&tempdata1);
			m_pTileMap[x][y].SetPixWidth(tempdata1);

			pTile->Attribute("PixHeight",&tempdata1);
			m_pTileMap[x][y].SetPixHeight(tempdata1);
			
			pTile->Attribute("TileWidth",&tempdata1);
			m_pTileMap[x][y].SetTileWidth(tempdata1);

			pTile->Attribute("TileHeight",&tempdata1);
			m_pTileMap[x][y].SetTileHeight(tempdata1);

			pTile->Attribute("Status",&tempdata1);
			m_pTileMap[x][y].SetStatus(tempdata1);

			pTile->Attribute("PlayerID",&tempdata1);
			m_pTileMap[x][y].SetPlayerID(tempdata1);

			pTile->Attribute("TType",&tempdata1);
			m_pTileMap[x][y].SetTileType(tempdata1);
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