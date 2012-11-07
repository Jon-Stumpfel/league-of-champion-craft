#pragma once
#include "BitmapFont.h"
class CTutorialTextState: public IGameState
{
public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	RECT CellAlgorithm(int id);
	static CTutorialTextState* GetInstance();

private:
	CTutorialTextState(void);
	virtual ~CTutorialTextState(void);
	CTutorialTextState(const CTutorialTextState&);
	CTutorialTextState* operator=(CTutorialTextState&);

	CBitmapFont m_cFont;
	int m_nNextText;
};

