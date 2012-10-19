#pragma once

#include "ParticleManager.h"

enum Shape { DOT, CIRCLE, SQUARE, LINE };

class CParticle;

class CEmitter
{

public:

	CEmitter(void);
	~CEmitter(void);

	void Render( void );
	void Update( float fElapsedTime );

	void LoadParticles( PRTCL_TYPE eType, Vec2D sPos );
	void Clear( void );

	bool Alive( void );

private:

	void Loop( void );

	int m_nNumParticles;
	
	unsigned int m_nNumSpawned;

	Color m_sStartColor;
	Color m_sEndColor;

	Vec2Df m_sMinDir;
	Vec2Df m_sMaxDir;
	Vec2Df m_sStartVelMax;
	Vec2Df m_sStartVelMin;
	Vec2Df m_sEndVelMax;
	Vec2Df m_sEndVelMin;
	Vec2D m_sImgPos;
	Vec2D m_sEmitPos;

	RECT m_sSource;

	int m_nMinSpawnRate;	
	int m_nMaxSpawnRate;
	int m_nImgID;
	float m_fSpawnRate;
	float m_fStartRot;
	float m_fEndRot;
	float m_fStartScale;
	float m_fEndScale;
	float m_fMinLife;
	float m_fMaxLife;
	float m_fSpawnTimer;

	float Radius;
	Vec2D m_sPoint;
	Vec2D m_sPoint2;
	int m_nHeight;
	int m_nWidth;
	Shape m_eType;

	bool m_bLooping;

	const char* m_szPath;
	
	std::vector< CParticle* > m_vAliveParticles;
};

