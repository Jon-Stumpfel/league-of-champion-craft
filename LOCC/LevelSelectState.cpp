#include "StdAfx.h"
#include "LevelSelectState.h"
#include "CoinToss.h"
#include "MultiplayerState.h"
#include "SocketServer.h"
#include "StringTable.h"

const float MAPWIDTH=180.0f;
const float MAPHEIGHT=180.0f;
const int	ROW1=150;
const int	ROW2=450;
const int	COL1=100;
const int	COL2=300;

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
	m_2Dselected.nPosX = 0;
	m_2Dselected.nPosY = 0;

	CTileManager* pTM=CTileManager::GetInstance();
	string filename1= "Assets/Tiles/Level1.xml";
	m_vMap1= pTM->JonsLoad(filename1);

	m_nScrollID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets\\Menus\\Scroll.png"), D3DXCOLOR(255,255,255,255));

	string filename2= "Assets/Tiles/Level2.xml";
	m_vMap2=pTM->JonsLoad(filename2);
	
	string filename3= "Assets/Tiles/Level3.xml";
	m_vMap3= pTM->JonsLoad(filename3);

	string filename4= "Assets/Tiles/Level4.xml";
	m_vMap4= pTM->JonsLoad(filename4);
}

void LevelSelectState::Exit(void)
{

	m_vMap1.clear();
	m_vMap2.clear();
	m_vMap3.clear();
	m_vMap4.clear();
}

