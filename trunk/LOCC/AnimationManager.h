#pragma once

#include "Animation.h"

class CAnimationManager
{

public:

	void Update( float fElapsedTime );
	void Render( void );

	static CAnimationManager* GetInstance( void );

private:

	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager(const CAnimationManager&);
	CAnimationManager& operator=(const CAnimationManager&);

	static CAnimationManager* s_Instance;

	std::map<UnitType, AnimType> AnimMap;

};

