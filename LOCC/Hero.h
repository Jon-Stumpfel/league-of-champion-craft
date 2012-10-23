#pragma once

#include "unit.h"
#include "GraphicsManager.h"
#include "Ability.h"
class CHero : public CUnit
{
private:
	std::vector<CAbility*> m_vSpells;
	int m_ncooldown[4];
public:
	//Get the cooldown left for a select spell "i" in the cooldown array
	int GetCooldown( int i)    {return m_ncooldown[i];};
	//set the cooldown amount for a select spell "i" in the cooldown array
	void SetCooldown(int i, int amount) {m_ncooldown[i]=amount;};
	//updates the cooldown array
	void ChillCooldown(void);

	void GiveSpell(SPELL_TYPE type);
	CAbility* GetSpell(int i);
	unsigned int GetNumSpells( void ) { return m_vSpells.size(); }
	CHero(void);
	~CHero(void);
	void Render(void);
};

