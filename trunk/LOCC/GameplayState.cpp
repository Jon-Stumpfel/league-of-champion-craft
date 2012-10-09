#include "StdAfx.h"
#include "GameplayState.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "GameManager.h"
#include "MessageSystem.h"
#include "SpawnUnitMessage.h"
#include "AddResourceMessage.h"
#include "DeSpawnUnitMessage.h"
#include "Unit.h"
#include "ParticleManager.h"
#include "Player.h"
#include "TileManager.h"
#include "Tile.h"

//CGameplayState* CGameplayState::s_Instance = nullptr;

CGameplayState::CGameplayState(void)
{
}

CGameplayState::~CGameplayState(void)
{
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState s_Instance;
	return &s_Instance;
	//if( s_Instance == nullptr )
	//	s_Instance = new CGameplayState();

	//return s_Instance;
}

void CGameplayState::Enter(void)
{
	// test stuff

	CSpawnUnitMessage* pMsg = new CSpawnUnitMessage(Vec2D(1, 1), 0, UT_SWORDSMAN);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(2, 1), 0, UT_ARCHER);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(3, 1), 0, UT_HERO);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(4, 1), 0, UT_CAVALRY);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(5, 1), 0, UT_CASTLE);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(6, 1), 0, UT_SKELETON);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	pMsg = new CSpawnUnitMessage(Vec2D(7, 1), 0, UT_ICEBLOCK);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	CGameManager::GetInstance()->CreatePlayer(false);


	CGameManager::GetInstance()->CreatePlayer(false); // player 2
	pMsg = new CSpawnUnitMessage(Vec2D(3, 7), 1, UT_HERO);
	CMessageSystem::GetInstance()->SendMessageW(pMsg);

	CGameManager* pGM = CGameManager::GetInstance();
	CParticleManager* pPM = CParticleManager::GetInstance();

	Vec2Df test;
	test.fVecX = 400;
	test.fVecY = 300;

	pPM->LoadParticles( TEST, test );

	//test.fVecX = 100;
	//test.fVecY = 100;
	//pPM->LoadParticles( TESTSECOND,	test );

	CTileManager* pTM=CTileManager::GetInstance();

	string filename= "Assets\\Tiles\\TestMap.xml";

	pTM->LoadSave(filename);


	SetRect(&rCamRect, 0, 0, 
		CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth, CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight);

	// INITIALIZATION SETUP
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_CameraPos = Vec2D(0, 0);
	m_SelectionPos = Vec2D(0, 0);
}

int CGameplayState::GetCamOffsetX(void)
{
	return rCamRect.left * nFakeTileWidth;
}
int CGameplayState::GetCamOffsetY(void)
{
	return rCamRect.top * nFakeTileHeight;
}
void CGameplayState::Exit(void)
{
}

// Snaps the camera to pUnit. This is used for moving the camera to the player's hero at turn start
// but could be used for anything. Just pass a pUnit in and the camera and selection cursor shifts to that unit.
void CGameplayState::SnapToUnit(CUnit* pUnit)
{
	int nSelX = pUnit->GetPos().nPosX - m_SelectionPos.nPosX;
	int nSelY = pUnit->GetPos().nPosY - m_SelectionPos.nPosY;
	int nWindowTileWidth = CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth;
	int nWindowTileHeight = CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight;
	int nDesiredCamX = pUnit->GetPos().nPosX - (nWindowTileWidth / 2);
	int nDesiredCamY = pUnit->GetPos().nPosY - (nWindowTileHeight / 2);
	int camX = nDesiredCamX - m_CameraPos.nPosX;
	int camY = nDesiredCamY - m_CameraPos.nPosY;
	MoveCursor(nSelX, nSelY, false);
	MoveCamera(camX, camY);
}

