#include "StdAfx.h"
#include "Swordsman.h"


CSwordsman::CSwordsman(void) : CUnit(UT_SWORDSMAN)
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

void CSwordsman::Render(void)
{
	RECT soldierRect = {GetPos().nPosX, GetPos().nPosY, GetPos().nPosX + 32, GetPos().nPosY + 32};
	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 255, 0, 0);	
}
