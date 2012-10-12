#pragma once
#include "igamestate.h"
class CPauseState : public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CPauseState* GetInstance();

private:
	CPauseState(void);
	virtual ~CPauseState(void);
	CPauseState(const CPauseState&);
	CPauseState* operator=( CPauseState& );


	int m_nVerticalChoice;
};
