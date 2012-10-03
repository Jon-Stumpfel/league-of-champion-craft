#include "StdAfx.h"
#include "ParticleManager.h"

CParticleManager* CParticleManager::s_Instance = nullptr;

CParticleManager::CParticleManager(void)
{
}

CParticleManager::~CParticleManager(void)
{
	
}

CParticleManager* CParticleManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CParticleManager();

	return s_Instance;
}

void CParticleManager::Update( float fElapsedTime )
{

}

void CParticleManager::Render( void )
{

}

