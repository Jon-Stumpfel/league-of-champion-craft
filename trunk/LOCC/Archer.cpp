#include "StdAfx.h"
#include "Archer.h"


CArcher::CArcher(void) : CUnit(UT_ARCHER)
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

void CArcher::Render(void)
{
	RECT soldierRect = {GetPos().nPosX * nFakeTileWidth, GetPos().nPosY * nFakeTileHeight, 
		GetPos().nPosX * nFakeTileWidth + nFakeTileWidth, GetPos().nPosY * nFakeTileHeight + nFakeTileHeight};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 100, 255,100);	
}

