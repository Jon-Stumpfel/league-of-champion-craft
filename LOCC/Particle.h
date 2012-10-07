#pragma once

#include "GameObject.h"
#include "ParticleManager.h"

class CParticle
{

public:

	CParticle(void);
	~CParticle(void);

	CParticle( Vec2D sPos, Vec2Df sDir, Vec2Df sVel, float fScale, 
				float fLife, Color sColor, float fRot, RECT sSource);

	void Update( float fElapsedTime );
	void Render( void );
	void RefreshTime( void ) { m_fCurTime = 0; }

	float GetScale( void ) const { return m_fScale; }
	float GetCurTime( void ) const { return m_fCurTime; }
	float GetEndTime( void ) const { return m_fEndTime; }
	Color GetColor( void ) const { return m_sColor; }
	float GetRotation( void ) const { return m_fRot; }
	RECT GetRect( void ) const { return m_sSource; }
	Vec2Df GetVel( void ) const { return m_sVel; }
	Vec2Df GetDir( void ) const { return m_sDir; }

	void SetScale( float fScale ) { m_fScale = fScale; }
	void SetCurTime( float fTime ) { m_fCurTime = fTime; }	
	void SetEndTime( float fTime ) { m_fEndTime = fTime; }
	void SetColor( Color sColor ) { m_sColor = sColor; }
	void SetRotation( float fRot ) { m_fRot = fRot; }
	void SetRect( RECT sSource ) { m_sSource = sSource; }
	void SetVel( Vec2Df sVel ) { m_sVel = sVel; }
	void SetDir( Vec2Df sDir ) { m_sDir = sDir; }

private:

	Vec2D m_sPos;
	Vec2Df m_sVel;
	Vec2Df m_sDir;
	float m_fScale;
	float m_fRot;
	float m_fCurTime;
	float m_fEndTime;
	Color m_sColor;
	RECT m_sSource;
};

