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

CParticle::CParticle( Vec2D sPos, Vec2Df sDir, Vec2Df sVel, float fScale, 
						float fLife, Color sColor, float fRot, RECT sSource)
{
	m_sPos = sPos;
	m_sVel = sVel;
	m_sDir = sDir;
	m_fScale = fScale;
	m_fCurTime = 0;
	m_fEndTime = fLife;
	m_sColor = sColor;
	m_fRot = fRot;
	m_sSource = sSource;
}

void CParticle::Update( float fElapsedTime )
{
	// finds the velocity over the amount of elapsed time
	m_sPos.nPosX += int(m_sVel.fVecX);
	m_sPos.nPosY += int(m_sVel.fVecY);

	// Increases the age of the particle
	m_fCurTime += fElapsedTime;
}

void CParticle::Render( void )
{
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	int ID = pGM->GetID( _T("Particle") );

	pTM->Draw( ID, m_sPos.nPosX, m_sPos.nPosY, m_fScale, m_fScale, &m_sSource, float(m_sSource.right - m_sSource.left)/2.0f, float(m_sSource.bottom - m_sSource.top)/2.0f,
					m_fRot, D3DCOLOR_ARGB(m_sColor.a, m_sColor.r, m_sColor.g, m_sColor.b ) );
}