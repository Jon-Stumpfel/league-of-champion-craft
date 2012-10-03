#pragma once

#include "igamestate.h"
#include "GameObject.h"

class CHelpMenuState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CHelpMenuState* GetInstance();

private:

	
	CHelpMenuState(void);
	virtual ~CHelpMenuState(void);
	CHelpMenuState(const CHelpMenuState&);
	CHelpMenuState* operator=( CHelpMenuState& );

	static CHelpMenuState* s_Instance;

};