// Moves the selection cursor by deltaX and deltaY values. Lock when true locks the camera from moving, otherwise
// the camera will stick with the cursor should it go off screen. Lock defaults to true
void CGameplayState::MoveCursor(int dX, int dY, bool lock)
{
	m_SelectionPos.nPosX += dX;
	m_SelectionPos.nPosY += dY;

	// If we're in moving mode, then calculate the best path
	if (m_bIsMoving)
	{
		CTileManager* pTM = CTileManager::GetInstance();
		CTile* pStartTile = pTM->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY);
		CTile* pTargetTile = pTM->GetTile(m_SelectionPos.nPosX, m_SelectionPos.nPosY);

		CalculateMove(pStartTile, pTargetTile);
	}

	// This locks camera to cursor position
	if (lock == true)
	{
		if (m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth) < m_SelectionPos.nPosX)
		{
			int n = m_CameraPos.nPosX + (CGame::GetInstance()->GetWindowWidth() / nFakeTileWidth);
			int nDistance = m_SelectionPos.nPosX - n;
			MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosX > m_SelectionPos.nPosX)
		{
			int n = m_CameraPos.nPosX;
			int nDistance = m_SelectionPos.nPosX - n;
			MoveCamera(nDistance, 0);
		}
		if (m_CameraPos.nPosY + (CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight) < m_SelectionPos.nPosY)
		{
			int n = m_CameraPos.nPosY + (CGame::GetInstance()->GetWindowHeight() / nFakeTileHeight);
			int nDistance = m_SelectionPos.nPosY - n;
			MoveCamera(0, nDistance);
		}
		if (m_CameraPos.nPosY > m_SelectionPos.nPosY)
		{
			int n = m_CameraPos.nPosY;
			int nDistance = m_SelectionPos.nPosY - n;
			MoveCamera(0, nDistance);
		}
	}

}

// Moves the camera by dX and dY values (delta)
void CGameplayState::MoveCamera(int dX, int dY)
{
	OffsetRect(&rCamRect, dX, dY);
	m_CameraPos.nPosX += dX;
	m_CameraPos.nPosY += dY;
}
void CGameplayState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_UP:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving))
			{
				// do nothing, up arrow does nothing with a unit selected
			}
			else
			{
				MoveCursor(0, -1);
			}
		}
		break;
	case INPUT_LEFT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (ShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell--;
				//	if (m_nSelectedChampSpell < 0)
				//		m_nSelectedChampSpell = 3;
				//}
				//else
				//{
				//	// Champion ability is not pulled up, so just move the cursor on the main panel
				//	m_nSelectedAbility--;
				//	if (m_nSelectedAbility < 0)
				//		m_nSelectedAbility = 2;
				//}
			}
			else
				MoveCursor(-1, 0);
		}
		break;
	case INPUT_RIGHT:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected!
			{
				// Move the ability selection box selector thing. Check if we have the champion spell pane pulled up 
				//if (m_bShowChampPane == true)
				//{
				//	// We have the champion ability pane up!
				//	m_nSelectedChampSpell++;
				//	if (m_nSelectedChampSpell > 3)
				//		m_nSelectedChampSpell = 0;
				//}
				//else
				//{
				//	// Champion ability is not pulled up, so just move the cursor on the main panel
				//	m_nSelectedAbility++;
				//	if (m_nSelectedAbility > 2)
				//		m_nSelectedAbility = 0;
				//}
			}
			else
				MoveCursor(1, 0);
		}
		break;
	case INPUT_DOWN:
		{
			if (m_pSelectedUnit != nullptr && (!m_bIsMoving)) // we have a unit selected
			{
				// do nothing! Up arrow does nada;
			}
			else
				MoveCursor(0, 1);
		}
		break;
	case INPUT_ACCEPT:
		{
			if (m_pSelectedUnit == nullptr)
			{
				m_pSelectedUnit = CGameManager::GetInstance()->FindUnit(m_SelectionPos);
			}
			else
			{
				if (m_bIsMoving)
				{
					MoveToTile(m_SelectionPos);
				}
				else
					m_bIsMoving = true;
			}
		}
		break;
	case INPUT_CANCEL:
		{
			m_pSelectedUnit = nullptr;
			m_bIsMoving = false;
			m_vWaypoints.clear();
		}
		break;
	case INPUT_CAM_UP:
		MoveCamera(0, -1);
		break;
	case INPUT_CAM_DOWN:
		MoveCamera(0, 1);
		break;
	case INPUT_CAM_LEFT:
		MoveCamera(-1, 0);
		break;
	case INPUT_CAM_RIGHT:
		MoveCamera(1, 0);
		break;
	default:
		break;
	}
}

