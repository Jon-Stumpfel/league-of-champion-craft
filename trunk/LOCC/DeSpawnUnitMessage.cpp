#include "StdAfx.h"
#include "DeSpawnUnitMessage.h"



CDespawnUnitMessage::CDespawnUnitMessage( CUnit* pUnit ) : CMessage(MSG_DESPAWNUNIT)
{
	m_pUnitToDespawn = pUnit;
	pUnit->AddRef();
}

CDespawnUnitMessage::~CDespawnUnitMessage(void)
{
	m_pUnitToDespawn->Release();
}
