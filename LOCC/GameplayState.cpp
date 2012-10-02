#include "StdAfx.h"
#include "GameplayState.h"


CGameplayState::CGameplayState(void)
{
}


CGameplayState::~CGameplayState(void)
{
}



CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState s_Instance;
	return &s_Instance;
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