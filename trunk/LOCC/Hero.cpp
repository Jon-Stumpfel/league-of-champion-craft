#include "StdAfx.h"
#include "Hero.h"
#include "GameplayState.h"
#include "AbilityManager.h"


CHero::CHero(void) : CUnit(UT_HERO)
{
	SetHP(50);
	SetMaxHP(50);
	SetAttack(9);
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
	//GiveSpell(SP_PATHFINDER);
	//GiveSpell(SP_SPEED);
	GiveSpell(SP_RAISEMOUNTAIN);
	GiveSpell(SP_DESTROYFOREST);
	GiveSpell(SP_FIREBALL);
	GiveSpell(SP_SHIELD);

	for (int i=0; i<4;++i)
		m_ncooldown[i]=0;
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
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect().top - tempanchorpoint.nPosY;
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Champion"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-20,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.9f,0.9f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,color);
}

void CHero::ChillCooldown(void)
{
	for (int i=0; i<4;++i)
	{
		if(m_ncooldown[i]!=0)
			m_ncooldown[i]-=1;
	}
}
