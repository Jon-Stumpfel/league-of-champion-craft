#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CCavalry : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CCavalry(void);
	~CCavalry(void);
	void Render(void);
};

