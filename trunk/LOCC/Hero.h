#pragma once

#include "unit.h"
#include "GraphicsManager.h"
#include "Ability.h"
class CHero : public CUnit
{
private:
	std::vector<CAbility*> m_vSpells;
public:
	void GiveSpell(SPELL_TYPE type);
	CAbility* GetSpell(int i) { return m_vSpells[i];}
	unsigned int GetNumSpells( void ) { return m_vSpells.size(); }
	CHero(void);
	~CHero(void);
	void Render(void);
};

