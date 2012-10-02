#pragma once

#include "GameObject.h"

class CParticle
{

public:

	CParticle(void);
	~CParticle(void);

private:

	Vec2D m_sPos;
	Vec2D m_sScale;

	float m_fLife;

};

