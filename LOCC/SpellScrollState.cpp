#include "StdAfx.h"
#include "SpellScrollState.h"

//CSpellScrollState* CSpellScrollState::s_Instance = nullptr;

CSpellScrollState::CSpellScrollState(void)
{
}


CSpellScrollState::~CSpellScrollState(void)
{
}


void CSpellScrollState::Enter(void)
{

}

void CSpellScrollState::Exit(void)
{

}

void CSpellScrollState::Input(INPUT_ENUM input)
{

}

void CSpellScrollState::Update(float fElapsedTime)
{

}

void CSpellScrollState::Render(void)
{

}

CSpellScrollState* CSpellScrollState::GetInstance(void)
{
	static CSpellScrollState s_Instance;
	return &s_Instance;
}