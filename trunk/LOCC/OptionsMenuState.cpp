#include "StdAfx.h"
#include "OptionsMenuState.h"

//COptionsMenuState* COptionsMenuState::s_Instance = nullptr;

COptionsMenuState::COptionsMenuState(void)
{
}


COptionsMenuState::~COptionsMenuState(void)
{
}


void COptionsMenuState::Enter(void)
{

}

void COptionsMenuState::Exit(void)
{

}

void COptionsMenuState::Input(INPUT_ENUM input)
{

}

void COptionsMenuState::Update(float fElapsedTime)
{

}

void COptionsMenuState::Render(void)
{

}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}