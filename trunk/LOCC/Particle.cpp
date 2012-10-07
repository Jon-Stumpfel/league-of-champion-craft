#include "StdAfx.h"
#include "Particle.h"

#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_TextureManager.h"


CParticle::CParticle(void)
{
}


CParticle::~CParticle(void)
{
}

CParticle::CParticle( Vec2D sPos, Vec2Df sVel, float fScale, float fLife, Color sColor, float fRot, RECT sSource )
{
	m_sPos = sPos;
	m_sVel = sVel;
	m_fScale = fScale;
	m_fLife = fLife;
	m_sColor = sColor;
	m_fRot = fRot;
	m_sSource = sSource;
}

void CParticle::Update( float fElapsedTime )
{
	if( fElapsedTime != 2 )
	{
		m_sPos.nPosX += int(m_sVel.fVecX * fElapsedTime);
		m_sPos.nPosY += int(m_sVel.fVecY * fElapsedTime);
	}
	else
	{
		m_sPos.nPosX += int(m_sVel.fVecX * .2f);
		m_sPos.nPosY += int(m_sVel.fVecY * .2f);
	}
}

void CParticle::Render( void )
{
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	int ID = pGM->GetID( _T("Particle") );

	pTM->Draw( ID, m_sPos.nPosX, m_sPos.nPosY, m_fScale, m_fScale, &m_sSource, 0.0f, 0.0f,
				m_fRot, D3DCOLOR_ARGB(m_sColor.a, m_sColor.r, m_sColor.g, m_sColor.b ) );
}