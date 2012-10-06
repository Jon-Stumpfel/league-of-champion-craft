#include "StdAfx.h"
#include "Swordsman.h"


CSwordsman::CSwordsman(void) : CUnit(SWORDSMAN)
{
	SetHP(20);
	SetAttack(8);
	SetSpeed(3);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CSwordsman::~CSwordsman(void)
{

}