#include "StdAfx.h"
#include "Hero.h"
#include "GameplayState.h"
#include "AbilityManager.h"


CHero::CHero(void) : CUnit(UT_HERO)
{
	SetHP(50);
	SetMaxHP(50);
	SetAttack(900);
	SetSpeed(4);
	SetRange(1);
	SetEXPValue(0);

	SetHasAttacked(false);
	SetShielded(false);
	SetIsMoving(false);

	CGraphicsManager::GetInstance()->LoadImageW(L"Assets/Animations/champion.png",L"Champion",D3DCOLOR_ARGB(255,255,255,255));


	// TODO: Setup abilities when they are in place
	 
	// Finds specified spell for the Hero
	CAbilityManager * pAM = CAbilityManager::GetInstance();
	//GiveSpell(SP_TEST);
	GiveSpell(SP_CARTOGRAPHY);
	//GiveSpell(SP_SPEED);
	GiveSpell(SP_HEAL);
	GiveSpell(SP_FIREBALL);
	GiveSpell(SP_SHIELD);
}

void CHero::GiveSpell(SPELL_TYPE type)
{
	m_vSpells.push_back(CAbilityManager::GetInstance()->GetAbility(type));
}
CHero::~CHero(void)
{
}

void CHero::Render(void)
{
	D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
	if (GetHasAttacked())
		color = D3DCOLOR_XRGB(90, 90, 90);
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Champion"),
		(m_sWorldPos.nPosX + 24)- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX() -20,
		(m_sWorldPos.nPosY - 6) - (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY() - 20,
		1.0f,1.0f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,color);
}
