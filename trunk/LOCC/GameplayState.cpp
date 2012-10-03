#include "StdAfx.h"
#include "GameplayState.h"

CGameplayState* CGameplayState::s_Instance = nullptr;

CGameplayState::CGameplayState(void)
{
}

CGameplayState::~CGameplayState(void)
{
}

CGameplayState* CGameplayState::GetInstance(void)
{
	if( s_Instance == nullptr )
		s_Instance = new CGameplayState;

	return s_Instance;
}

void CGameplayState::Enter(void)
{

}

void CGameplayState::Exit(void)
{
}

void CGameplayState::Input(INPUT_ENUM input)
{
}

void CGameplayState::Update(float fElapsedTime)
{
}

void CGameplayState::Render(void)
{
}