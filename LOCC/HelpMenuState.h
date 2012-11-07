#pragma once
#include "BitmapFont.h"
#include "igamestate.h"

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
	int m_nswitchscreen;
	int m_nScrollID;
	int m_nTileHelpID;
	int m_nUnitHelpID;
	int m_nGameplayHelpID;
	int m_nArcadeHelpID;
	int m_nXboxHelpID;
	int m_nKeyBoardHelpID;
	int m_nArrowID;
	CHelpMenuState(void);
	virtual ~CHelpMenuState(void);
	CHelpMenuState(const CHelpMenuState&);
	CHelpMenuState* operator=( CHelpMenuState& );
	CBitmapFont* m_pBitmapfont;

	//static CHelpMenuState* s_Instance;

};

