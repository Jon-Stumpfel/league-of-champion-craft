#pragma once

class IGameState;

class CStateStack
{

public:
	static CStateStack* GetInstance( void );
	static void DeleteInstance(void);

	void ClearStack(void);

	void Push( IGameState* pState );
	void Pop( void );
	void Switch( IGameState* pState );
	IGameState* GetTop(void);

	void	UpdateStack(float fElapsedTime);
	void	RenderStack(void);

	void	SetRenderTopOnly(bool b) { m_bRenderTopOnly = b;}
	bool FindState(IGameState* pState);
private:

	CStateStack(void);
	virtual ~CStateStack(void);
	CStateStack(const CStateStack&);
	CStateStack& operator=(const CStateStack&);

	static CStateStack* s_Instance;

	bool	m_bRenderTopOnly;
	std::vector< IGameState* > m_vCurStates;

};

