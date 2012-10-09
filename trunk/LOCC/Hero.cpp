#include "StdAfx.h"
#include "Hero.h"
#include "GameplayState.h"


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
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 205, 150, 100);	
}
