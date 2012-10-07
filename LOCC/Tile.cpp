#include "StdAfx.h"
#include "Tile.h"
#include <assert.h>


//{ TS_FROZEN, TS_RESOURCETILE, TS_OCCUPIED, TS_CAPTURING, TS_CAPTURED, TS_IS_DEAD, TS_ISPASSABLE};
CTile::CTile(void)
{	
	m_eTType=TT_PLAINS;
	m_ucStatus=0;
	m_nPlayerID=0;
	m_sPos= Vec2D();
}

CTile::CTile( int eTile, bool bResouceTile, Vec2D sPos )
{
	m_eTType=eTile;
	m_ucStatus=0;
	if (bResouceTile==true)
		SetStatus(TS_RESOURCETILE, true);

	m_nPlayerID=0;
	m_sPos= Vec2D();
}

CTile::~CTile(void)
{

}

void CTile::SetStatus(unsigned char TileStatus, bool On_or_Off)
{
	
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
	assert(TileStatus>TS_ISPASSABLE&&"TileStatus out of range");
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

bool CTile::GetIfFrozen		(void)
{
	if(m_ucStatus & (1<<TS_FROZEN))
		return true;
	else 
		return false;                    
}

void CTile::SetIfFrozen	(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_FROZEN);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_FROZEN);
	}
}

bool CTile::GetIfResoruce	(void)
{
	return true;
}

void CTile::SetIfResoruce	(bool OnOff)
{

}

bool CTile::GetIfOccupied	(void)
{
	return true;
}

void CTile::SetIfOccupied	(bool OnOff)
{

}

bool CTile::GetIfCapturing	(void)
{
	return true;
}

void CTile::SetIfCapturing	(bool OnOff)
{

}