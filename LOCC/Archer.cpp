#include "StdAfx.h"
#include "Archer.h"
#include "GameplayState.h"
CArcher::CArcher(void) : CUnit(UT_ARCHER)
{
	SetHP(12);
	SetMaxHP(12);
	SetAttack(6);
	SetSpeed(4);
	SetRange(3);
	SetEXPValue(10);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);
	
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\archer.png",L"Archer",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CArcher::~CArcher(void)
{
}

void CArcher::Render(void)
{
	               //   int x = (nFakeTileWidth / 2 * GetPos().nPosX) - (nFakeTileHeight / 2 * GetPos().nPosY);
                  //  int y = (nFakeTileWidth / 2 * GetPos().nPosX) + (nFakeTileHeight  / 2 * GetPos().nPosY);
	RECT soldierRect = {m_sWorldPos.nPosX + 24, 
						m_sWorldPos.nPosY - 6, 
						0, 
						0};
	//RECT temprect = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect();
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Archer"),
		soldierRect.left - (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		soldierRect.top  - (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}

