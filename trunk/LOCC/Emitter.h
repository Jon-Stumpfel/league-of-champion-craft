#pragma once

#include "StdAfx.h"

class CParticle;

class CEmitter
{

public:

	CEmitter(void);
	~CEmitter(void);
	void Execute( void );

private:

	int m_nImgID;
	int m_nSourceBlend;
	int m_nDestBlend;
	int m_nStartColor[4];
	int m_nEndColor[4];

	Vec2D m_sStartVel;
	Vec2D m_sEndVel;
	Vec2D m_sPos;

	float m_fSpawnRate;
	float m_fStartRot;
	float m_fEndRot;
	float m_fStartScale;
	float m_fEndScale;
	
	std::vector< CParticle* > m_vAliveParticles;
	std::vector< CParticle* > m_vDeadParticles;
};

