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
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().top - tempanchorpoint.nPosY;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Castle"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-60,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.45f,0.45f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}