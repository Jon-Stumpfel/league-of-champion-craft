#pragma once
#include "igamestate.h"
#include "StateStack.h"
#include "TileManager.h"
#include "Tile.h"
#include "GameManager.h"
#include "GraphicsManager.h"
class LevelSelectState : public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	RECT CellAlgorithm(int id);
	static LevelSelectState* GetInstance();
private:
	int selected;
	LevelSelectState(void);
	virtual ~LevelSelectState(void);
	LevelSelectState(const LevelSelectState&);
	LevelSelectState* operator=(LevelSelectState&);
	CBitmapFont tempfont;
};

