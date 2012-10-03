#pragma once

#include "igamestate.h"
#include "GameObject.h"

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

	Vec2D m_sCursorPos;

};

