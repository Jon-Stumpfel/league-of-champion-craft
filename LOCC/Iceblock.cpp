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
	// TODO: Setup abilities when they are in place
}


CIceblock::~CIceblock(void)
{
}

void CIceblock::Render(void)
{

	D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
	if (GetHasAttacked())
		color = D3DCOLOR_XRGB(90, 90, 90);
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect().top - tempanchorpoint.nPosY;
	RECT temprecta = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct)->GetRect();
	RECT temprectb = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"IceBlock"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
}

