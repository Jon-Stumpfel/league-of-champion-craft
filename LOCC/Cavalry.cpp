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
	SetEXPValue(100);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	// TODO: Setup abilities when they are in place
}


CCavalry::~CCavalry(void)
{
}
void CCavalry::Render(void)
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
	if(this->GetPlayerID() == 0)
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"CavalryB"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"CavalryR"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
}