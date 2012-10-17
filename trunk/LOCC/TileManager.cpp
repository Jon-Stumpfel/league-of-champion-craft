#include "StdAfx.h"
#include "TileManager.h"
#include "Unit.h"
#include "Tile.h"
#include "GraphicsManager.h"
#include "GameplayState.h"
#include "GameManager.h"
#include "ObjectManager.h"
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
void CTileManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->ShutDown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CTileManager::ShutDown(void)
{

	for (int  x = 0; x < m_nRows; ++x)
	{
		delete[] m_pTileMap[x];
	}
	delete[] m_pTileMap;
	//for (int x = 0; x<m_nRows; ++x)
	//{
	//	for (int y=0; y<m_nColumns;++y)
	//	{
	//		delete [] m_pTileMap[y];
	//	}
	//	delete[] m_pTileMap[x];
	//}	

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
	TiXmlElement* pTile = pTiles->FirstChild("Tile")->ToElement();

	// KBV
	m_nRows = m_ucRows;
	m_nColumns = m_ucColumns;

	m_pTileMap= new CTile*[m_ucRows];

	for (int x = 0; x< m_nRows; ++x)
	{
		m_pTileMap[x]= new CTile[m_nColumns];
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
			SetTileWidth(tempdata1);

			pTile->Attribute("PixHeight",&tempdata1);
			m_pTileMap[x][y].SetPixHeight(tempdata1);
			SetTileHieght(tempdata1);

			/*pTile->Attribute("TileWidth",&tempdata1);
			m_pTileMap[x][y].SetTileWidth(tempdata1);

			pTile->Attribute("TileHeight",&tempdata1);
			m_pTileMap[x][y].SetTileHeight(tempdata1);*/

			pTile->Attribute("Status",&tempdata1);
			m_pTileMap[x][y].SetStatus(tempdata1);

			pTile->Attribute("PlayerID",&tempdata1);
			m_pTileMap[x][y].SetPlayerID(tempdata1);

			pTile->Attribute("TType",&tempdata1);
			m_pTileMap[x][y].SetTileType(tempdata1);

			pTile = pTile->NextSiblingElement("Tile");
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

	int TWidth=m_pTileMap[0][0].GetPixWidth(),
		THeight=m_pTileMap[0][0].GetPixHeight();
	
			THeight += 27;
			TWidth += 26;
	for ( int i=0; i<m_nRows;i++)
	{
		for ( int j=0; j<m_nColumns;j++)
		{
			int camX = CGameplayState::GetInstance()->GetCamOffsetX();
			int camY = CGameplayState::GetInstance()->GetCamOffsetY();

            int x = (TWidth / 2 * i) - (THeight / 2 * j);
            int y = (TWidth / 2 * i) + (THeight  / 2 * j);

			// Tile culling
			if (x > camX + 790)
				continue;
			if (x < camX - 90)
				continue;
			if (y > camY + 500)
				continue;
			if (y < camY - 90)
				continue;

			RECT Rsource= { 0,0,0,0}; 

			float fRad = (float(45 * 3.14159286 / 180));
			switch(m_pTileMap[i][j].GetTileType())
			{	
			case TT_PLAINS:
				{
					Rsource = CellAlgorithm(TT_PLAINS);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_FOREST:
				{
					Rsource = CellAlgorithm(TT_FOREST);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y- CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_MOUNTAINS:
				{
					Rsource = CellAlgorithm(TT_MOUNTAINS);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_WATER:
				{
					Rsource = CellAlgorithm(TT_WATER);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y  - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_FARM:
				{
					Rsource = CellAlgorithm(TT_FARM);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_MILL:
				{
					Rsource = CellAlgorithm(TT_MILL);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_MINE:
				{
					Rsource = CellAlgorithm(TT_MINE);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y  - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			case TT_CASTLE:
				{
					Rsource = CellAlgorithm(TT_CASTLE);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				}
				break;
			}
		}
	}
}

CTile* CTileManager::GetTile( int x, int y )
{
	if (x>=m_nRows || y>=m_nColumns)
		return nullptr;
	if (x<0 || y<0)
		return nullptr;

	return &m_pTileMap[x][y];
}

CUnit* CTileManager::GetUnit( int x, int y )
{
	if (x>=m_nRows || y>=m_nColumns)
		return nullptr;
	if (x<0 || y<0)
		return nullptr;

	if (m_pTileMap[x][y].GetIfOccupied())
		return nullptr;

	return nullptr;
}

CUnit* CTileManager::GetUnit( CTile* Tile )
{
	return nullptr;
}