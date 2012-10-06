#include "StdAfx.h"
#include "Cavalry.h"


CCavalry::CCavalry(void) : CUnit(UT_CAVALRY)
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
void CCavalry::Render(void)
{
	RECT soldierRect = {GetPos().nPosX, GetPos().nPosY, GetPos().nPosX + 32, GetPos().nPosY + 32};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 0, 255, 255);	
}