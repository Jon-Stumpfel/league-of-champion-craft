#pragma once

#include "unit.h"
#include "GraphicsManager.h"
class CCastle : public CUnit
{
	UnitAnimation* m_sAnimStruct;
public:

	CCastle(void);
	virtual ~CCastle(void);
	void Render( void );
	void Update( float fElapsedTime );

};

