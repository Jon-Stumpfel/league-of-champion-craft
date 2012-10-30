#pragma once
#include "igamestate.h"
#include "Ability.h"
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

	void ClearSelections(void);

	CUnit* GetSelectedUnit(void) { return m_pSelectedUnit; }

	CUnit* GetHighlighted(void) { return m_pHighlightedUnit;}
	void ClearHighlighted(void) { m_pHighlightedUnit = nullptr;}

	Vec2D GetSelectionPos(void) { return m_SelectionPos;}

	int GetSelectedSpell( void ) { return m_nSelectedSpell; }

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
	public:
	bool CalculateMove(CTile* startTile, CTile* targetTile, std::vector<CTile*>& m_vVector);
	private:
	void FindNode(std::list<ASNode*> list, CTile* pTile);


	
	Vec2D m_newCamPixelPos;
	Vec2D m_oldCamPixelPos;
	Vec2D m_currCamPixelPos;
	float m_fLerpPercent;
	bool m_bLerpingX;
	void LerpCamera(float fElapsedTime);


	RECT rCamRect;
	Vec2D m_MouseOffset;
	Vec2D m_CameraPos;
	Vec2D m_SelectionPos;

	bool m_bIsFacing;

	int m_nCardOffsetX;
	int m_nTooltipOffsetX;
	int m_nTooltipOffsetMaxX;
	int m_nCardOffsetMaxX;
	float m_fCardOffsetLerp;
	bool m_bShowingCard;

	bool m_bSelectChampionAbility;
	int m_nSelectedSpell;
	int m_nSpellPanelOffsetY;
	int m_nSpellPanelOffsetYMAX;
	bool m_bShowSpellPanel;

	int m_nSelectedAbility;
	void UseAbility(CAbility* ability);


	CUnit* m_pSelectedUnit;
	CUnit* m_pHighlightedUnit;
	bool m_bIsHighlighting;
	CTile* m_pTargetedTile;
	bool m_bIsMoving;
	bool m_bIsTargeting;
	CBitmapFont* m_pBitmapFont;
//	static CGameplayState* s_Instance;

};

