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

CParticle::CParticle( Vec2D sPos, Vec2D sVel, float fScale, float fLife, Color sColor, float fRot, RECT sSource )
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
	m_sPos.nPosX += m_sVel.nPosX;
	m_sPos.nPosY += m_sVel.nPosY;
}

void CParticle::Render( void )
{
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();

	int ID = pGM->GetID( _T("Particle") );

	pTM->Draw( ID, m_sPos.nPosX, m_sPos.nPosY, m_fScale, m_fScale, &m_sSource, 0.0f, 0.0f,
				m_fRot, D3DCOLOR_ARGB(m_sColor.a, m_sColor.r, m_sColor.g, m_sColor.b ) );
}