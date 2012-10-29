#include "StdAfx.h"
#include "LevelSelectState.h"
#include "CoinToss.h"
#include "MultiplayerState.h"
#include "SocketServer.h"
#include "StringTable.h"
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
	string filename= "Assets\\Tiles\\Level1.xml";
	pTM->LoadSave(filename);
	m_pRows = pTM->GetNumRows();
	m_pColumns = pTM->GetNumColumns();
	Scroll = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\scroll.png"), D3DXCOLOR(255,255,255,255));
	m_vMap1.clear();
	m_vMap2.clear();
	for (int x = 0; x < m_pRows; ++x)
	{
		std::vector<TILE_TYPE> vec;
		for (int y = 0; y < m_pColumns; ++y)
		{
			vec.push_back((TILE_TYPE)pTM->GetTile(x, y)->GetTileType());
		}
		m_vMap1.push_back(vec);
	}

	int x = 9;
	//m_ptempmap= new CTile*[m_pRows];
	//for (int x = 0; x< m_pRows; ++x)
	//{
	//	m_ptempmap[x]= new CTile[m_pColumns];
	//}
	//for(int i = 0; i < m_pRows; i++)
	//{
	//	for(int j = 0; j < m_pColumns; j++)
	//	{
	//		m_ptempmap[i][j] = *pTM->GetTile(i,j);
	//	}
	//}
	string thefilename= "Assets\\Tiles\\Level2.xml";
	pTM->LoadSave(thefilename);
	m_p2ndRows = pTM->GetNumRows();
	m_p2ndColumns = pTM->GetNumColumns();

	for (int x = 0; x < m_p2ndRows; ++x)
	{
		std::vector<TILE_TYPE> vec;
		for (int y = 0; y < m_p2ndColumns; ++y)
		{
			vec.push_back((TILE_TYPE)pTM->GetTile(x, y)->GetTileType());
		}
		m_vMap2.push_back(vec);
	}

	//m_p2ndtempmap= new CTile*[m_pRows];
	//for (int x = 0; x< m_pRows; ++x)
	//{
	//	m_p2ndtempmap[x]= new CTile[m_pColumns];
	//}
	//for(int i = 0; i < m_p2ndRows; i++)
	//{
	//	for(int j = 0; j < m_p2ndColumns; j++)
	//	{
	//		m_p2ndtempmap[i][j] = *pTM->GetTile(i,j);
	//	}
	//}
}

void LevelSelectState::Exit(void)
{
	m_vMap1.clear();
	m_vMap2.clear();
}

