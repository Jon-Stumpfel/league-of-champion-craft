#include "StdAfx.h"
#include "Archer.h"
#include "GameplayState.h"
CArcher::CArcher(void) : CUnit(UT_ARCHER)
{
	SetHP(12);
	SetAttack(6);
	SetSpeed(4);
	SetFacing(0);
	SetRange(3);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	
	m_sAnimStruct = new UnitAnimation();
	m_sAnimStruct->animationType = AT_WALK_W;
	m_sAnimStruct->fCurrentTime = 0.0f;
	m_sAnimStruct->unitType = UT_ARCHER;
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer.png",L"Archer",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CArcher::~CArcher(void)
{
	delete m_sAnimStruct;
}

void CArcher::Render(void)
{
	               //   int x = (nFakeTileWidth / 2 * GetPos().nPosX) - (nFakeTileHeight / 2 * GetPos().nPosY);
                  //  int y = (nFakeTileWidth / 2 * GetPos().nPosX) + (nFakeTileHeight  / 2 * GetPos().nPosY);
	RECT soldierRect = {m_sWorldPos.nPosX + 24, 
						m_sWorldPos.nPosY - 6, 
						0, 
						0};
	RECT temprect = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct);
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Archer"),
		soldierRect.left  - CGameplayState::GetInstance()->GetCamOffsetX(),
		soldierRect.top  - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}

