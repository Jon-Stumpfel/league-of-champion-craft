#include "StdAfx.h"
#include "Hero.h"


CHero::CHero(void) : CUnit(UT_HERO)
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

void CHero::Render(void)
{
	RECT soldierRect = {GetPos().nPosX, GetPos().nPosY, GetPos().nPosX + 32, GetPos().nPosY + 32};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 205, 150, 100);	
}
