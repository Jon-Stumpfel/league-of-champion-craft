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

		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
	if (GetHasAttacked())
		color = D3DCOLOR_XRGB(90, 90, 90);
	RECT soldierRect = {m_sWorldPos.nPosX + 24, 
						m_sWorldPos.nPosY - 6, 
						0, 
						0};
	//RECT temprect = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect();
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().top - tempanchorpoint.nPosY;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Archer"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX),
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-15,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,color);
}

