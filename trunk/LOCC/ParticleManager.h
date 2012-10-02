#pragma once

class CEmitter;

class CParticleManager
{

public:

	CParticleManager(void);
	~CParticleManager(void);
	void Update( float fElapsedTime );
	void Render( void );

private:

	std::vector< CEmitter* > m_vEmitters;

};

