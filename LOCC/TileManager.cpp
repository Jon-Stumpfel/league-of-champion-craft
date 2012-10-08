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

	int m_ucRows=0, m_ucColumns=0;
	string texturefile;
	TSTRING _TStupid_textconversion;

	pRoot->Attribute("Rows",&m_ucRows);
	pRoot->Attribute("Columns", &m_ucColumns);
	texturefile= pRoot->Attribute("FileName");

	_TStupid_textconversion.resize(texturefile.length());
	for (unsigned int i=0; i<_TStupid_textconversion.length(); ++i)
	{
		_TStupid_textconversion[i]=texturefile[i];
	}

	CGraphicsManager::GetInstance()->LoadImageW(_TStupid_textconversion,_T("GrassTile"),D3DCOLOR_XRGB(0,0,0));
	m_nTextureImageID= CGraphicsManager::GetInstance()->GetID(_T("GrassTile"));

	TiXmlElement* pTiles = pRoot->FirstChildElement("Tiles");
	TiXmlElement* pTile = pTiles->FirstChildElement("Tile");

	m_pTileMap= new CTile*[m_ucRows];

	for (int x = 0; x< m_ucRows; ++x)
	{
		m_pTileMap[x]= new CTile[m_ucColumns];
	}
	int tempdata1=0,tempdata2=0;

	for (int x=0; x<m_ucRows; ++x)
	{
		for(int y=0;y<m_ucColumns;++y)
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
	CSGD_TextureManager* pTM=CSGD_TextureManager::GetInstance();

	int TWidth=m_pTileMap[0][0].GetTileWidth(),
		THeight=m_pTileMap[0][0].GetTileHeight();
	
		m_ucRows=2;m_ucColumns=5;

	for ( int i=0; i<m_ucRows;i++)
	{
		for ( int j=0; j<m_ucRows;j++)
		{
			int x = (j * TWidth / 2) + (i * TWidth / 2);
			int y = (i * THeight / 2) - (j * THeight / 2);
			pTM->Draw(m_nTextureImageID,x,y); 
            
										
		}
	}
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