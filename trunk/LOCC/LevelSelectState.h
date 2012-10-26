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
	CTile** m_ptempmap;
	CTile** m_p2ndtempmap;
	int m_pRows;
	int m_pColumns;
	int m_p2ndRows;
	int m_p2ndColumns;

	std::vector<std::vector<TILE_TYPE>> m_vMap1;
	std::vector<std::vector<TILE_TYPE>> m_vMap2;

};

