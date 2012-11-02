#pragma once

class CEmitter;
class CGameObject;

struct Color
{
	int a, r, g, b;
};

class CParticleManager
{

public:

	void Update( float fElapsedTime );
	void Render( void );
	void LoadParticles( PRTCL_TYPE eType, Vec2D sPos, CGameObject* track = nullptr );
	void StopLoop( PRTCL_TYPE eType );

	void Clear( void );

	static CParticleManager* GetInstance( void );

private:

	CParticleManager(void);
	~CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);


	std::vector< CEmitter* > m_vEmitters;

};

