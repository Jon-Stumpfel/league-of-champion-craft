#include "StdAfx.h"
#include "Iceblock.h"
#include "GameplayState.h"


CIceblock::CIceblock(void) : CUnit(UT_ICEBLOCK)
{
	SetHP(20);
	SetMaxHP(20);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(5);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = UT_ICEBLOCK;
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\iceblock.png",L"IceBlock",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CIceblock::~CIceblock(void)
{
	delete m_sAnimStruct;
}

void CIceblock::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"IceBlock"),
		m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}

