#include "StdAfx.h"
#include "Cavalry.h"
#include "GameplayState.h"


CCavalry::CCavalry(void) : CUnit(UT_CAVALRY)
{
	SetHP(22);
	SetMaxHP(22);
	SetAttack(6);
	SetSpeed(5);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(15);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = UT_CAVALRY;
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\calvary.png",L"Cavalry",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CCavalry::~CCavalry(void)
{
	delete m_sAnimStruct;
}
void CCavalry::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Cavalry"),
		m_sWorldPos.nPosX + 16 - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - 8- CGameplayState::GetInstance()->GetCamOffsetY(),
		0.72f,0.77f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}