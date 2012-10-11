#include "StdAfx.h"
#include "Swordsman.h"
#include "GameplayState.h"

CSwordsman::CSwordsman(void) : CUnit(UT_SWORDSMAN)
{
	SetHP(20);
	SetMaxHP(20);
	SetAttack(8);
	SetSpeed(3);
	SetRange(1);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman.png",L"Swordsman",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CSwordsman::~CSwordsman(void)
{
}

void CSwordsman::Render(void)
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Swordsman"),
		(m_sWorldPos.nPosX + 24)- (tempanchorpoint.nPosX/4*3)- CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - (tempanchorpoint.nPosY/4*3)- CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));	
}
