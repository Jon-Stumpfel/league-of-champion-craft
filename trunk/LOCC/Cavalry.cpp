#include "StdAfx.h"
#include "Cavalry.h"
#include "GameplayState.h"


CCavalry::CCavalry(void) : CUnit(UT_CAVALRY)
{
	SetHP(22);
	SetMaxHP(22);
	SetAttack(6);
	SetSpeed(5);
	SetRange(1);
	SetEXPValue(15);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary.png",L"Cavalry",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CCavalry::~CCavalry(void)
{
}
void CCavalry::Render(void)
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Cavalry"),
		(m_sWorldPos.nPosX + 16)- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		(m_sWorldPos.nPosY - 8) - (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.72f,0.77f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}