// Attempts to move the selectedUnit to the tile at position nTilePosition
void CGameplayState::MoveToTile(Vec2D nTilePosition)
{
	// Cheapest movement algorithm hooray
	CTileManager* pTM = CTileManager::GetInstance();
	CTile* pStartTile = pTM->GetTile(m_pSelectedUnit->GetPos().nPosX, m_pSelectedUnit->GetPos().nPosY);
	CTile* pTargetTile = pTM->GetTile(nTilePosition.nPosX, nTilePosition.nPosY);


	// Check if where we are going to is passable and occupied, if so, return out of function
	if (pTargetTile->GetIfPassable() || pTargetTile->GetIfOccupied())
	{
		return;
	}

	// Check if the unit has already moved a number of tiles this turn up to their speed, if so, return out and clear stuff
	if (m_pSelectedUnit->GetTilesMoved() == m_pSelectedUnit->GetSpeed())
	{
		m_bIsMoving = false;
		m_pSelectedUnit = nullptr;
		m_vWaypoints.clear();
		// error sound?
		return;
	}


	// Calculate total number of moves this will take as well as total AP cost for the path. If the path ends
	// up taking us past our speed (or available tiles left to move), break out early and only count what we will make 
	// it to
	int nTotalAPCost = 0;
	int nMoveCount = 0;
	for (int i = m_vWaypoints.size() - 1; i >= 0 ; --i)
	{
		nTotalAPCost+= m_vWaypoints[i]->GetAPCost();
		nMoveCount++;
		if (nMoveCount == (m_pSelectedUnit->GetSpeed() - m_pSelectedUnit->GetTilesMoved()))
		{
			break;
		}
	}

	// If the total AP cost of the move is more than we have, return out. We can't afford to move
	if (nTotalAPCost > CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP())
	{
		// play error sound?
		return;
	}
	// If we're here, we're movin. Subtract the cost of the move from the player's AP
	CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->SetAP(
		CGameManager::GetInstance()->GetPlayer(m_pSelectedUnit->GetPlayerID())->GetAP() - nTotalAPCost);

	// Add the tile waypoints to the unit so that he can slide along them neatly
	for (int i = 0; i < m_vWaypoints.size(); ++i)
	{
		m_pSelectedUnit->AddWaypoint(m_vWaypoints[i]);
	}

	// After we hit enter we want to cancel and clear, either we're moving or we're not.
	m_bIsMoving = false;
	m_pSelectedUnit = nullptr;
	m_vWaypoints.clear();
	return;

}

