#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CIceblock : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CIceblock(void);
	~CIceblock(void);
	void Render(void);
};

