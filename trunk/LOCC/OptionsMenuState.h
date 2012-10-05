#pragma once

#include "igamestate.h"

class COptionsMenuState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static COptionsMenuState* GetInstance();

private:

	
	COptionsMenuState(void);
	virtual ~COptionsMenuState(void);
	COptionsMenuState(const COptionsMenuState&);
	COptionsMenuState& operator=(const COptionsMenuState&);

	static COptionsMenuState* s_Instance;

	Vec2D m_sCursorPos;

};

