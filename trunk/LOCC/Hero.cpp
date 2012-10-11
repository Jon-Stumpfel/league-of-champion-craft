#include "StdAfx.h"
#include "Hero.h"
#include "GameplayState.h"


CHero::CHero(void) : CUnit(UT_HERO)
{
	SetHP(50);
	SetMaxHP(50);
	SetAttack(9);
	SetSpeed(4);
	SetFacing(0);
	SetRange(1);
	SetEXPValue(0);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = UT_HERO;
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\champion.png",L"Champion",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CHero::~CHero(void)
{
	delete m_sAnimStruct;
}

void CHero::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Champion"),
		m_sWorldPos.nPosX + 24 - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - 6- CGameplayState::GetInstance()->GetCamOffsetY(),
		0.55f,0.55f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}
