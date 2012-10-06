#include "StdAfx.h"
#include "Tile.h"
#include <assert.h>

CTile::CTile(void)
{	
	m_eTType=PLAINS;
	m_ucStatus=0;
	m_nPlayerID=0;
	m_sPos= Vec2D();
}

CTile::CTile( int eTile, bool bResouceTile, Vec2D sPos )
{
	m_eTType=eTile;
	m_ucStatus=0;
	if (bResouceTile==true);
		SetStatus(RESOURCETILE, true);

	m_nPlayerID=0;
	m_sPos= Vec2D();
}

CTile::~CTile(void)
{

}

void CTile::SetStatus(unsigned char TileStatus, bool On_or_Off)
{
	//FROZEN, RESOURCETILE, OCCUPIED, CAPTURING, CAPTURED, IS_DEAD
	if (On_or_Off==true)
	{
		m_ucStatus |= (1<<TileStatus);
	}
	if (On_or_Off==false)
	{
		m_ucStatus &= ~(1<<TileStatus);
	}

}

bool CTile::IsStatus(unsigned char TileStatus, bool On_or_Off)
{
	//FROZEN, RESOURCETILE, OCCUPIED, CAPTURING, CAPTURED, IS_DEAD,ISPASSABLE
		assert(TileStatus<ISPASSABLE&&"TileStatus out of range");
		return false;
	if (On_or_Off==true)
	{
		if(m_ucStatus & (1<<TileStatus))
			return true;
		else 
			return false;
	}
	if (On_or_Off==false)
	{
		if(m_ucStatus & (1<<TileStatus))
			return false;
		else 
			return true;
	}
}

void CTile::GetIfFrozen		(void)
	{

	}

bool CTile::SetIfFrozen		(bool OnOff)
	{
		return true;
	}
		
void CTile::GetIfResoruce	(void)
	{


	}

bool CTile::SetIfResoruce	(bool OnOff)
	{
		return true;

	}

void CTile::GetIfOccupied	(void)
	{

	}

bool CTile::SetIfOccupied	(bool OnOff)
	{
		return true;
	}

void CTile::GetIfCaputring	(void)
	{

	}

bool CTile::SetIfCaputring	(bool OnOff)
	{
		return true;
	}
