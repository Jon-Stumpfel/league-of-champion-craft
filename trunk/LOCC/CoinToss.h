#pragma once
#include "StdAfx.h"
#include "IGameState.h"
#include <time.h>

class CCoinToss:
	public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CCoinToss* GetInstance();

private:
	CCoinToss(void);
	~CCoinToss(void);
	CCoinToss(const CCoinToss&);
	CCoinToss* operator=( CCoinToss& );
	int m_nCoinArc;
	UnitAnimation* m_UAnonsense;
	int m_nChosenplayer;
	float m_fTimer;
	bool m_bGoDown;
	bool m_bStop;
};

