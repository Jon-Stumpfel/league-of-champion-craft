#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CArcher : public CUnit
{
	UnitAnimation* tempanimstruct;
public:

	CArcher(void);
	~CArcher(void);
	void Render(void);
};

