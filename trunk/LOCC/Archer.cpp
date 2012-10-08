#include "StdAfx.h"
#include "Archer.h"
#include "GameplayState.h"
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
	RECT soldierRect = {GetPos().nPosX * nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						GetPos().nPosY * nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY(), 
						GetPos().nPosX * nFakeTileWidth + nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						GetPos().nPosY * nFakeTileHeight + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 100, 255,100);	
}

