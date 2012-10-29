#pragma once

#include "igamestate.h"
#include "BitmapFont.h"
class COptionsMenuState : public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	static COptionsMenuState* GetInstance();
private:
	int musicvolume;
	int soundvolume;
	int selected;
	bool windowed;
	COptionsMenuState(void);
	virtual ~COptionsMenuState(void);
	COptionsMenuState(const COptionsMenuState&);
	COptionsMenuState& operator=(const COptionsMenuState&);
	CBitmapFont* m_pBitmapFont;
	//static COptionsMenuState* s_Instance;
	CSGD_TextureManager* pTM;
	Vec2D m_sCursorPos;
	int	jcs_nImageID;
	int Scroll;
	bool IsModern;
};

