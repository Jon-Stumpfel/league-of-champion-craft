#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CSwordsman : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:
	void SetAnimType(ANIM_TYPE temptype) { m_sAnimStruct->animationType = temptype;}
	void SetUnitAnim(UnitAnimation* tempanim) {m_sAnimStruct = tempanim;}
	UnitAnimation* GetUnitAnim() {return m_sAnimStruct;}
	CSwordsman(void);
	~CSwordsman(void);
	void Render(void);
};

