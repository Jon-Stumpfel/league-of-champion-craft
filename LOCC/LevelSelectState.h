#pragma once
#include "igamestate.h"
#include "StateStack.h"
#include "TileManager.h"
#include "Tile.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "StdAfx.h"
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

	void SetType(int type) { m_nType = type; }

private:

	void DrawMap(string sLevelname, int row, int col, vector<vector<TILE_TYPE>> m_vMap_, bool Selected);
	Vec2D m_2Dselected;
	LevelSelectState(void);
	virtual ~LevelSelectState(void);
	LevelSelectState(const LevelSelectState&);
	LevelSelectState* operator=(LevelSelectState&);
	int m_pRows;
	int m_pColumns;
	int m_p2ndRows;
	int m_p2ndColumns;
	int m_nType;
	vector<vector<TILE_TYPE>> m_vMap1;
	vector<vector<TILE_TYPE>> m_vMap2;
	vector<vector<TILE_TYPE>> m_vMap3;
	vector<vector<TILE_TYPE>> m_vMap4;
	bool m_sbSelected[4];

};

