#include "StdAfx.h"
#include "Cavalry.h"


CCavalry::CCavalry(void) : CUnit(CAVALRY)
{
	SetHP(22);
	SetAttack(6);
	SetSpeed(5);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(15);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CCavalry::~CCavalry(void)
{
}
