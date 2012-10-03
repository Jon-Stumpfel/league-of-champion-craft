#include "StdAfx.h"
#include "AnimationManager.h"

CAnimationManager* CAnimationManager::s_Instance = nullptr;


CAnimationManager::CAnimationManager(void)
{
}


CAnimationManager::~CAnimationManager(void)
{
}

void CAnimationManager::Update( float fElapsedTime )
{

}

void CAnimationManager::Render( void )
{

}

CAnimationManager* CAnimationManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CAnimationManager();

	return s_Instance;
}