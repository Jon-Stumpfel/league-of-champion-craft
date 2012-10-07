#pragma once

#include "GameObject.h"
#include "ParticleManager.h"

class CParticle
{

public:

	CParticle(void);
	~CParticle(void);

	CParticle( Vec2D sPos, Vec2Df sVel, float fScale, 
				float fLife, Color sColor, float fRot, RECT sSource);

	void Update( float fElapsedTime );
	void Render( void );

	Vec2Df GetVel( void ) const { return m_sVel; }
	float GetScale( void ) const { return m_fScale; }
	float GetLife( void ) const { return m_fLife; }
	Color GetColor( void ) const { return m_sColor; }
	float GetRotation( void ) const { return m_fRot; }
	RECT GetRect( void ) const { return m_sSource; }

	void SetVel( Vec2Df sVel ) { m_sVel = sVel; }
	void SetScale( float fScale ) { m_fScale = fScale; }
	void SetLife( float fLife ) { m_fLife = fLife; }
	void SetColor( Color sColor ) { m_sColor = sColor; }
	void SetRotation( float fRot ) { m_fRot = fRot; }
	void SetRect( RECT sSource ) { m_sSource = sSource; }

private:

	Vec2D m_sPos;
	Vec2Df m_sVel;
	float m_fScale;
	float m_fRot;
	float m_fLife;
	Color m_sColor;
	RECT m_sSource;
};

