#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CArcher : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CArcher(void);
	~CArcher(void);
	void Render(void);
};

