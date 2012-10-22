#include "StdAfx.h"
#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(void)
{
}

LevelSelectState::~LevelSelectState(void)
{
}

RECT LevelSelectState::CellAlgorithm( int id )
{
	RECT rSource;

	rSource.left	= (id % 4) * (nFakeTileWidth - 26);
	rSource.top		= (id / 4) * (nFakeTileHeight - 27);

	rSource.right	= rSource.left	+ (nFakeTileWidth - 26) +1;
	rSource.bottom	= rSource.top	+ (nFakeTileHeight - 27);

	return rSource;
}

void LevelSelectState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	selected = 0;
	m_ptempmap = new CTile*();
	m_p2ndtempmap = new CTile*();
	CTileManager* pTM=CTileManager::GetInstance();
	string filename= "Assets\\Tiles\\TestMap1.xml";
	pTM->LoadSave(filename);
	m_pRows = pTM->GetNumRows();
	m_pColumns = pTM->GetNumColumns();
	m_ptempmap= new CTile*[m_pRows];
	for (int x = 0; x< m_pRows; ++x)
	{
		m_ptempmap[x]= new CTile[m_pColumns];
	}
	for(int i = 0; i < m_pRows; i++)
	{
		for(int j = 0; j < m_pColumns; j++)
		{
			m_ptempmap[i][j] = *pTM->GetTile(i,j);
		}
	}
	string thefilename= "Assets\\Tiles\\TestMap2.xml";
	pTM->LoadSave(thefilename);
	m_p2ndRows = pTM->GetNumRows();
	m_p2ndColumns = pTM->GetNumColumns();
	m_p2ndtempmap= new CTile*[m_pRows];
	for (int x = 0; x< m_pRows; ++x)
	{
		m_p2ndtempmap[x]= new CTile[m_pColumns];
	}
	for(int i = 0; i < m_p2ndRows; i++)
	{
		for(int j = 0; j < m_p2ndColumns; j++)
		{
			m_p2ndtempmap[i][j] = *pTM->GetTile(i,j);
		}
	}
}

void LevelSelectState::Exit(void)
{
	m_ptempmap = nullptr;
	delete m_ptempmap;
	m_p2ndtempmap = nullptr;
	delete m_p2ndtempmap;
}

void LevelSelectState::Input(INPUT_ENUM input)
{
	switch(input)
	{
	case INPUT_ACCEPT:
		{
			if(selected == 0)
			{
				CTileManager* pTM=CTileManager::GetInstance();
				CGameManager::GetInstance()->NewGame("level1", 1);
				CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
			}
			else if(selected == 1)
			{
				CTileManager* pTM=CTileManager::GetInstance();
				CGameManager::GetInstance()->NewGame("level2", 2);
				CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
			}
			break;
		}
	case INPUT_LEFT:
		{
			std::wostringstream oss;
			oss << "LevelState: INPUT_LEFT @ " << GetTickCount() << '\n';
			OutputDebugString((LPCWSTR)oss.str().c_str());
			if(selected == 1)
				selected--;
			else
				selected++;
			break;
		}
	case INPUT_RIGHT:
		{
			std::wostringstream oss;
			oss << "LevelState: INPUT_RIGHT @ " << GetTickCount() << '\n';
			OutputDebugString((LPCWSTR)oss.str().c_str());
			if(selected == 0)
				selected++;
			else
				selected--;
			break;
		}
	case INPUT_CANCEL:
		{
			CStateStack::GetInstance()->Pop();
		}
	}
}

void LevelSelectState::Update(float fElapsedTime)
{

}

