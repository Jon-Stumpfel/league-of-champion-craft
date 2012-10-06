#include "StdAfx.h"
#include "Archer.h"


CArcher::CArcher(void) : CUnit(ARCHER)
{
	SetHP(12);
	SetAttack(6);
	SetSpeed(4);
	SetFacing(0);
	SetRange(3);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CArcher::~CArcher(void)
{
}
