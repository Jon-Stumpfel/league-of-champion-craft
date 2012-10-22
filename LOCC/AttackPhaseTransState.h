#pragma once
#include "igamestate.h"
class CAttackPhaseTransState :
	public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CAttackPhaseTransState* GetInstance();

private:
	CAttackPhaseTransState(void);
	virtual ~CAttackPhaseTransState(void);
	CAttackPhaseTransState(const CAttackPhaseTransState&);
	CAttackPhaseTransState* operator=( CAttackPhaseTransState& );
	int m_MovingL;
	int m_MovingR;
	float m_fTimer;

};

