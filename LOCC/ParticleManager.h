#pragma once

class CEmitter;

enum PRTCL_TYPE { TEST };

struct Color
{
	int a, r, g, b;
};

class CParticleManager
{

public:

	void Update( float fElapsedTime );
	void Render( void );
	void LoadParticles( PRTCL_TYPE eType, Vec2Df sPos );

	static CParticleManager* GetInstance( void );

private:

	CParticleManager(void);
	~CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);


	std::vector< CEmitter* > m_vEmitters;

};

