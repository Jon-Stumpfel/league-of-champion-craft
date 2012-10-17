#include "StdAfx.h"
#include "Particle.h"

#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "GameplayState.h"


CParticle::CParticle(void)
{
}


CParticle::~CParticle(void)
{
}

CParticle::CParticle( Vec2Df sPos, Vec2Df sVelEnd, Vec2Df sVelStart, float fScale, 
						float fLife, Color sColor, float fRot, RECT sSource)
{
	m_sPos = sPos;
	m_sVelStart = sVelStart;
	m_sVelEnd = sVelEnd;
	m_sVel = sVelStart;
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
	m_sPos.fVecX += m_sVel.fVecX * fElapsedTime;
	m_sPos.fVecY += m_sVel.fVecY * fElapsedTime;

	// Increases the age of the particle
	m_fCurTime += fElapsedTime;
}

void CParticle::Render( void )
{
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	CGameplayState* pGP = CGameplayState::GetInstance();

	int ID = pGM->GetID( _T("Particle") );

	int x = int(m_sPos.fVecX);
	int y = int(m_sPos.fVecY);

	float nWidth = (m_sSource.right - m_sSource.left) * m_fScale * .5f;
	float nHeight = (m_sSource.bottom - m_sSource.top) * m_fScale * .5f;

	pTM->Draw( ID, int((x - nWidth)-pGP->GetCamOffsetX()), int((y - nHeight)-pGP->GetCamOffsetY()), m_fScale, m_fScale, &m_sSource,
				float(m_sSource.right - m_sSource.left)/2.0f, float(m_sSource.bottom - m_sSource.top)/2.0f,
				m_fRot, D3DCOLOR_ARGB(m_sColor.a, m_sColor.r, m_sColor.g, m_sColor.b ) );
}