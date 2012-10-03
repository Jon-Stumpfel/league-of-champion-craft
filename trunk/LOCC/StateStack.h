#pragma once

class IGameState;

class CStateStack
{

public:

	void Push( IGameState* pState );
	void Pop( IGameState* pState );
	void Switch( IGameState* pState );

	static CStateStack* GetInstance( void );

private:

	CStateStack(void);
	virtual ~CStateStack(void);
	CStateStack(const CStateStack&);
	CStateStack& operator=(const CStateStack&);

	static CStateStack* s_Instance;

	std::vector< IGameState* > m_vCurStates;

};

