#include "StdAfx.h"
#include "StateStack.h"
#include "IGameState.h"

CStateStack* CStateStack::s_Instance = nullptr;

CStateStack::CStateStack(void)
{
	m_bRenderTopOnly = false;
}

CStateStack::~CStateStack(void)
{
}

CStateStack* CStateStack::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CStateStack;

	return s_Instance;
}

// Push a state onto the stack. Call's the state's Enter() function for initialization
// and then adds it to the vector
void CStateStack::Push( IGameState* pState )
{
	assert(pState != nullptr && "CStateStack::Push - pState is nullptr");

	m_vCurStates.push_back(pState);
	if (m_vCurStates.back() != nullptr)
		m_vCurStates.back()->Enter();
}

// Pop the top stacked item, running it's Exit() and then removing it from the vector
void CStateStack::Pop(void)
{
	if (m_vCurStates.size() == 0)
		return;
	m_vCurStates.back()->Exit();
	m_vCurStates.pop_back();
}

// This will basically clear the stack and then push the passed state into the stack
// Pretty much for switching between main menu and gameplay state, clear any stacked on top states.
// Like if you have it stacked as thus: GameplayState->PauseState->OptionsState and you somehow go from this
// to the main menu, it would clear all of those states and then push MainMenustate.

void CStateStack::Switch( IGameState* pState )
{
	assert(pState != nullptr && "CStateStack::Switch - pState is nullptr");

	// Pop all states in the stack
	ClearStack();

	// Push the new one.
	Push(pState);
}
	bool  CStateStack::FindState(IGameState* pState)
	{
		for (unsigned int i = 0; i < m_vCurStates.size(); ++i)
		{
			if (pState == m_vCurStates[i])
				return true;
		}

		return false;
	}

IGameState* CStateStack::GetTop(void)
{
	return m_vCurStates.back();
}

// Update the states
void CStateStack::UpdateStack(float fElapsedTime)
{
	// Should this call update on ALL states in the stack or just the top?
	// If all, then we'd have to implement some kind of pause logic, whereas if we just do the top
	// then if you bring up pause menu, the GameplayState would "pause".

	// Update all
	//for (decltype(m_vCurStates.size()) i = 0; i < m_vCurStates.size(); ++i)
	//{
	//	m_vCurStates[i]->Update(fElapsedTime);
	//}

	// Update only the top
	GetTop()->Update(fElapsedTime);
}

// Render the states!
// If m_bRenderTopOnly is true, then only the top state in the stack will render. If you set the flag
// you must remember to unset the flag later
void CStateStack::RenderStack(void)
{
	if (m_bRenderTopOnly)
		GetTop()->Render();
	else
		for (decltype(m_vCurStates.size()) i = 0; i < m_vCurStates.size(); ++i)
			m_vCurStates[i]->Render();
}

void CStateStack::ClearStack(void)
{
	while (m_vCurStates.size() != 0)
	{
		Pop();
	}
}

void CStateStack::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->ClearStack();
		delete s_Instance;
	}
	s_Instance = nullptr;
}