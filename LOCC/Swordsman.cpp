#include "StdAfx.h"
#include "Swordsman.h"
#include "GameplayState.h"

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
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};
	CSGD_Direct3D::GetInstance()->DrawRect(soldierRect, 255, 0, 0);	
}