// Uses A* pathfinding algorithm to find a cheap route from startTile to targetTile
bool CGameplayState::CalculateMove(CTile* startTile, CTile* targetTile)
{
	// If either of the tiles are null or we can't move into the last tile, don't calculate anything.
	if (startTile == nullptr || targetTile == nullptr || targetTile->GetIfOccupied() || targetTile->GetIfPassable())
		return false;

	// Create our lists that we will work inside and add the initial tile to the closed list
	CTileManager* pTM = CTileManager::GetInstance();
	std::list<ASNode*> openList;
	std::list<ASNode*> closedList;
	typedef std::list<ASNode*>::iterator closedIter;
	m_vWaypoints.clear();
	ASNode* n = new ASNode();
	n->pTile = startTile;
	n->nCost = 0;

	int safeCheck = 0;
	closedList.push_back(n);
	openList.remove(n);

	int nEstimatedTileCost = 3;

	while (true && (safeCheck < 1000))
	{
		// This loop will go through and check all tiles adjacent to our active tile. If they are legit tiles
		// I.E not null, are passable and are not occupied, then we add them to our openList of available tiles to move
		// we calculate the estimated cost on how much that tile will take us to get to our target if we go that way
		// Once we added all adjacent tiles, we find which of those tiles on the openList has the cheapest estimated route
		// we make the cheapest one our active tile, then repeat the process adding the tiles adjacent to the active tile.
		// We do this until we find our target tile and when we do, we break out of the loop.
		// We go to our targetTile node and see which tile we had set as it's parent in the path, then go to that. Then we loop
		// through parents until we get back to the start and we then have our path

		if (n->pTile->GetPosition().nPosY -1 >= 0) // check north
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY -1);
			if (pTestTile == nullptr)
			{
				int x = 9;
			}
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			bool pPass = !(pTestTile->GetIfPassable());
			bool pOcc = !(pTestTile->GetIfOccupied());
			if (iter == closedList.end() && !(pTestTile->GetIfPassable()) && !(pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY -1);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosY + 1 < pTM->GetNumColumns()) // check south
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY + 1);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX, n->pTile->GetPosition().nPosY +1);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosX -1 >= 0) // check West
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX - 1, n->pTile->GetPosition().nPosY);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX -1, n->pTile->GetPosition().nPosY);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}
		if (n->pTile->GetPosition().nPosX +1 < pTM->GetNumRows()) // check east
		{
			CTile* pTestTile = pTM->GetTile(n->pTile->GetPosition().nPosX + 1, n->pTile->GetPosition().nPosY);
			std::list<ASNode*>::iterator iter;
			iter = std::find_if(closedList.begin(), closedList.end(), [&pTestTile](const ASNode* node)
			{
				return (node->pTile == pTestTile);
			});
			if (iter == closedList.end() && (!pTestTile->GetIfPassable()) && (!pTestTile->GetIfOccupied()))
			{
				iter = std::find_if(openList.begin(), openList.end(), [&pTestTile](const ASNode* node)
				{
					return (node->pTile == pTestTile);
				});
				if (iter != openList.end()) // it is in the open list, so check if it's cheaper to go that way
				{
					(*iter)->parent = n;
					(*iter)->nF = pTestTile->GetAPCost() + n->nH;
				}
				else // it's not.
				{
					ASNode* newNode = new ASNode();
					newNode->pTile = pTM->GetTile(n->pTile->GetPosition().nPosX + 1, n->pTile->GetPosition().nPosY);
					if (newNode->pTile->GetPosition().nPosY == 400 || newNode->pTile->GetPosition().nPosX < -5000)
					{
						int x = 9;
					}
					newNode->parent = n;
					newNode->nCost = newNode->parent->nCost + newNode->pTile->GetAPCost();
					int xDist = targetTile->GetPosition().nPosX - newNode->pTile->GetPosition().nPosX;
					int yDist = targetTile->GetPosition().nPosY - newNode->pTile->GetPosition().nPosY;
					newNode->nH = (int)(sqrt(double(xDist * xDist) + double(yDist * yDist) * nEstimatedTileCost));
					newNode->nF = newNode->pTile->GetAPCost() + newNode->nH;
					openList.push_back(newNode);
				}
			}
		}

		// find which one in the open list has the cheapest cost and make it our active tile, and add it to the closed list
		ASNode* lowestF = nullptr;
		int nLowestF = INT_MAX;
		std::list<ASNode*>::iterator listIter;
		for (listIter = openList.begin(); listIter != openList.end(); ++listIter)
		{
			if ((*listIter)->nF < nLowestF)
			{
				nLowestF = (*listIter)->nF;
				lowestF = (*listIter);
			}
		}

		if (lowestF == nullptr)
			break;
		openList.remove(lowestF);
		closedList.push_back(lowestF);

		// if the lowest cost is our target tile, we're done!
		if (lowestF->pTile == targetTile)
		{
			break;
		}
		n = lowestF;
		safeCheck++;
	}

	// if we didnt find anything, get out of here
	if (closedList.size() == 0)
	{
		return false;
	}

	// Go through the list of found tiles and add them to our waypoints of our path
	ASNode* nNode = closedList.back();
	safeCheck = 0;
	while (nNode->parent != nullptr && (safeCheck < 5000))
	{
		m_vWaypoints.push_back(nNode->pTile);
		nNode = nNode->parent;
	}

	// CLEANUP. delete all memory we made
	std::list<ASNode*>::iterator listIter;
	for (listIter = openList.begin(); listIter != openList.end(); ++listIter)
	{
		delete (*listIter);
	}
	for (listIter = closedList.begin(); listIter != closedList.end(); ++listIter)
	{
		delete (*listIter);
	}

	// return that it worked fine
	return true;
}

