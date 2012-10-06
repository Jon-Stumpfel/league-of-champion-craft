#include "StdAfx.h"
#include "Castle.h"


CCastle::CCastle(void) : CUnit(CASTLE)
{
	SetHP(500);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CCastle::~CCastle(void)
{
}

void CCastle::Render( void )
{

}

void CCastle::Update( float fElapsedTime )
{

}