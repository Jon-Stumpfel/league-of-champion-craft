#pragma once

#include "IGameState.h"


class CGameOverState : public IGameState
{

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CGameOverState* GetInstance();

private:

	
	CGameOverState(void);
	virtual ~CGameOverState(void);
	CGameOverState(const CGameOverState&);
	CGameOverState* operator=( CGameOverState& );

	static CGameOverState* s_Instance;

	Vec2D m_sCursorPos;

};

