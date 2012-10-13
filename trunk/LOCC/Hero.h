#pragma once

#include "unit.h"
#include "GraphicsManager.h"
#include "Ability.h"
class CHero : public CUnit
{
private:
	std::vector<CAbility*> m_vSpells;
public:

	CAbility* GetSpell(int i) { return m_vSpells[i];}
	CHero(void);
	~CHero(void);
	void Render(void);
};

