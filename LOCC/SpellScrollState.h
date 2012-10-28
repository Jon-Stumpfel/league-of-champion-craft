#pragma once

#include "igamestate.h"

class CAbility;
class CHero;

class CSpellScrollState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	void Initialize( void );

	static CSpellScrollState* GetInstance(void);

private:

	CSpellScrollState(void);
	~CSpellScrollState(void);
	CSpellScrollState(const CSpellScrollState&);
	CSpellScrollState& operator=(const CSpellScrollState&);

	//static CSpellScrollState* s_Instance;

	std::vector< std::pair< std::string, int > > m_vIDs;

	std::vector< CAbility* > m_vElemental;
	std::vector< CAbility* > m_vPhysical;
	std::vector< CAbility* > m_vSupport;

	int m_nSelected;
	int m_nSelectedAbility;
	bool m_bTreeSelect;

	CHero* m_pCustomer;
	int m_nSwap;
	int m_nExp;

};

