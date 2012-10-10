#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CHero : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CHero(void);
	~CHero(void);
	void Render(void);
};

