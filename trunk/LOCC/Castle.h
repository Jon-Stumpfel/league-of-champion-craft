#pragma once

#include "unit.h"

class CCastle : public CUnit
{

public:

	CCastle(void);
	virtual ~CCastle(void);
	void Render( void );
	void Update( float fElapsedTime );

};

