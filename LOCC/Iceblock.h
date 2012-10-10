#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CIceblock : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:
	void SetAnimType(ANIM_TYPE temptype) { m_sAnimStruct->animationType = temptype;}
	void SetUnitAnim(UnitAnimation* tempanim) {m_sAnimStruct = tempanim;}
	UnitAnimation* GetUnitAnim() {return m_sAnimStruct;}
	CIceblock(void);
	~CIceblock(void);
	void Render(void);
};

