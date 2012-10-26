#include "StdAfx.h"
#include "TileManager.h"
#include "Unit.h"
#include "Tile.h"
#include "GraphicsManager.h"
#include "ParticleManager.h"
#include "GameplayState.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Message.h"
#include "AddResourceMessage.h"
#include "FloatingText.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "Player.h"


CTileManager* CTileManager::s_Instance = nullptr;

CTileManager::CTileManager(void)
{
	//m_pTileMap=nullptr;
	//m_nTextureImageID=0;
	//m_nFrozenTextureImageID=0;
}

CTileManager::~CTileManager(void)
{

}

CTileManager* CTileManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CTileManager();

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
	m_pTileMap = nullptr;
}

void CTileManager::Init()
{
	m_pTileMap = nullptr;
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
	TSTRING Path= _T("Assets/Tiles")+_TStupid_textconversion;
	CGraphicsManager::GetInstance()->LoadImageW(Path,_T("Map"),D3DCOLOR_XRGB(0,0,0));
	m_nTextureImageID= CGraphicsManager::GetInstance()->GetID(_T("Map"));

	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets/Tiles/MapEditorFrozenTiles.png"),_T("iceTile"),D3DCOLOR_XRGB(0,0,0));
	m_nFrozenTextureImageID= CGraphicsManager::GetInstance()->GetID(_T("iceTile"));

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
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_FOREST:
				{
					
					Rsource = CellAlgorithm(TT_FOREST);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y- CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_MOUNTAINS:
				{
					Rsource = CellAlgorithm(TT_MOUNTAINS);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_WATER:
				{
					Rsource = CellAlgorithm(TT_WATER);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y  - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_FARM:
				{
					Rsource = CellAlgorithm(TT_FARM);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_MILL:
				{
					Rsource = CellAlgorithm(TT_MILL);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			case TT_MINE:
				{
					Rsource = CellAlgorithm(TT_MINE);
					if (m_pTileMap[i][j].GetIfFrozen())
					{
					pTM->Draw(m_nFrozenTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource, (float)(TWidth / 2), (float)(THeight/ 2), fRad);						
					}
					else
					{
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y  - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
					}
				}
				break;
			}
			if (m_pTileMap[i][j].GetIfDeadTile())
			{
				Rsource = CellAlgorithm(TT_TOMBSTONE);
					pTM->Draw(m_nTextureImageID,x - CGameplayState::GetInstance()->GetCamOffsetX()
						,y  - CGameplayState::GetInstance()->GetCamOffsetY(),1.0F,1.0F,&Rsource,(float)(TWidth / 2), (float)(THeight/ 2), fRad);
				
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

void CTileManager::EvaluateResources(int nPlayerID)
{
	int nTotalMetal = 0;
	int nTotalWood = 0;
	for (int x = 0; x < m_nRows; x++)
	{
		for (int y = 0; y < m_nColumns; y++)
       {
		   if (m_pTileMap[x][y].GetIfCaptured())
		   {
			   if (m_pTileMap[x][y].GetPlayerID()==nPlayerID)
			   {
					CAddResourceMessage* pMsg = new CAddResourceMessage((TILE_TYPE)m_pTileMap[x][y].GetTileType(),nPlayerID);
					CMessageSystem::GetInstance()->SendMessageW(pMsg);
					switch (m_pTileMap[x][y].GetTileType())
					{
					case (TT_MILL):
						nTotalWood+= WOOD_PER_MILL;
						break;
					case (TT_MINE):
						nTotalMetal+= METAL_PER_MINE;
						break;
					}
			   }
		   }
		   if (m_pTileMap[x][y].GetIfCapturing())
		   {
			   if (m_pTileMap[x][y].GetIfOccupied())
			   {
				   if ((CGameManager::GetInstance()->FindUnit(Vec2D(x, y))->GetPlayerID() == CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID()))
				   {
					   m_pTileMap[x][y].SetIfCaptured(true);
					   m_pTileMap[x][y].SetIfCapturing(false);
				   }
			   }
			   else
			   {
				   m_pTileMap[x][y].SetIfCapturing(false);
				   m_pTileMap[x][y].SetPlayerID(-1);
			   }
		   }
	   }
	}
	std::ostringstream oss;
	oss << "+" << nTotalWood;
	CFloatingText::GetInstance()->AddScreenText(oss.str(), Vec2Df(510, 480), Vec2Df(0, -10), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));

	CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerWoodEarned += nTotalWood;
	oss.str("");
	oss << "+" << nTotalMetal;
	CFloatingText::GetInstance()->AddScreenText(oss.str(), Vec2Df(610, 480), Vec2Df(0, -10), 1.0f, 0.4f, D3DCOLOR_XRGB(0, 255, 0));
	CGameManager::GetInstance()->GetCurrentPlayer()->GetStats()->nPlayerWoodEarned += nTotalMetal;

}


int CTileManager::GetSelectedTile(lua_State* L)
{
	CTile* selectedTile = CTileManager::GetInstance()->GetTile(CGameplayState::GetInstance()->GetSelectionPos().nPosX, 
		CGameplayState::GetInstance()->GetSelectionPos().nPosY);

	if (selectedTile != nullptr)
	{
		lua_pushnumber(L, selectedTile->GetPosition().nPosX);
		lua_pushnumber(L, selectedTile->GetPosition().nPosY);
	}
	return 2;
}

int CTileManager::DestroyForest(lua_State* L)
{
	int posX = (int)lua_tonumber(L, 1);
	int posY = (int)lua_tonumber(L, 2);

	CTile* selectedTile = CTileManager::GetInstance()->GetTile(CGameplayState::GetInstance()->GetSelectionPos().nPosX, 
		CGameplayState::GetInstance()->GetSelectionPos().nPosY);
	if( selectedTile != nullptr )
	{	
		if (selectedTile->GetTileType() == TT_FOREST)
		{
			selectedTile->SetTileType(TT_PLAINS);
			MapModification mod;
			mod.posX = selectedTile->GetPosition().nPosX;
			mod.posY = selectedTile->GetPosition().nPosY;
			mod.modType = SP_DESTROYFOREST;
			CGameManager::GetInstance()->AddModification(mod);
		}
	}

	return 0;
}
int CTileManager::RaiseMountain(lua_State* L)
{
	int posX = (int)lua_tonumber(L, 1);
	int posY = (int)lua_tonumber(L, 2);

	CTile* selectedTile = CTileManager::GetInstance()->GetTile(CGameplayState::GetInstance()->GetSelectionPos().nPosX, 
		CGameplayState::GetInstance()->GetSelectionPos().nPosY);
	if( selectedTile != nullptr )
	{	
		if (selectedTile->GetTileType() != TT_FARM && selectedTile->GetTileType() != TT_MILL &&
			selectedTile->GetTileType() != TT_MINE)
		{
			selectedTile->SetTileType(TT_MOUNTAINS);
			selectedTile->SetIfPassable(false);
			MapModification mod;
			mod.posX = selectedTile->GetPosition().nPosX;
			mod.posY = selectedTile->GetPosition().nPosY;
			mod.modType = SP_RAISEMOUNTAIN;
			CGameManager::GetInstance()->AddModification(mod);
		}
	}

	return 0;

}