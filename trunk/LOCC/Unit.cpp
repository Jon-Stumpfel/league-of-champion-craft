#include "StdAfx.h"
#include "Unit.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "Tile.h"
CUnit::CUnit(UNIT_TYPE type) : m_eType(type)
{
	m_nTilesMoved = 0;
}


CUnit::~CUnit(void)
{
}

void CUnit::AddWaypoint(CTile* pTile)
{
	if (pTile != nullptr)
		m_vWaypoints.push_back(pTile);
}

// Just used for checking if two numbers are close enough together for waypoint moving. Used to be
// 5 pixels, but left some weird off. Now it's just 0, so it's a relic function but it doesn't hurt leaving it
static bool CloseEnough(int n1, int n2)
{
	if (abs(n1 - n2) == 0)
		return true;
	else
		return false;
}
void CUnit::Update(float fElapsedTime)
{
	// move me along the route!
	// If we have any waypoints in our list of waypoints added in from GameplayState::MoveToTile, then we need to move across them
	if (m_vWaypoints.size() != 0)
	{
		// Set the tile we are moving off of's occupied to false.
		CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY)->SetIfOccupied(false);

		// Find out how we need to move, pixel wise, to our intended target.
		int nNewPixelPosX = m_vWaypoints.back()->GetPosition().nPosX * nFakeTileWidth;
		int nNewPixelPosY = m_vWaypoints.back()->GetPosition().nPosY * nFakeTileHeight;

		// Moves our posX or posY over time so that our pixel position matches up with the pixel position
		// of the first waypoint
		if (m_sWorldPos.nPosX < nNewPixelPosX)
		{
			m_sWorldPos.nPosX += 2;
		}
		else if (m_sWorldPos.nPosX > nNewPixelPosX)
		{
			m_sWorldPos.nPosX -= 2;
		}
		if (m_sWorldPos.nPosY < nNewPixelPosY)
		{
			m_sWorldPos.nPosY += 2;
		}
		else if (m_sWorldPos.nPosY > nNewPixelPosY)
		{
			m_sWorldPos.nPosY -= 2;
		}

		// If we're "close enough" to the pixel position (i.e. our unit's pixel position and the tile's pixel position match)
		// then we are considered "on" that tile. We've made it!
		// Set our logical position to that tile's position, cause we're on it, and then set that tile to occupied.
		// Progress the number of tiles we have moved by 1
		// Remove that tile from our waypoint, and then if we've moved our speed, clear the rest of the waypoints 
		// because we can't move any further.
		if (CloseEnough((m_sWorldPos.nPosX ) ,(m_vWaypoints.back()->GetPosition().nPosX *nFakeTileWidth))&&
			CloseEnough((m_sWorldPos.nPosY ),(m_vWaypoints.back()->GetPosition().nPosY *nFakeTileHeight)))
		{
			m_sGamePos = m_vWaypoints.back()->GetPosition();
			CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY)->SetIfOccupied(true);
			m_nTilesMoved++;

			m_vWaypoints.pop_back();
			if (m_nTilesMoved == m_nSpeed)
			{
				m_vWaypoints.clear();
			}
		}
	}
}

void CUnit::Render(void)
{


}

// Sets our logical position to the passed in X/Y and sets that tile to occupied. Sets our previous
// tile to no longer occupied, and sets our pixel position to equal that new tile
void CUnit::SetPos(int posX, int posY)
{
	m_sWorldPos.nPosX = posX * nFakeTileWidth;
	m_sWorldPos.nPosY = posY * nFakeTileHeight;
	CTile* pTile = CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY);
	if (pTile != nullptr)
		pTile->SetIfOccupied(false);
	m_sGamePos.nPosX = posX;
	m_sGamePos.nPosY = posY;
	pTile = CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY);
	if (pTile != nullptr)
		pTile->SetIfOccupied(true);
}
void CUnit::SetPos(Vec2D pos)
{
	SetPos(pos.nPosX, pos.nPosY);
}