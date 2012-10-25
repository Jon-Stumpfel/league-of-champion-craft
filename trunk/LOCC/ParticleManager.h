#pragma once

class CEmitter;

struct Color
{
	int a, r, g, b;
};

class CParticleManager
{

public:

	void Update( float fElapsedTime );
	void Render( void );
	void LoadParticles( PRTCL_TYPE eType, Vec2D sPos );
	void StopLoop( PRTCL_TYPE eType );

	static CParticleManager* GetInstance( void );

private:

	CParticleManager(void);
	~CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);


	std::vector< CEmitter* > m_vEmitters;

};

