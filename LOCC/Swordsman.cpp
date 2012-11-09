#include "StdAfx.h"
#include "Swordsman.h"
#include "GameplayState.h"

CSwordsman::CSwordsman(void) : CUnit(UT_SWORDSMAN)
{
	SetHP(25);
	SetMaxHP(25);
	SetAttack(8);
	SetSpeed(3);
	SetRange(1);
	SetEXPValue(75);

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
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"SwordsmanB"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"SwordsmanR"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
}
