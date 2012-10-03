#include "StdAfx.h"
#include "StateStack.h"
#include "IGameState.h"

CStateStack* CStateStack::s_Instance = nullptr;

CStateStack::CStateStack(void)
{
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

void CStateStack::Push( IGameState* pState )
{

}

void CStateStack::Pop( IGameState* pState )
{

}

void CStateStack::Switch( IGameState* pState )
{

}