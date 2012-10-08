#include "StdAfx.h"
#include "Skeleton.h"
#include "GameplayState.h"

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
	RECT soldierRect = {GetPos().nPosX * nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						GetPos().nPosY * nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY(), 
						GetPos().nPosX * nFakeTileWidth + nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						GetPos().nPosY * nFakeTileHeight + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 255, 255, 255);	
}