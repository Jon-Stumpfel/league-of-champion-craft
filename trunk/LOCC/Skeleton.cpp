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
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 255, 255, 255);	
}