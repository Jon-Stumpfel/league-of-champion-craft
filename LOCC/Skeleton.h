#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CSkeleton : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CSkeleton(void);
	~CSkeleton(void);
	void Render(void);
};

