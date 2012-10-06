#pragma once
#include "Message.h"
#include "Unit.h"
class CDespawnUnitMessage : public CMessage
{

private:

	CUnit* m_pUnitToDespawn;

public:

	CUnit* GetUnit(void) { return m_pUnitToDespawn;}

	CDespawnUnitMessage( CUnit* pUnit );
	~CDespawnUnitMessage(void);

};