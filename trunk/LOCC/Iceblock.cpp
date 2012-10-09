#include "StdAfx.h"
#include "Iceblock.h"
#include "GameplayState.h"


CIceblock::CIceblock(void) : CUnit(UT_ICEBLOCK)
{
	SetHP(20);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(5);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	// TODO: Setup abilities when they are in place
}


CIceblock::~CIceblock(void)
{
}

void CIceblock::Render(void)
{
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};

	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 0, 255, 0);	
}

