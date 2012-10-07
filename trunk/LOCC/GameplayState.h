#pragma once
#include "StdAfx.h"
#include "igamestate.h"
#include "InputManager.h"
#include "Unit.h"
class CGameplayState :	public IGameState
	{
public:

	static CGameplayState* GetInstance(void);

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

private:

	CGameplayState(void);
	~CGameplayState(void);
	CGameplayState(const CGameplayState&);
	CGameplayState& operator=(const CGameplayState&);

	void MoveCursor(int dX, int dY);
	void MoveToTile(Vec2D nTilePosition);
	Vec2D m_CameraPos;
	Vec2D m_SelectionPos;

	CUnit* m_pSelectedUnit;

	bool m_bIsMoving;
//	static CGameplayState* s_Instance;

};

