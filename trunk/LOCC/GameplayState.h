#pragma once
#include "StdAfx.h"
#include "igamestate.h"
#include "InputManager.h"
#include "AnimationManager.h"
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

	int GetCamOffsetX(void);
	int GetCamOffsetY(void);

	Vec2D GetMouseOffset(void) { return m_MouseOffset;}
	void SetMouseOffset(Vec2D v) { m_MouseOffset = v;}


	void SnapToPosition(Vec2D pPos);
private:

	class ASNode
	{
	public:
		CTile* pTile;
		int	 nCost;
		ASNode* parent;
		int nF;
		int nH;
		int nG;
	};
	CGameplayState(void);
	~CGameplayState(void);
	CGameplayState(const CGameplayState&);
	CGameplayState& operator=(const CGameplayState&);

	void MoveCamera(int dX, int dY);
	void MoveCursor(int dX, int dY, bool lock = true);
	void MoveToTile(Vec2D nTilePosition);


	// A* algorithm stuff
	std::vector<CTile*> m_vWaypoints;
	bool CalculateMove(CTile* startTile, CTile* targetTile);
	void FindNode(std::list<ASNode*> list, CTile* pTile);


	
	Vec2D m_newCamPixelPos;
	Vec2D m_oldCamPixelPos;
	Vec2D m_currCamPixelPos;
	float m_fLerpPercent;
	bool m_bLerpingX;
	bool m_bLerpingY;
	void LerpCamera(float fElapsedTime);


	RECT rCamRect;
	Vec2D m_MouseOffset;
	Vec2D m_CameraPos;
	Vec2D m_SelectionPos;

	CUnit* m_pSelectedUnit;
	bool m_bIsMoving;
//	static CGameplayState* s_Instance;

};

