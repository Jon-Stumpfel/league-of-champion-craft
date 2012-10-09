#include "StdAfx.h"
#include "Cavalry.h"
#include "GameplayState.h"


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
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 0, 255, 255);	
}