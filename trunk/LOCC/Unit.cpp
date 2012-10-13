#include "StdAfx.h"
#include "Unit.h"
#include "GraphicsManager.h"
#include "TileManager.h"
#include "Archer.h"
#include "Tile.h"
#include "DeSpawnUnitMessage.h"
#include "MessageSystem.h"
CUnit::CUnit(UNIT_TYPE type) : m_eType(type)
{
	m_nTilesMoved = 0;
	CAbility* pAbility = new CAbility();
	pAbility->m_nAPCost = 0;
	pAbility->m_bIsMove = true;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_szInterfaceIcon = TSTRING(_T("moveicon"));
	m_vAbilities.push_back(pAbility);

	if (m_eType != UT_ARCHER)
	{
		
	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_bIsMove = false;
	pAbility->m_bIsAttack = true;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nPhase = GP_ATTACK;
	pAbility->m_nRange = 1;
	pAbility->m_nCooldown = 0;
	pAbility->m_vPattern.push_back(Vec2D(-1, 0));
	pAbility->m_vPattern.push_back(Vec2D(1, 0));
	pAbility->m_vPattern.push_back(Vec2D(0, -1));
	pAbility->m_vPattern.push_back(Vec2D(0, 1));
	pAbility->m_szInterfaceIcon = TSTRING(_T("meleeattackicon"));
	}
	else
	{
		pAbility = new CAbility();
		pAbility->m_nAPCost = 1;
		pAbility->m_bIsMove = false;
		pAbility->m_bIsAttack = true;
		pAbility->m_nNumTargets = 1;
		pAbility->m_nPhase = GP_ATTACK;
		pAbility->m_nRange = 2;
		pAbility->m_nCooldown = 0;
		pAbility->m_vPattern.push_back(Vec2D(-1, 0));
		pAbility->m_vPattern.push_back(Vec2D(1, 0));
		pAbility->m_vPattern.push_back(Vec2D(0, -1));
		pAbility->m_vPattern.push_back(Vec2D(0, 1));
		pAbility->m_vPattern.push_back(Vec2D(-2, 0));
		pAbility->m_vPattern.push_back(Vec2D(2, 0));
		pAbility->m_vPattern.push_back(Vec2D(0, -2));
		pAbility->m_vPattern.push_back(Vec2D(0, 2));
		pAbility->m_vPattern.push_back(Vec2D(-1, -1));
		pAbility->m_vPattern.push_back(Vec2D(1, 1));
		pAbility->m_vPattern.push_back(Vec2D(1, -1));
		pAbility->m_vPattern.push_back(Vec2D(-1, 1));
		pAbility->m_szInterfaceIcon = TSTRING(_T("rangeattackicon"));

	}
	m_vAbilities.push_back(pAbility);

	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = m_eType;
}

int CUnit::GetPortraitID(void)
{
	switch(m_eType)
	{
	case UT_ARCHER:
		return CGraphicsManager::GetInstance()->GetID(_T("archerportrait"));
		break;
	case UT_CASTLE:
		return CGraphicsManager::GetInstance()->GetID(_T("castleportrait"));
		break;
	case UT_CAVALRY:
		return CGraphicsManager::GetInstance()->GetID(_T("cavalryportrait"));
		break;
	case UT_HERO:
		return CGraphicsManager::GetInstance()->GetID(_T("heroportrait"));
		break;
	case UT_ICEBLOCK:
		return CGraphicsManager::GetInstance()->GetID(_T("iceblockportrait"));
		break;
	case UT_SKELETON:
		return CGraphicsManager::GetInstance()->GetID(_T("skeletonportrait"));
		break;
	case UT_SWORDSMAN:
		return CGraphicsManager::GetInstance()->GetID(_T("swordsmanportrait"));
		break;
	}
	return -1;
}

CUnit::~CUnit(void)
{
	for (decltype(m_vAbilities.size()) i =0; i < m_vAbilities.size(); ++i)
		delete m_vAbilities[i];
	delete m_sAnimStruct;
}

void CUnit::AddWaypoint(CTile* pTile)
{
	if (pTile != nullptr)
		m_vWaypoints.push_back(pTile);
}
CAbility* CUnit::GetAbility(int index)
{
	if ((decltype(m_vAbilities.size()))index < m_vAbilities.size())
		return m_vAbilities[index];
	else
		return nullptr;
}

// Just used for checking if two numbers are close enough together for waypoint moving. Used to be
// 5 pixels, but left some weird off. Now it's just 0, so it's a relic function but it doesn't hurt leaving it
static bool CloseEnough(int n1, int n2)
{
	if (abs(n1 - n2) < 2)
		return true;
	else
		return false;
}
void CUnit::Update(float fElapsedTime)
{
	if (m_nHP <= 0)
	{
		CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(this);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	// move me along the route!
	// If we have any waypoints in our list of waypoints added in from GameplayState::MoveToTile, then we need to move across them

			if (m_nFacing == 0)
				m_sAnimStruct->animationType = AT_WALK_W; // S
			else if (m_nFacing == 1)
				m_sAnimStruct->animationType = AT_WALK_W; // N
			else if (m_nFacing == 2)
				m_sAnimStruct->animationType = AT_WALK_W; // E
			else if (m_nFacing == 3)
				m_sAnimStruct->animationType = AT_WALK_W; // W
	if (m_vWaypoints.size() != 0)
	{
		// Set the tile we are moving off of's occupied to false.
		CTileManager::GetInstance()->GetTile(m_sGamePos.nPosX, m_sGamePos.nPosY)->SetIfOccupied(false);

		int xDistance = m_sGamePos.nPosX - m_vWaypoints.back()->GetPosition().nPosX;
		int yDistance = m_sGamePos.nPosY - m_vWaypoints.back()->GetPosition().nPosY;
			if (yDistance == -1)
				m_nFacing = 0;
			else if (yDistance == 1)
				m_nFacing = 1;
			else if (xDistance == -1)
				m_nFacing = 2;
			else if (xDistance == 1)
				m_nFacing = 3;



		// Find out how we need to move, pixel wise, to our intended target.
		float x = float((nFakeTileWidth / 2 * m_vWaypoints.back()->GetPosition().nPosX ) - (nFakeTileHeight / 2 * m_vWaypoints.back()->GetPosition().nPosY));
		float y = float((nFakeTileWidth / 2 * m_vWaypoints.back()->GetPosition().nPosX ) + (nFakeTileHeight  / 2 * m_vWaypoints.back()->GetPosition().nPosY));
		float nNewPixelPosX = x;//m_vWaypoints.back()->GetPosition().nPosX * nFakeTileWidth;
		float nNewPixelPosY = y;//m_vWaypoints.back()->GetPosition().nPosY * nFakeTileHeight;

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
		if (CloseEnough((m_sWorldPos.nPosX ) ,((int)x))&&
			CloseEnough((m_sWorldPos.nPosY ),((int)y)))
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
	int x = (nFakeTileWidth / 2 * posX ) - (nFakeTileHeight / 2 * posY);
	int y = (nFakeTileWidth / 2 *posX ) + (nFakeTileHeight  / 2 * posY);
	m_sWorldPos.nPosX = x;//posX * nFakeTileWidth;
	m_sWorldPos.nPosY = y;//posY * nFakeTileHeight;
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