void CGameplayState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if (pDI->KeyPressed(DIK_W))
	{
		Input(INPUT_CAM_UP);
	}
	else if (pDI->KeyPressed(DIK_S))
	{
		Input(INPUT_CAM_DOWN);
	}
	else if (pDI->KeyPressed(DIK_A))
	{
		Input(INPUT_CAM_LEFT);
	}
	else if (pDI->KeyPressed(DIK_D))
	{
		Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementX() < -nMouseSensitivity)
	{
		Input(INPUT_CAM_LEFT);
	}
	else if (pDI->MouseMovementX() > nMouseSensitivity)
	{
		Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementY() < -nMouseSensitivity)
	{
		Input(INPUT_CAM_UP);
	}
	else if (pDI->MouseMovementY() > nMouseSensitivity)
	{
		Input(INPUT_CAM_DOWN);
	}

	if (pDI->KeyPressed(DIK_UP))
		Input(INPUT_UP);
	else if (pDI->KeyPressed(DIK_LEFT))
		Input(INPUT_LEFT);
	else if (pDI->KeyPressed(DIK_RIGHT))
		Input(INPUT_RIGHT);
	else if (pDI->KeyPressed(DIK_DOWN))
		Input(INPUT_DOWN);
	else if (pDI->KeyPressed(DIK_RETURN))
		Input(INPUT_ACCEPT);
	else if (pDI->KeyPressed(DIK_Z))
		Input(INPUT_CANCEL);
	else if (pDI->KeyPressed(DIK_T)) // DEBUG DELETE SELECTED UNIT
	{
		if (m_pSelectedUnit)
		{
			CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(m_pSelectedUnit);
			CMessageSystem::GetInstance()->SendMessageW(pMsg);

			Input(INPUT_CANCEL);
		}
	}
	else if (pDI->KeyPressed(DIK_R))
	{
		CAddResourceMessage* pMsg = new CAddResourceMessage(TT_MINE, 0);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	else if (pDI->KeyPressed(DIK_Y))
	{
		SnapToUnit(CGameManager::GetInstance()->GetChampion(0));
	}
	else if (pDI->KeyPressed(DIK_U))
	{
		SnapToUnit(CGameManager::GetInstance()->GetChampion(1));
	}
	else if (pDI->KeyPressed(DIK_I))
	{
		CGameManager* pGM = CGameManager::GetInstance();
		int x = 9;
	}
	// Testing Particle Rendering
	CParticleManager::GetInstance()->Update(fElapsedTime);
	CObjectManager::GetInstance()->UpdateAllObjects(fElapsedTime);
}

void CGameplayState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);
	CTileManager::GetInstance()->Render();
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	// render the waypoints?
	if (m_pSelectedUnit != nullptr)
	{
		int nTilesCanMove = m_pSelectedUnit->GetSpeed() - m_pSelectedUnit->GetTilesMoved();
		int nAPCost = 0;
		int r = 0;
		int g = 255;
		int b = 0;

		for (int i = m_vWaypoints.size() - 1; i >= 0; --i)
		{
			nAPCost += m_vWaypoints[i]->GetAPCost();
			nTilesCanMove--;
			CPlayer* pPlayer = CGameManager::GetInstance()->GetCurrentPlayer();
			if (nAPCost > CGameManager::GetInstance()->GetCurrentPlayer()->GetAP())
			{
				r = 255;
				g = 0;
			}
			if (nTilesCanMove < 0)
			{
				r = 255;
				g = 0;
			}
			RECT tileRect = { m_vWaypoints[i]->GetPosition().nPosX * nFakeTileWidth - GetCamOffsetX(), 
				m_vWaypoints[i]->GetPosition().nPosY * nFakeTileHeight - GetCamOffsetY(),  
				nFakeTileWidth, nFakeTileHeight};
		//	CGraphicsManager::GetInstance()->DrawWireframeRect(tileRect, r, g, b);
			CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("wphighlight")),
				tileRect.left, tileRect.top, 1.0f, 1.0f, (RECT*)0, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(120,r, g, b));
		}
	}
	CObjectManager::GetInstance()->RenderAllObjects();

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();


	//Render the map

	// Testing particle rendering
	CParticleManager::GetInstance()->Render();

	// DEBUG STUFF
	CPlayer* pDebugPlayer = CGameManager::GetInstance()->GetPlayer(0);
	std::wostringstream oss;
	oss << "Player: " << pDebugPlayer->GetPlayerID() << ", AP: " << pDebugPlayer->GetAP() << ", POP: "
		<< pDebugPlayer->GetPopCap() << ", WOOD: " << pDebugPlayer->GetWood() << ", METAL: " << pDebugPlayer->GetMetal() << '\n';
	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 0, 255, 255, 255);

	oss.str(_T(""));
	oss << "Selected Unit: ";
	if (m_pSelectedUnit != nullptr)
	{
		oss << m_pSelectedUnit->GetType() << ", X: " << m_pSelectedUnit->GetPos().nPosX << ", Y: " << 
			m_pSelectedUnit->GetPos().nPosY << ", HP: " << m_pSelectedUnit->GetHP();
	}
	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)oss.str().c_str(), 0, 350, 255, 255, 255);


	// selection cursor
	RECT selectRect = { m_SelectionPos.nPosX * nFakeTileWidth - GetCamOffsetX(), m_SelectionPos.nPosY * nFakeTileHeight - GetCamOffsetY(),  
		nFakeTileWidth, nFakeTileHeight};
	if (m_bIsMoving)
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 0, 255, 0);
	else
		CGraphicsManager::GetInstance()->DrawWireframeRect(selectRect, 255, 255, 255);

}
