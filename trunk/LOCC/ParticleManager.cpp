#include "StdAfx.h"
#include "ParticleManager.h"
#include "Emitter.h"
#include "SGD Wrappers\tinyxml.h"

CParticleManager::CParticleManager(void)
{
}

CParticleManager::~CParticleManager(void)
{
	for( unsigned int i = 0; i < m_vEmitters.size(); i++ )
	{
		m_vEmitters[i]->Clear();
		delete m_vEmitters[i];
		m_vEmitters.erase( m_vEmitters.begin() + i );
		i--;
	}
}

CParticleManager* CParticleManager::GetInstance( void )
{
	static CParticleManager s_Instance;
	return &s_Instance;
}

void CParticleManager::Update( float fElapsedTime )
{
	for( unsigned int i = 0; i < m_vEmitters.size(); i++ )
	{
		if( m_vEmitters[i]->Alive() )
			m_vEmitters[i]->Update( fElapsedTime );
		else
		{
			m_vEmitters[i]->Clear();
			delete m_vEmitters[i];
			m_vEmitters.erase( m_vEmitters.begin() + i );
			i--;
		}
	}
}

void CParticleManager::Render( void )
{
	for( unsigned int i = 0; i < m_vEmitters.size(); i++ )
	{
		if( m_vEmitters[i]->Alive() )
			m_vEmitters[i]->Render();
	}
}

void  CParticleManager::LoadParticles( PRTCL_TYPE eType, Vec2D sPos )
{
	m_vEmitters.push_back( new CEmitter );
	m_vEmitters[m_vEmitters.size()-1]->LoadParticles( eType, sPos );
}