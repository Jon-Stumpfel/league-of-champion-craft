#include "StdAfx.h"
#include "HelpMenuState.h"

//CHelpMenuState* CHelpMenuState::s_Instance = nullptr;

CHelpMenuState::CHelpMenuState(void)
{
}


CHelpMenuState::~CHelpMenuState(void)
{
}
			 
void CHelpMenuState::Enter(void)
{

}

void CHelpMenuState::Exit(void)
{

}

void CHelpMenuState::Input(INPUT_ENUM input)
{

}

void CHelpMenuState::Update(float fElapsedTime)
{

}

void CHelpMenuState::Render(void)
{

}

CHelpMenuState* CHelpMenuState::GetInstance()
{
	static CHelpMenuState s_Instance;
	return &s_Instance;
}