#include "StdAfx.h"
#include "Skeleton.h"
#include "GameplayState.h"

CSkeleton::CSkeleton(void) : CUnit(UT_SKELETON)
{
	SetHP(10);
	SetMaxHP(10);
	SetAttack(4);
	SetSpeed(2);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\skeleton.png",L"Skeleton",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CSkeleton::~CSkeleton(void)
{
}


void CSkeleton::Render(void)
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Skeleton"),
		m_sWorldPos.nPosX- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY- (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}