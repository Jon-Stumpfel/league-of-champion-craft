#include "StdAfx.h"
#include "Castle.h"
#include "GameplayState.h"


CCastle::CCastle(void) : CUnit(UT_CASTLE)
{
	SetHP(500);
	SetMaxHP(500);
	SetAttack(0);
	SetSpeed(0);
	SetRange(0);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/castle.png",L"Castle",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place	
}


CCastle::~CCastle(void)
{
}

void CCastle::Render( void )
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Castle"),
		(m_sWorldPos.nPosX + 16)- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		(m_sWorldPos.nPosY - 6) - (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.5f,0.5f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}