void LevelSelectState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0,100,255);
	int nMiniMapOffsetX = 60;
	int nMiniMapOffsetY = 50;
	RECT miniR = {nMiniMapOffsetX, nMiniMapOffsetY, nMiniMapOffsetX + 225, nMiniMapOffsetY + 152};
	RECT selectedrect = {nMiniMapOffsetX-5, nMiniMapOffsetY-5, nMiniMapOffsetX + 230, nMiniMapOffsetY + 157};
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	if(selected == 0)
		CSGD_Direct3D::GetInstance()->DrawRect(selectedrect,255,0,0);
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	float nMiniMapWidth = 225.0f;
	float nMiniMapHeight = 152.0f;
	float nMiniTileWidth = nMiniMapWidth / m_pRows;
	float nMiniTileHeight = nMiniMapHeight / m_pColumns;

	// Render the tiles. Only using colored blocks for now
	for (int i = 0; i < m_pRows; ++i)
	{
		for (int j = 0; j < m_pColumns; ++j)
		{
			RECT tileRect = { (LONG)(i * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			CTile* pTile = &m_ptempmap[i][j];
			RECT rSrc;
			switch (pTile->GetTileType())
			{
			case TT_PLAINS:
				rSrc = CellAlgorithm(TT_PLAINS);
				g=177; r=34; b=76; break;
			case TT_FOREST:
				rSrc = CellAlgorithm(TT_FOREST);
				g=128; r=0; b=0; break;
			case TT_MOUNTAINS:
				rSrc = CellAlgorithm(TT_MOUNTAINS);
				g=64;r=128; b=0; break;
			case TT_WATER:
				rSrc = CellAlgorithm(TT_WATER);
				g=128;r=0;b=192;break; 
			case TT_MINE:
				rSrc = CellAlgorithm(TT_MINE);
				g=64;r=128; b=0; break;
			case TT_MILL:
				rSrc = CellAlgorithm(TT_MILL);
				g=128; r=0; b=0; break;
			case TT_FARM:
				rSrc = CellAlgorithm(TT_FARM);
				g=177; r=34; b=76; break;
			case TT_CASTLE:
				rSrc = CellAlgorithm(TT_CASTLE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("GrassTile")),
				tileRect.left, tileRect.top, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);
			//CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);
			r = 255 * !(pTile->GetPlayerID());
			b = 255 * (pTile->GetPlayerID());
			g = 0;
			switch (pTile->GetTileType())
			{
			case TT_MILL:
			case TT_MINE:
			case TT_FARM:
				break;
			}
		}
	}
	ostringstream woss;
	woss<<"Basic test map";
	tempfont.Print(woss.str().c_str(), nMiniMapOffsetX, nMiniMapOffsetY + 162, 0.5f, D3DXCOLOR(255,255,255,255));
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	nMiniMapOffsetX = 500;
	nMiniMapOffsetY = 50;
	miniR.left = nMiniMapOffsetX; miniR.top = nMiniMapOffsetY; miniR.right = nMiniMapOffsetX + 225; miniR.bottom = nMiniMapOffsetY + 152;
	selectedrect.left = nMiniMapOffsetX-5; selectedrect.top = nMiniMapOffsetY-5; selectedrect.right = nMiniMapOffsetX + 230; selectedrect.bottom = nMiniMapOffsetY + 157;
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	if(selected == 1)
		CSGD_Direct3D::GetInstance()->DrawRect(selectedrect,255,0,0);
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	nMiniMapWidth = 225.0f;
	nMiniMapHeight = 152.0f;
	nMiniTileWidth = nMiniMapWidth / m_p2ndRows;
	nMiniTileHeight = nMiniMapHeight / m_p2ndColumns;

	// Render the tiles. Only using colored blocks for now
	for (int i = 0; i < m_p2ndRows; ++i)
	{
		for (int j = 0; j < m_p2ndColumns; ++j)
		{
			RECT tileRect = { (LONG)(i * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			CTile* pTile = &m_p2ndtempmap[i][j];
			RECT rSrc;
			switch (pTile->GetTileType())
			{
			case TT_PLAINS:
				rSrc = CellAlgorithm(TT_PLAINS);
				g=177; r=34; b=76; break;
			case TT_FOREST:
				rSrc = CellAlgorithm(TT_FOREST);
				g=128; r=0; b=0; break;
			case TT_MOUNTAINS:
				rSrc = CellAlgorithm(TT_MOUNTAINS);
				g=64;r=128; b=0; break;
			case TT_WATER:
				rSrc = CellAlgorithm(TT_WATER);
				g=128;r=0;b=192;break; 
			case TT_MINE:
				rSrc = CellAlgorithm(TT_MINE);
				g=64;r=128; b=0; break;
			case TT_MILL:
				rSrc = CellAlgorithm(TT_MILL);
				g=128; r=0; b=0; break;
			case TT_FARM:
				rSrc = CellAlgorithm(TT_FARM);
				g=177; r=34; b=76; break;
			case TT_CASTLE:
				rSrc = CellAlgorithm(TT_CASTLE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("GrassTile")),
				tileRect.left, tileRect.top, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);
			//CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);
			r = 255 * !(pTile->GetPlayerID());
			b = 255 * (pTile->GetPlayerID());
			g = 0;
			switch (pTile->GetTileType())
			{
			case TT_MILL:
			case TT_MINE:
			case TT_FARM:
				break;
			}
		}
	}
	ostringstream boss;
	boss<<"You are now surrounded by water!";
	tempfont.Print(boss.str().c_str(), nMiniMapOffsetX, nMiniMapOffsetY + 162, 0.5f, D3DXCOLOR(255,255,255,255), 210);

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();


}

LevelSelectState* LevelSelectState::GetInstance()
{
	static LevelSelectState s_Instance;
	return &s_Instance;
}