#include "StdAfx.h"
#include "Skeleton.h"


CSkeleton::CSkeleton(void) : CUnit(SKELETON)
{
	SetHP(10);
	SetAttack(4);
	SetSpeed(2);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CSkeleton::~CSkeleton(void)
{
}
