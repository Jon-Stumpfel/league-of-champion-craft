#include "StdAfx.h"
#include "Skeleton.h"


CSkeleton::CSkeleton(void) : CUnit(UT_SKELETON)
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


void CSkeleton::Render(void)
{
	RECT soldierRect = {GetPos().nPosX * nFakeTileWidth, GetPos().nPosY * nFakeTileHeight, 
		GetPos().nPosX * nFakeTileWidth + nFakeTileWidth, GetPos().nPosY * nFakeTileHeight + nFakeTileHeight};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 255, 255, 255);	
}