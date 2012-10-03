#pragma once

#include "Animation.h"

class CAnimationManager
{

public:

	CAnimationManager(void);
	~CAnimationManager(void);
	void Update( float fElapsedTime );
	void Render( void );

private:

	std::map<UnitType, AnimType> AnimMap;

};

