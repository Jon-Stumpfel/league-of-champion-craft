#pragma once

#include "GameObject.h"
#include "ParticleManager.h"

class CParticle
{

public:

	CParticle(void);
	~CParticle(void);

	CParticle( Vec2D sPos, Vec2Df sVelEnd, Vec2Df sVelStart, float fScale, 
				float fLife, Color sColor, float fRot, RECT sSource, int ID);

	void Update( float fElapsedTime );
	void Render( void );
	void RefreshTime( void ) { m_fCurTime = 0; }

	float GetScale( void ) const { return m_fScale; }
	float GetCurTime( void ) const { return m_fCurTime; }
	float GetEndTime( void ) const { return m_fEndTime; }
	Color GetColor( void ) const { return m_sColor; }
	float GetRotation( void ) const { return m_fRot; }
	RECT GetRect( void ) const { return m_sSource; }
	Vec2Df GetVelStart( void ) const { return m_sVelStart; }
	Vec2Df GetVelEnd( void ) const { return m_sVelEnd; }

	void SetScale( float fScale ) { m_fScale = fScale; }
	void SetCurTime( float fTime ) { m_fCurTime = fTime; }	
	void SetEndTime( float fTime ) { m_fEndTime = fTime; }
	void SetColor( Color sColor ) { m_sColor = sColor; }
	void SetRotation( float fRot ) { m_fRot = fRot; }
	void SetRect( RECT sSource ) { m_sSource = sSource; }
	void SetVelStart( Vec2Df sVel ) { m_sVelStart = sVel; }
	void SetVelEnd( Vec2Df sVel ) { m_sVelEnd = sVel; }

private:

	Vec2D m_sPos;
	Vec2Df m_sVelStart;
	Vec2Df m_sVelEnd;
	Vec2Df m_sVel;
	float m_fScale;
	float m_fRot;
	float m_fCurTime;
	float m_fEndTime;
	int m_nImgID;
	Color m_sColor;
	RECT m_sSource;
};

