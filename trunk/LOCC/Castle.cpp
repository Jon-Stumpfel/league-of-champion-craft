#include "StdAfx.h"
#include "Castle.h"
#include "GameplayState.h"


CCastle::CCastle(void) : CUnit(UT_CASTLE)
{
	SetHP(500);
	SetAttack(0);
	SetSpeed(0);
	SetFacing(0);
	SetRange(0);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = UT_CASTLE;
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\castle.png",L"Castle",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CCastle::~CCastle(void)
{
	delete m_sAnimStruct;
}

void CCastle::Render( void )
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Castle"),
		m_sWorldPos.nPosX + 16 - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - 6- CGameplayState::GetInstance()->GetCamOffsetY(),
		0.25f,0.25f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}

void CCastle::Update( float fElapsedTime )
{

}

