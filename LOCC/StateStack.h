#pragma once

class IGameState;

class CStateStack
{

public:

	CStateStack(void);
	~CStateStack(void);
	void Push( IGameState* pState );
	void Pop( IGameState* pState );
	void Switch( IGameState* pState );

private:

	std::vector< IGameState* > m_vCurStates;

};

