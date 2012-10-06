#pragma once

#include "igamestate.h"

class CCreditsState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CCreditsState* GetInstance();

private:

	
	CCreditsState(void);
	virtual ~CCreditsState(void);
	CCreditsState(const CCreditsState&);
	CCreditsState* operator=( CCreditsState& );

//	static CCreditsState* s_Instance;

};

