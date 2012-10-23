#include "StdAfx.h"
#include "Skeleton.h"
#include "GameplayState.h"

CSkeleton::CSkeleton(void) : CUnit(UT_SKELETON)
{
	SetHP(10);
	SetMaxHP(10);
	SetAttack(4);
	SetSpeed(2);
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
	D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
	if (GetHasAttacked())
		color = D3DCOLOR_XRGB(90, 90, 90);
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().top - tempanchorpoint.nPosY;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Skeleton"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)+10,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-20,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,color);
}