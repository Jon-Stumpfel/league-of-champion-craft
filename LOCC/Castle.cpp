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
	// TODO: Setup abilities when they are in place	
}


CCastle::~CCastle(void)
{
}

void CCastle::Render( void )
{
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
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"CastleB"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-60,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.5f,0.5f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,D3DXCOLOR(255,255,255,255));
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"CastleR"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-60,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.5f,0.5f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,D3DXCOLOR(255,255,255,255));
	}
}