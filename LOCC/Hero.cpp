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

	CGraphicsManager::GetInstance()->LoadImageW(L"Assets\\Animations\\champion.png",L"Champion",D3DCOLOR_ARGB(255,255,255,255));


	// TODO: Setup abilities when they are in place
	CAbility* pAbility = new CAbility();
	pAbility->m_nAPCost = 3;
	pAbility->m_nCooldown = 1;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_nNumTargets = 1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("shieldicon"));
	SetShielded(true);
	PushDebuff(pAbility);

	// Finds specified spell for the Hero
	CAbilityManager * pAM = CAbilityManager::GetInstance();
	m_vSpells.push_back(pAM->GetAbility(SP_TESTSPELL));
	m_vSpells.push_back(pAM->GetAbility(SP_CONE));

	/*pAbility = new CAbility();
	pAbility->m_nAPCost = 3;
	pAbility->m_nCooldown = 1;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_nNumTargets = 1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("shieldicon"));	
	m_vSpells.push_back(pAbility);

	pAbility = new CAbility();
	pAbility->m_nAPCost = 3;
	pAbility->m_nCooldown = 1;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_nNumTargets = 1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("shieldicon"));	
	m_vSpells.push_back(pAbility);

	pAbility = new CAbility();
	pAbility->m_nAPCost = 3;
	pAbility->m_nCooldown = 1;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_nNumTargets = 1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("shieldicon"));
	m_vSpells.push_back(pAbility);*/
}


CHero::~CHero(void)
{
	delete GetDebuff(0);
}

void CHero::Render(void)
{
	Vec2D tempanchorpoint = CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetAnchorPoint();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(L"Champion"),
		(m_sWorldPos.nPosX + 24)- (tempanchorpoint.nPosX/4*3) - CGameplayState::GetInstance()->GetCamOffsetX(),
		(m_sWorldPos.nPosY - 6) - (tempanchorpoint.nPosY/4*3) - CGameplayState::GetInstance()->GetCamOffsetY(),
		0.55f,0.55f,&CAnimationManager::GetInstance()->GetFrame(*m_sAnimStruct).GetRect(),0,
		0,0,D3DCOLOR_ARGB(255,255,255,255));
}
