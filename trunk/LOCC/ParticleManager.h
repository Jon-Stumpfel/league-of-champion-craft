#pragma once

class CEmitter;

class CParticleManager
{

public:

	void Update( float fElapsedTime );
	void Render( void );

	static CParticleManager* GetInstance( void );

private:

	CParticleManager(void);
	~CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);

	static CParticleManager* s_Instance;

	std::vector< CEmitter* > m_vEmitters;

};

