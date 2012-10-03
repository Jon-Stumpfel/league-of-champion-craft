#pragma once

#include "igamestate.h"

class CSpellScrollState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CSpellScrollState* GetInstance(void);

private:

	CSpellScrollState(void);
	~CSpellScrollState(void);
	CSpellScrollState(const CSpellScrollState&);
	CSpellScrollState& operator=(const CSpellScrollState&);

	static CSpellScrollState* s_Instance;

	std::vector< std::pair< std::string, int > > m_vIDs;

};

