#pragma once
#include "igamestate.h"
class CMovetPhaseTransState:
	public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CMovetPhaseTransState* GetInstance();

private:
	CMovetPhaseTransState(void);
	virtual ~CMovetPhaseTransState(void);
	CMovetPhaseTransState(const CMovetPhaseTransState&);
	CMovetPhaseTransState* operator=( CMovetPhaseTransState& );
	int m_MovingUp;
	float m_fTimer;


};

