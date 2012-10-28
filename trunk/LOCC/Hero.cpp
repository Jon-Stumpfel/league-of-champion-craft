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

	// TODO: Setup abilities when they are in place5
	 
	// Finds specified spell for the Hero
	CAbilityManager * pAM = CAbilityManager::GetInstance();

	GiveSpell(SP_LIGHTCHAIN);
	GiveSpell(SP_LIGHTSTRIKE);
	GiveSpell(SP_HEAL);
	GiveSpell(SP_SHIELD);
	//GiveSpell(SP_LIGHTSTRIKE);
	//GiveSpell(SP_FIREWEP);
	//GiveSpell(SP_ICEBOLT);
	//GiveSpell(SP_SHIELD);

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
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetAnchorPoint();
	Vec2D tempoffset;
	tempoffset.nPosX = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect().left - tempanchorpoint.nPosX;
	tempoffset.nPosY = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect().top - tempanchorpoint.nPosY;
	RECT temprecta = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct)->GetRect();
	RECT temprectb = CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect();
	if(this->GetPlayerID() == 0)
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"ChampionB"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-15,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.75f,0.75f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
	else
	{
		CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"ChampionR"),
		(m_sWorldPos.nPosX) - CGameplayState::GetInstance()->GetCamOffsetX() - (tempoffset.nPosX)-15,
		(m_sWorldPos.nPosY) - CGameplayState::GetInstance()->GetCamOffsetY()  - (tempoffset.nPosY)-60,
		0.7f,0.7f,&CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetFrameVec()
		[CAnimationManager::GetInstance()->GetAnimation(m_sAnimStruct->unitType,m_sAnimStruct->animationType)->GetCurrFrame()].GetRect(),0,
		0,0,color);
	}
}
void CHero::ChillCooldown(void)
{
	for (int i=0; i<4;++i)
	{
		if(m_ncooldown[i]!=0)
			m_ncooldown[i]-=1;
	}
}
	CAbility* CHero::GetSpell(int i)
	{
		if ((unsigned int)(i + 1) > m_vSpells.size())
			return nullptr;
		return m_vSpells[i];
	}