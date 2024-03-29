#pragma once

#include "igamestate.h"
#include "LevelSelectState.h"
class CMainMenuState : public IGameState
{

public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	static CMainMenuState* GetInstance();

private:
	int selected;
	int swordid;
	int blueguyid;
	int redguyid;
	CMainMenuState(void);
	virtual ~CMainMenuState(void);
	CMainMenuState(const CMainMenuState&);
	CMainMenuState* operator=( CMainMenuState& );
	CBitmapFont* m_pBitmapFont;
//	static CMainMenuState* s_Instance;

	Vec2D m_sCursorPos;
};

