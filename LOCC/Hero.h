#pragma once

#include "unit.h"
#include "GraphicsManager.h"
#include "Ability.h"
class CHero : public CUnit
{
private:
	std::vector<CAbility*> m_vSpells;
	std::vector<CAbility*> m_vBoughtSpells;

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
	bool SearchSpells( CAbility* ability );
	void SwapSpell(CAbility* ability, int index) { m_vSpells[index] = ability; }
	void SpellBought( CAbility* ability ) { m_vBoughtSpells.push_back(ability); }
	int GetNumBought( void ) { return (int)m_vBoughtSpells.size(); }
	CAbility* GetBought( int i ) { return m_vBoughtSpells[i]; }
	bool IfBought( CAbility* ability );
	unsigned int GetNumSpells( void ) { return m_vSpells.size(); }
	CHero(void);
	~CHero(void);
	void Render(void);

	static int HasSpell(lua_State* L);
	static int GetSpellCooldown(lua_State* L);
};

