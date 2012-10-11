#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CHero : public CUnit
{
public:
	void SetAnimType(ANIM_TYPE temptype) { m_sAnimStruct->animationType = temptype;}
	void SetUnitAnim(UnitAnimation* tempanim) {m_sAnimStruct = tempanim;}
	UnitAnimation* GetUnitAnim() {return m_sAnimStruct;}
	CHero(void);
	~CHero(void);
	void Render(void);
};

