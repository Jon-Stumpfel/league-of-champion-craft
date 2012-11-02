#pragma once
#include "igamestate.h"

class CGameModeState : public IGameState
{
public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	static CGameModeState* GetInstance();

private:

	int m_nSelected;

	CGameModeState(void);
	virtual ~CGameModeState(void);
	CGameModeState(const CGameModeState&);
	CGameModeState* operator=( CGameModeState& );
};

