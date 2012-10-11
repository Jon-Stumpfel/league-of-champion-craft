#include "StdAfx.h"
#include "Iceblock.h"
#include "GameplayState.h"


CIceblock::CIceblock(void) : CUnit(UT_ICEBLOCK)
{
	SetHP(20);
	SetMaxHP(20);
	SetAttack(0);
	SetSpeed(0);
	SetRange(0);
	SetEXPValue(5);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\iceblock.png",L"IceBlock",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CIceblock::~CIceblock(void)
{
}

void CIceblock::Render(void)
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"IceBlock"),
		m_sWorldPos.nPosX- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY- (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}

