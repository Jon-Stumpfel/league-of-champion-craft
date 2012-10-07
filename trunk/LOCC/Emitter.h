#pragma once

#include "StdAfx.h"
#include "ParticleManager.h"

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

	int m_nSourceBlend;
	int m_nDestBlend;
	int m_nHeight;
	int m_nWidth;

	int m_nNumParticles;
	
	unsigned int m_nNumSpawned;

	Color m_sStartColor;
	Color m_sEndColor;

	Vec2Df m_sMinDir;
	Vec2Df m_sMaxDir;
	Vec2Df m_sStartVel;
	Vec2Df m_sEndVel;
	Vec2D m_sImgPos;
	Vec2D m_sEmitPos;

	int m_nMinSpawnRate;	
	int m_nMaxSpawnRate;
	float m_fSpawnRate;
	float m_fStartRot;
	float m_fEndRot;
	float m_fStartScale;
	float m_fEndScale;
	float m_fMinLife;
	float m_fMaxLife;
	float m_fSpawnTimer;

	bool m_bLooping;

	const char* m_szPath;
	
	std::vector< CParticle* > m_vAliveParticles;
};

