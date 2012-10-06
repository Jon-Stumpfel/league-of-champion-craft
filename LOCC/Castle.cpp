#include "StdAfx.h"
#include "Castle.h"


CCastle::CCastle(void) : CUnit(UT_CASTLE)
{
	SetHP(500);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CCastle::~CCastle(void)
{
}

void CCastle::Render( void )
{
	RECT soldierRect = {GetPos().nPosX, GetPos().nPosY, GetPos().nPosX + 32, GetPos().nPosY + 32};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 0, 0, 255);
}

void CCastle::Update( float fElapsedTime )
{

}

