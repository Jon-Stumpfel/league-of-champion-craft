#pragma once
#include "StateStack.h"
#include "IGameState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "BitmapFont.h"
#include "GameManager.h"
class CGameOverState : public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	static CGameOverState* GetInstance();
	void SetPlayer(int temp) {Player = temp;}
	void SetAI(bool ai)  {AI = ai;}
private:
	int Player;
	bool AI;
	CGameOverState(void);
	virtual ~CGameOverState(void);
	CGameOverState(const CGameOverState&);
	CGameOverState* operator=( CGameOverState& );
	CBitmapFont tempfont;
//	static CGameOverState* s_Instance;

	Vec2D m_sCursorPos;

};

