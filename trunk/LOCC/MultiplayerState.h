#pragma once
#include "igamestate.h"
class CMultiplayerState :
	public IGameState
{
public:

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CMultiplayerState* GetInstance();


	bool GetWaitingForPlayer(void) { return m_bWaitingForPlayer;}
	void SetWaitingForPlayer(bool b) { m_bWaitingForPlayer = b;}

	void PlayerConnected(void);
	bool GetNetworkSetup(void) { return m_bNetworkSetup;}
private:
	CMultiplayerState(void);
	virtual ~CMultiplayerState(void);
	CMultiplayerState(const CMultiplayerState&);
	CMultiplayerState& operator=(const CMultiplayerState&);

	int m_nMenuChoice;
	bool m_bInputIPaddress;
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	unsigned char byte4;
	int m_nIPBracketLeft;

	bool m_bWaitingForPlayer;
	bool m_bWaitingForHost;
	bool m_bNetworkSetup;
};

