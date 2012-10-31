#include "StdAfx.h"
#include "Tile.h"
#include <assert.h>


//{ TT_PLAINS, TT_FOREST, TT_MOUNTAINS, TT_WATER, TT_FARM, TT_MILL, TT_MINE, TT_CASTLE };
//{ TS_FROZEN, TS_RESOURCETILE, TS_OCCUPIED, TS_CAPTURING, TS_CAPTURED, TS_IS_DEAD, TS_ISImpassable};

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
	//KEEP AN EYE ON THIS!!!
	assert(TileStatus>TS_ISIMPASSABLE&&"TileStatus out of range");
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

bool CTile::GetIfFrozen			(void)
{
	if(m_ucStatus & (1<<TS_FROZEN))
		return true;
	else 
		return false;                    
}
void CTile::SetIfFrozen			(bool OnOff)
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

bool CTile::GetIfOccupied		(void)
{
	if(m_ucStatus & (1<<TS_OCCUPIED))
		return true;
	else 
		return false;    
}
void CTile::SetIfOccupied		(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_OCCUPIED);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_OCCUPIED);
	}
}

bool CTile::GetIfCapturing		(void)
{
	if(m_ucStatus & (1<<TS_CAPTURING))
		return true;
	else 
		return false; 
}
void CTile::SetIfCapturing		(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_CAPTURING);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_CAPTURING);
	}
}

bool CTile::GetIfCaptured		(void)
{
	if(m_ucStatus & (1<<TS_CAPTURED))
		return true;
	else 
		return false;    
}
void CTile::SetIfCaptured		(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_CAPTURED);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_CAPTURED);
	}
}

bool CTile::GetIfResourceTile	(void)
{
	if(m_ucStatus & (1<<TS_RESOURCETILE))
		return true;
	else 
		return false;   
}
void CTile::SetIfResourceTile	(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_RESOURCETILE);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_RESOURCETILE);
	}
}

bool CTile::GetIfDeadTile		(void)
{
	if(m_ucStatus & (1<<TS_IS_DEAD))
		return true;
	else 
		return false;  
}
void CTile::SetIfDeadTile		(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_IS_DEAD);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_IS_DEAD);
	}
}

bool CTile::GetIfImpassable		(void)
{
	if(m_ucStatus & (1<<TS_ISIMPASSABLE))
		return true;
	else 
		return false; 
}
void  CTile::SetIfImpassable		(bool OnOff)
{
	if (OnOff==true)
	{
		m_ucStatus |= (1<<TS_ISIMPASSABLE);
	}
	if (OnOff==false)
	{
		m_ucStatus &= ~(1<<TS_ISIMPASSABLE);
	}
}

int CTile::GetAPCost()
{
	switch (m_eTType)
	{
	case TT_MOUNTAINS:
		{
			if (this->GetIfFrozen())
				return 4;
			else
				return 3;
		}
	case TT_FOREST:
		{
			if (this->GetIfFrozen())
				return 3;
			else
				return 2;
		}
	case TT_PLAINS:
		{
			if (this->GetIfFrozen())
				return 2;
			else
				return 1;
		}
	}
	
	if (m_eTType>TT_WATER)
		if (this->GetIfFrozen())
				return  m_eTType+2-TT_FARM;
			else
				return  m_eTType+1-TT_FARM;

	if (m_eTType==TT_WATER)
		if(GetIfImpassable()==false)
		return 1;
	return -1;
}

bool CTile::operator==(const CTile& rhs)
{
	return ((m_sPos.nPosX == rhs.m_sPos.nPosX) && (m_sPos.nPosY == rhs.m_sPos.nPosY));
}