void LevelSelectState::Input(INPUT_ENUM input)
{
	bool bNetworkedGame = false;
	switch(input)
	{
	case INPUT_ACCEPT:
		{
			if(m_2Dselected.nPosX ==0  && m_2Dselected.nPosY==0)
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
			else if(m_2Dselected.nPosX ==1  && m_2Dselected.nPosY==0)
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
			else if(m_2Dselected.nPosX ==0  && m_2Dselected.nPosY==1)
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
				CGameManager::GetInstance()->NewGame("level3", 3);

				CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
			}
			else if(m_2Dselected.nPosX ==1  && m_2Dselected.nPosY==1)
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
				CGameManager::GetInstance()->NewGame("level4", 4);

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
			if(m_2Dselected.nPosY >= 1)
				m_2Dselected.nPosY--;
			else
				m_2Dselected.nPosY++;
			break;
		}
	case INPUT_RIGHT:
		{
			std::wostringstream oss;
			oss << "LevelState: INPUT_RIGHT @ " << GetTickCount() << '\n';
			OutputDebugString((LPCWSTR)oss.str().c_str());
			if(m_2Dselected.nPosY <= 0)
				m_2Dselected.nPosY++;
			else
				m_2Dselected.nPosY--;
			break;
		}
	case INPUT_UP:
		{
			std::wostringstream oss;
			oss << "LevelState: INPUT_LEFT @ " << GetTickCount() << '\n';
			OutputDebugString((LPCWSTR)oss.str().c_str());
			if(m_2Dselected.nPosX >= 1)
				m_2Dselected.nPosX--;
			else
				m_2Dselected.nPosX++;
			break;
		}
	case INPUT_DOWN:
		{
			std::wostringstream oss;
			oss << "LevelState: INPUT_RIGHT @ " << GetTickCount() << '\n';
			OutputDebugString((LPCWSTR)oss.str().c_str());
			if(m_2Dselected.nPosX <= 0)
				m_2Dselected.nPosX++;
			else
				m_2Dselected.nPosX--;
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
	if (m_2Dselected.nPosX==0 && m_2Dselected.nPosY==0)
	{
		m_sbSelected[0]=true; m_sbSelected[1]=false; m_sbSelected[2]=false; m_sbSelected[3]=false;
	}
	if (m_2Dselected.nPosX==1 && m_2Dselected.nPosY==0)
	{
		m_sbSelected[0]=false; m_sbSelected[1]=true; m_sbSelected[2]=false; m_sbSelected[3]=false;
	}
	if (m_2Dselected.nPosX==0 && m_2Dselected.nPosY==1)
	{
		m_sbSelected[0]=false; m_sbSelected[1]=false; m_sbSelected[2]=true; m_sbSelected[3]=false;
	}
	if (m_2Dselected.nPosX==1 && m_2Dselected.nPosY==1)
	{
		m_sbSelected[0]=false; m_sbSelected[1]=false; m_sbSelected[2]=false; m_sbSelected[3]=true;
	}
}

void LevelSelectState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);
	//CSGD_TextureManager::GetInstance()->Draw(blueguyid,0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	//CSGD_TextureManager::GetInstance()->Draw(redguyid,290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));

	// Draw The Scroll pieces

	RECT Scrollrect;
	//Draw the middle first , so that you can put the top and bottm over it
	Scrollrect.bottom = 392;
	Scrollrect.top = 198;
	Scrollrect.left = 15;
	Scrollrect.right = 537;
	CSGD_TextureManager::GetInstance()->Draw(m_nScrollID,25,80,1.44f,2.5f,&Scrollrect,0,0,0,D3DXCOLOR(255,255,255,255));
	
	//draw the top part
	Scrollrect.bottom = 113;
	Scrollrect.top = 0;
	Scrollrect.left = 0;
	Scrollrect.right = 555;
	CSGD_TextureManager::GetInstance()->Draw(m_nScrollID,0,0,1.45f,.8f,&Scrollrect,0,0,0,D3DXCOLOR(255,255,255,255));
	
	//Draw the bottom
	Scrollrect.bottom = 584;
	Scrollrect.top = 472;
	Scrollrect.left = 2;
	Scrollrect.right = 557;
	CSGD_TextureManager::GetInstance()->Draw(m_nScrollID,0,487,1.45f,.85f,&Scrollrect,0,0,0,D3DXCOLOR(255,255,255,255));
	
	//STRINGHERE=("JON PUT A STRING HERE");
	DrawMap(string("Trample Hill"),ROW1,COL1,m_vMap1,m_sbSelected[0]);
	//STRINGHERE=("JON PUT A STRING HERE");
	DrawMap(string("Forest Siege"),ROW1,COL2,m_vMap2,m_sbSelected[1]);
	DrawMap(string("Siege on the mountain"),ROW2,COL1,m_vMap3,m_sbSelected[2]);
	//STRINGHERE=("JON PUT A STRING HERE");
	DrawMap(string("Close Quarters"),ROW2,COL2,m_vMap4,m_sbSelected[3]);

}
void LevelSelectState::DrawMap(string sLevelname, int rowoffset, int coloffset, vector<vector<TILE_TYPE>> m_vMap_, bool selected)
{
	int nMiniMapOffsetX = rowoffset;
	int nMiniMapOffsetY = coloffset;
	
	float fMapWidth		=MAPWIDTH;
	float fMapHeight	= MAPHEIGHT;
	int rows= m_vMap_.size();
	int	cols= m_vMap_.size();
	float nMiniTileWidth	=0;
	float nMiniTileHeight	=0;

	if(rows!=cols)
	{
		if (cols>rows)
		{
			nMiniTileWidth	= (fMapWidth  / rows)/2;
			nMiniTileHeight	= fMapHeight / cols;
		}
		if (cols<rows)
		{
			nMiniTileWidth	= fMapWidth  / rows;
			nMiniTileHeight	= (fMapHeight / cols)/2;
		}
	}
	else
	{
		nMiniTileWidth	= fMapWidth  / rows;
		nMiniTileHeight	= fMapHeight / cols;
	}

	RECT miniR = {nMiniMapOffsetX-5, nMiniMapOffsetY-5, 
					(float)(nMiniMapOffsetX +nMiniTileWidth*rows+5),
					(float)(nMiniMapOffsetY +nMiniTileHeight*cols+5)};
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	if(selected)
		CSGD_Direct3D::GetInstance()->DrawRect(miniR,255,0,0);
	else
	CSGD_Direct3D::GetInstance()->DrawRect(miniR, 0, 0, 0);

	// Render the tiles. Only using colored blocks for now
	std::vector<std::vector<TILE_TYPE>>::iterator itermap1;
	int i = 0;
	int j = 0;
	std::vector<TILE_TYPE>::iterator iter;
	std::wostringstream looss;
	int x = 0;
	int y = 0;
	for (itermap1 = m_vMap_.begin(); itermap1 != m_vMap_.end(); ++itermap1)
	{
		for (iter = (*itermap1).begin(); iter != (*itermap1).end(); ++iter)
		{
			RECT tileRect = { (LONG)(i * nMiniTileWidth + nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight+ nMiniMapOffsetY), 
				(LONG)(i * nMiniTileWidth + nMiniTileWidth+ nMiniMapOffsetX),
				(LONG)(j * nMiniTileHeight + nMiniTileHeight+ nMiniMapOffsetY)};
			int r = 0;
			int g = 0;
			int b = 0;
			TILE_TYPE workType = (*iter);

			switch (workType)
			{
			case TT_PLAINS://light green
				g=177; r=34; b=76; break;
			case TT_FOREST://dark green
				g=134; r=59; b=38; break;
			case TT_MOUNTAINS://grey
				g=100;r=100; b=100; break;
			case TT_WATER://light blue
				g=155;r=0;b=195;break; 
			case TT_MINE: //gold
				g=194;r=155; b=79; break;
			case TT_MILL://orange
				g=106; r=255; b=0; break;
			case TT_FARM:// yellow
				g=240; r=255; b=33; break;
			case TT_TOMBSTONE:
				//rSrc = CellAlgorithm(TT_TOMBSTONE);
			default:
				g=255; r=255; b=255; break;
			}
			CSGD_Direct3D::GetInstance()->DrawRect(tileRect, r, g, b);

			j++;
		}
		j = 0;
		i++;
	}
	ostringstream woss;
	woss<<StringTable::GetInstance()->GetString(sLevelname);
	tempfont.Print(woss.str().c_str(), nMiniMapOffsetX+2, nMiniMapOffsetY+10, 0.3f, D3DXCOLOR(255,255,255,255));
	//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
}

LevelSelectState* LevelSelectState::GetInstance()
{
	static LevelSelectState s_Instance;
	return &s_Instance;
}