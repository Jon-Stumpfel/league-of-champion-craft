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
	
	tempanimstruct = new UnitAnimation();
	tempanimstruct->animationType = AT_WALK_W;
	tempanimstruct->fCurrentTime = 0.0f;
	tempanimstruct->nCurrentFrame = 0;
	tempanimstruct->unitType = UT_ARCHER;
	this->SetAnimStruct(tempanimstruct);
	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\Footman.png",L"Archer",D3DCOLOR_ARGB(255,255,255,255));
	// TODO: Setup abilities when they are in place
}


CArcher::~CArcher(void)
{
	delete tempanimstruct;
}

void CArcher::Render(void)
{
	RECT soldierRect = {m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(), 
						m_sWorldPos.nPosX+ nFakeTileWidth - CGameplayState::GetInstance()->GetCamOffsetX(), 
						m_sWorldPos.nPosY + nFakeTileHeight - CGameplayState::GetInstance()->GetCamOffsetY()};
	RECT temprect = CAnimationManager::GetInstance()->GetFrame(*this->GetAnimStruct());
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Archer"),
		m_sWorldPos.nPosX - CGameplayState::GetInstance()->GetCamOffsetX(),
		m_sWorldPos.nPosY - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetFrame(*this->GetAnimStruct()),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));	
}