void LevelSelectState::Input(INPUT_ENUM input)
{
	bool bNetworkedGame = false;
	switch(input)
	{
	case INPUT_ACCEPT:
		{
			if(selected == 0)
			{
				CTileManager* pTM=CTileManager::GetInstance();

				if (CMultiplayerState::GetInstance()->GetNetworkSetup())
				{
					char buffer[80];
					sprintf_s(buffer, "%c%d", NET_BEGINMAP1, 0);
					send(CSocketServer::GetInstance()->sockets[2], buffer, 2, 0);
					unsigned int seed = (unsigned int)(time(0));
					CGameManager::GetInstance()->SetRandomSeed(seed);
					sprintf_s(buffer, "%d", seed);
					send(CSocketServer::GetInstance()->sockets[2], buffer, 10, 0);
					bNetworkedGame = true;
				}

				CGameManager::GetInstance()->NewGame("level1", 1);
				CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
			}
			else if(selected == 1)
			{
				CTileManager* pTM=CTileManager::GetInstance();

				if (CMultiplayerState::GetInstance()->GetNetworkSetup())
				{
					char buffer[80];
					sprintf_s(buffer, "%c%d", NET_BEGINMAP2, 0);
					send(CSocketServer::GetInstance()->sockets[2], buffer, 2, 0);
					unsigned int seed = (unsigned int)(time(0));
					CGameManager::GetInstance()->SetRandomSeed(seed);
					sprintf_s(buffer, "%d", seed);
					send(CSocketServer::GetInstance()->sockets[2], buffer, 8, 0);
					bNetworkedGame = true;
				}
				CGameManager::GetInstance()->NewGame("level2", 2);

				CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
			}
			if (!bNetworkedGame)
				CStateStack::GetInstance()->Push(CCoinToss::GetInstance());

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
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);
	//CSGD_TextureManager::GetInstance()->Draw(blueguyid,0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	//CSGD_TextureManager::GetInstance()->Draw(redguyid,290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	RECT* toprect = new RECT();
	toprect->bottom = 392;
	toprect->top = 198;
	toprect->left = 15;
	toprect->right = 537;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,25,100,1.44f,2.3f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 113;
	toprect->top = 0;
	toprect->left = 0;
	toprect->right = 555;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,0,0,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 584;
	toprect->top = 472;
	toprect->left = 2;
	toprect->right = 557;
	CSGD_TextureManager::GetInstance()->Draw(Scroll,0,487,1.45f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->bottom = 77;
	toprect->top = 56;
	toprect->left = 152;
	toprect->right = 402;
	delete toprect;
	toprect = nullptr;
	int nMiniMapOffsetX = 60;
	int nMiniMapOffsetY = 50;
	RECT miniR = {nMiniMapOffsetX, nMiniMapOffsetY+100, nMiniMapOffsetX + 225, nMiniMapOffsetY + 252};
	RECT selectedrect = {nMiniMapOffsetX-5, nMiniMapOffsetY+95, nMiniMapOffsetX + 230, nMiniMapOffsetY + 257};
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	if(selected == 0)
		CSGD_Direct3D::GetInstance()->DrawRect(selectedrect,255,0,0);
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	float nMiniMapWidth = 225.0f;
	float nMiniMapHeight = 152.0f;
	float nMiniTileWidth = nMiniMapWidth / m_pRows;
	float nMiniTileHeight = nMiniMapHeight / m_pColumns;

	// Render the tiles. Only using colored blocks for now
	std::vector<std::vector<TILE_TYPE>>::iterator itermap1;
	int i = 0;
	int j = 0;
	std::vector<TILE_TYPE>::iterator iter;

		std::wostringstream looss;
	int x = 0;
	int y = 0;
	for (itermap1 = m_vMap1.begin(); itermap1 != m_vMap1.end(); ++itermap1)
	{
		looss.str(_T(""));

		looss << "Iter Map1 x: " << x++ << '\n';
		for (iter = (*itermap1).begin(); iter != (*itermap1).end(); ++iter)
		{
	//for (int i = 0; i < m_pRows; ++i)
	//{
	//	for (int j = 0; j < m_pColumns; ++j)
	//	{
			looss.str(_T(""));

			looss << "Iter Map1 y: " << y++ << '\n';
			RECT tileRect = { (LONG)(i * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			//CTile* pTile = &m_ptempmap[i][j];
			TILE_TYPE workType = (*iter);
			//if (pTile == nullptr)
			//	continue;
			RECT rSrc;
			switch (workType)
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
			//case TT_CASTLE:
			//	rSrc = CellAlgorithm(TT_CASTLE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("Map")),
				tileRect.left, tileRect.top+100, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);
	
			j++;
		}
		j = 0;
		i++;
	}
	ostringstream woss;
	woss<<StringTable::GetInstance()->GetString("Bottleneck");
	tempfont.Print(woss.str().c_str(), nMiniMapOffsetX, nMiniMapOffsetY + 262, 0.3f, D3DXCOLOR(255,255,255,255));
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	nMiniMapOffsetX = 500;
	nMiniMapOffsetY = 50;
	miniR.left = nMiniMapOffsetX; miniR.top = nMiniMapOffsetY+100; miniR.right = nMiniMapOffsetX + 225; miniR.bottom = nMiniMapOffsetY + 252;
	selectedrect.left = nMiniMapOffsetX-5; selectedrect.top = nMiniMapOffsetY+95; selectedrect.right = nMiniMapOffsetX + 230; selectedrect.bottom = nMiniMapOffsetY + 257;
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	if(selected == 1)
		CSGD_Direct3D::GetInstance()->DrawRect(selectedrect,255,0,0);
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	nMiniMapWidth = 225.0f;
	nMiniMapHeight = 152.0f;
	nMiniTileWidth = nMiniMapWidth / m_p2ndRows;
	nMiniTileHeight = nMiniMapHeight / m_p2ndColumns;

	//return;
	// Render the tiles. Only using colored blocks for now
	std::vector<std::vector<TILE_TYPE>>::iterator itermap2;
	int i1 = 0;
	int j1 = 0;

	looss.str(_T(""));
	x = y = 0;
	for (itermap2 = m_vMap2.begin(); itermap2 != m_vMap2.end(); ++itermap2)
	{
		looss.str(_T(""));

		looss << "Iter Map2 x: " << x++ << '\n';
		for (iter = (*itermap2).begin(); iter != (*itermap2).end(); ++iter)
		{
	//for (int i = 0; i < m_p2ndRows; ++i)
	//{
	//	for (int j = 0; j < m_p2ndColumns; ++j)
	//	{
			woss.str((""));
		woss << "Iter Map2 y: " << y++ << '\n';
			RECT tileRect = { (LONG)(i1 * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j1 * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i1 * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j1 * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			//CTile* pTile = &m_p2ndtempmap[i][j];
			//if (pTile == nullptr)
			//	continue;
			TILE_TYPE workType = (*iter);
			RECT rSrc;
			switch (workType)
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
			case TT_TOMBSTONE:
				rSrc = CellAlgorithm(TT_TOMBSTONE);
			default:
				g=177; r=34; b=76; break;
			}
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("Map")),
				tileRect.left, tileRect.top+100, nMiniTileWidth/(nFakeTileWidth - 27), nMiniTileHeight/(nFakeTileHeight - 27), &rSrc);
			//CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);
			//r = 255 * !(pTile->GetPlayerID());
			//b = 255 * (pTile->GetPlayerID());
			//g = 0;
			//switch (pTile->GetTileType())
			//{
			//case TT_MILL:
			//case TT_MINE:
			//case TT_FARM:
			//	break;
			//}
			j1++;
		}
		j1 = 0;
		i1++;
	}
	ostringstream boss;
	boss<<StringTable::GetInstance()->GetString("Siege on the mountain");
	tempfont.Print(boss.str().c_str(), nMiniMapOffsetX, nMiniMapOffsetY + 262, 0.3f, D3DXCOLOR(255,255,255,255), 210);

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
}

LevelSelectState* LevelSelectState::GetInstance()
{
	static LevelSelectState s_Instance;
	return &s_Instance;
}