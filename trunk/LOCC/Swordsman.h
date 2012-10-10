#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CSwordsman : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CSwordsman(void);
	~CSwordsman(void);
	void Render(void);
};

