#include "StdAfx.h"
#include "CreditsState.h"

//CCreditsState* CCreditsState::s_Instance = nullptr;

CCreditsState::CCreditsState(void)
{
}

CCreditsState::~CCreditsState(void)
{
}

void CCreditsState::Enter(void)
{

}

void CCreditsState::Exit(void)
{

}

void CCreditsState::Input(INPUT_ENUM input)
{

}

void CCreditsState::Update(float fElapsedTime)
{

}

void CCreditsState::Render(void)
{

}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState s_Instance;
	return &s_Instance;
}
