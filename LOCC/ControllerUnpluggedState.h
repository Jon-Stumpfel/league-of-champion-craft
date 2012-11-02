#pragma once
#include "igamestate.h"
class CControllerUnpluggedState :
	public IGameState
{
	
public:
	static CControllerUnpluggedState* GetInstance();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	void SetJoyToPlug(int i) { m_nJoyToPlug = i;}
	int GetJoyToPlug(void) { return m_nJoyToPlug;}
private:
	CControllerUnpluggedState(void);
	~CControllerUnpluggedState(void);
	CControllerUnpluggedState(const CControllerUnpluggedState&);
	CControllerUnpluggedState& operator=(const CControllerUnpluggedState&);

	int m_nJoyToPlug;
};

