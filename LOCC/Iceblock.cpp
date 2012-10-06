#include "StdAfx.h"
#include "Iceblock.h"


CIceblock::CIceblock(void) : CUnit(ICEBLOCK)
{
	SetHP(20);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(5);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CIceblock::~CIceblock(void)
{
}
