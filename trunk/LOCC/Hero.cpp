#include "StdAfx.h"
#include "Hero.h"


CHero::CHero(void) : CUnit(HERO)
{
	SetHP(50);
	SetAttack(9);
	SetSpeed(4);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(0);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CHero::~CHero(void)
{
}
