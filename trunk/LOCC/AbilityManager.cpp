#include "StdAfx.h"
#include "AbilityManager.h"
#include "Ability.h"
#include "ScriptManager.h"
#include "TileManager.h"
#include "GameplayState.h"
#include "Unit.h"

CAbilityManager* CAbilityManager::s_Instance = nullptr;

CAbilityManager::CAbilityManager(void)
{
}


CAbilityManager::~CAbilityManager(void)
{
	
}

CAbilityManager* CAbilityManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CAbilityManager();

	return s_Instance;
}

void CAbilityManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}

CAbility* CAbilityManager::GetAbility( SPELL_TYPE type )
{
	// Finds the ability that is given
	for( unsigned int i = 0; i < m_vAbilities.size(); i++ )
	{
		if( m_vAbilities[i].first == type )
			return m_vAbilities[i].second;
	}

	return nullptr;
}

void CAbilityManager::UseAbility(CAbility* pToUse, CTile* pTargetTile, CUnit* pCaster)
{
	// Tells the scriptmanager to run the lua code for the specified spell
	CScriptManager* pSM = CScriptManager::GetInstance();
	pSM->Execute(pToUse, pTargetTile, pCaster);
}

void CAbilityManager::LoadAbilities( void )
{
	int num = NUMSPELLS;
	for( int i = 0; i < num; i++ )
	{
		TiXmlDocument doc;
		switch(i)
		{
		case SP_FIREBALL:
			{
				if (doc.LoadFile("Assets/Ability/fireball.xml") == false)
					return;
			}
			break;
		case SP_HEAL:
			{
				if (doc.LoadFile("Assets/Ability/Heal.xml") ==false)
					return;
			}
			break;
		case SP_SHIELD:
			{
				if (doc.LoadFile("Assets/Ability/Shield.xml") ==false)
					return;
			}
			break;
		case SP_SPEED:
			{
				if(doc.LoadFile("Assets/Ability/Speed.xml") == false)
					return;
			}
			break;
		default:
			continue;
		}

		TiXmlElement* pRoot = doc.RootElement();
		if( pRoot == nullptr )
			return;

		int phase, attack, target, cooldown, ap, range;
		const char* spellname, *luaFile, *particleFile;

		pRoot->Attribute("Phase", &phase);
		pRoot->Attribute("Attack", &attack);
		spellname = pRoot->Attribute("SpellName");
		pRoot->Attribute("Target", &target);
		pRoot->Attribute("Cooldown", &cooldown);
		pRoot->Attribute("APCost", &ap);
		pRoot->Attribute("Range", &range);
		luaFile = pRoot->Attribute("LuaPath");
		particleFile = pRoot->Attribute("ParticlePath");
		vector<Vec2D> pos;
		TiXmlElement* pTile = pRoot->FirstChildElement("Tile");

		while( pTile != nullptr )
		{
			Vec2D p;
			pTile->Attribute("PosY", &p.nPosY);
			pTile->Attribute("PosX", &p.nPosX);
			pos.push_back(p);

			pTile = pTile->NextSiblingElement();
		}

		GAME_PHASE gPhase;
		if( phase == 0 )
			gPhase = GP_ATTACK;
		else
			gPhase = GP_MOVE;

		bool bAttack;
		if( attack == 0 )
			bAttack = false;
		else
			bAttack = true;

		CAbility* ab = new CAbility(pos, ap, cooldown, range, target,
			gPhase, bAttack, luaFile, particleFile, spellname);
		
		switch(i)
		{
			case SP_FIREBALL:
				{	
					ab->SetIsMove(false);
					ab->SetIcon(TSTRING(_T("fireballicon")));
					ab->SetType(SP_FIREBALL);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_FIREBALL;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_HEAL:
				{
					ab->SetIsMove(false);
					ab->SetIcon(TSTRING(_T("healspellicon")));
					ab->SetType(SP_HEAL);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_HEAL;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_SHIELD:
				{
					ab->SetIsMove(false);
					ab->SetIcon(TSTRING(_T("shieldspellicon")));
					ab->SetType(SP_SHIELD);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_SHIELD;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_SPEED:
				{
					ab->SetIsMove(false);
					ab->SetIcon(TSTRING(_T("moveicon")));
					ab->SetType(SP_SPEED);
					std::pair<SPELL_TYPE,CAbility*> tmp;
					tmp.first = SP_SPEED;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
		}
	}

	// Custom melee/range attack abilities
	CAbility* pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_bIsMove = false;
	pAbility->m_bIsAttack = true;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nPhase = GP_ATTACK;
	pAbility->m_nRange = 1;
	pAbility->m_nCooldown = 0;
	pAbility->m_vPattern.push_back(Vec2D(0, 0));
	pAbility->m_szInterfaceIcon = TSTRING(_T("meleeattackicon"));
	pAbility->SetType(SP_MELEEATTACK);
	std::pair<SPELL_TYPE, CAbility*> tmp;
	tmp.first = SP_MELEEATTACK;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_bIsMove = false;
	pAbility->m_bIsAttack = true;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nPhase = GP_ATTACK;
	pAbility->m_nRange = 3;
	pAbility->m_nCooldown = 0;
	pAbility->m_vPattern.push_back(Vec2D(0, 0));
	pAbility->m_szInterfaceIcon = TSTRING(_T("rangeattackicon"));
	pAbility->SetType(SP_ARCHERRANGEDATTACK);
	tmp.first = SP_ARCHERRANGEDATTACK;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);


	pAbility = new CAbility();
	pAbility->m_nAPCost = 0;
	pAbility->m_bIsMove = true;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_szInterfaceIcon = TSTRING(_T("moveicon"));
	pAbility->SetType(SP_MOVE);
	tmp.first = SP_MOVE;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);


	pAbility = new CAbility();
	pAbility->m_nAPCost = 0;
	pAbility->m_nNumTargets = -1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("champspellicon"));
	pAbility->SetType(SP_CHAMPSPELL);
	tmp.first = SP_CHAMPSPELL;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	SetRanges();
}

void CAbilityManager::SetRanges( void )
{
	// Set range of 1 pattern
	m_vRange1.push_back(Vec2D(-1, 0));
	m_vRange1.push_back(Vec2D(1, 0));
	m_vRange1.push_back(Vec2D(0, -1));
	m_vRange1.push_back(Vec2D(0, 1));

	// Set range of 2 pattern
	m_vRange2.push_back(Vec2D(-1, 0));
	m_vRange2.push_back(Vec2D(1, 0));
	m_vRange2.push_back(Vec2D(0, -1));
	m_vRange2.push_back(Vec2D(0, 1));
	m_vRange2.push_back(Vec2D(-2, 0));
	m_vRange2.push_back(Vec2D(2, 0));
	m_vRange2.push_back(Vec2D(0, -2));
	m_vRange2.push_back(Vec2D(0, 2));
	m_vRange2.push_back(Vec2D(-1, -1));
	m_vRange2.push_back(Vec2D(1, 1));
	m_vRange2.push_back(Vec2D(1, -1));
	m_vRange2.push_back(Vec2D(-1, 1));

	// Set range of 3 pattern
	m_vRange3.push_back(Vec2D(-1, 0));
	m_vRange3.push_back(Vec2D(1, 0));
	m_vRange3.push_back(Vec2D(0, -1));
	m_vRange3.push_back(Vec2D(0, 1));
	m_vRange3.push_back(Vec2D(-2, 0));
	m_vRange3.push_back(Vec2D(2, 0));
	m_vRange3.push_back(Vec2D(0, -2));
	m_vRange3.push_back(Vec2D(0, 2));
	m_vRange3.push_back(Vec2D(-1, -1));
	m_vRange3.push_back(Vec2D(1, 1));
	m_vRange3.push_back(Vec2D(1, -1));
	m_vRange3.push_back(Vec2D(-1, 1));

	m_vRange3.push_back(Vec2D(-2, -1));
	m_vRange3.push_back(Vec2D(-1, -2));
	m_vRange3.push_back(Vec2D(0, -3));
	m_vRange3.push_back(Vec2D(1, -2));
	m_vRange3.push_back(Vec2D(2, -1));
	m_vRange3.push_back(Vec2D(3, 0));
	m_vRange3.push_back(Vec2D(2, 1));
	m_vRange3.push_back(Vec2D(1, 2));
	m_vRange3.push_back(Vec2D(0, 3));
	m_vRange3.push_back(Vec2D(-1, 2));
	m_vRange3.push_back(Vec2D(-2, 1));
	m_vRange3.push_back(Vec2D(-3, 0));

	// Set range of 4 pattern
	m_vRange4.push_back(Vec2D(-1, 0));
	m_vRange4.push_back(Vec2D(1, 0));
	m_vRange4.push_back(Vec2D(0, -1));
	m_vRange4.push_back(Vec2D(0, 1));
	m_vRange4.push_back(Vec2D(-2, 0));
	m_vRange4.push_back(Vec2D(2, 0));
	m_vRange4.push_back(Vec2D(0, -2));
	m_vRange4.push_back(Vec2D(0, 2));
	m_vRange4.push_back(Vec2D(-1, -1));
	m_vRange4.push_back(Vec2D(1, 1));
	m_vRange4.push_back(Vec2D(1, -1));
	m_vRange4.push_back(Vec2D(-1, 1));
	m_vRange4.push_back(Vec2D(-2, -1));
	m_vRange4.push_back(Vec2D(-1, -2));
	m_vRange4.push_back(Vec2D(0, -3));
	m_vRange4.push_back(Vec2D(1, -2));
	m_vRange4.push_back(Vec2D(2, -1));
	m_vRange4.push_back(Vec2D(3, 0));
	m_vRange4.push_back(Vec2D(2, 1));
	m_vRange4.push_back(Vec2D(1, 2));
	m_vRange4.push_back(Vec2D(0, 3));
	m_vRange4.push_back(Vec2D(-1, 2));
	m_vRange4.push_back(Vec2D(-2, 1));
	m_vRange4.push_back(Vec2D(-3, 0));
	m_vRange4.push_back(Vec2D(0, 4));
	m_vRange4.push_back(Vec2D(1, 3));
	m_vRange4.push_back(Vec2D(2, 2));
	m_vRange4.push_back(Vec2D(3, 1));
	m_vRange4.push_back(Vec2D(4, 0));
	m_vRange4.push_back(Vec2D(3, -1));
	m_vRange4.push_back(Vec2D(2, -2));
	m_vRange4.push_back(Vec2D(1, -3));
	m_vRange4.push_back(Vec2D(0, -4));
	m_vRange4.push_back(Vec2D(-1, -3));
	m_vRange4.push_back(Vec2D(-2, -2));
	m_vRange4.push_back(Vec2D(-3, -1));
	m_vRange4.push_back(Vec2D(-4, 0));
	m_vRange4.push_back(Vec2D(-3, 1));
	m_vRange4.push_back(Vec2D(-2, 2));
	m_vRange4.push_back(Vec2D(-1, 3));
	// toally sucks...
}

void CAbilityManager::Initialize(void)
{
}
void CAbilityManager::Shutdown(void)
{
	for( unsigned int i = 0; i < m_vAbilities.size(); i++ )
	{
		delete m_vAbilities[i].second;
		m_vAbilities.erase(m_vAbilities.begin() + i);
		i--;
	}
	int i =0;
}

std::vector< Vec2D > CAbilityManager::GetProperFacing( int face, CAbility* pAbility, CTile* pTile )
{
	std::vector< Vec2D > pattern = pAbility->GetPattern();
	std::vector< Vec2D > TilePos;

	//if( face == 0 ) // S
	//{
	//	for( unsigned int i = 0; i < pattern.size(); i++ )
	//	{
	//		pattern[i].nPosX = -pattern[i].nPosX;
	//		pattern[i].nPosY = -pattern[i].nPosY;
	//		Vec2D tmp;
	//		tmp.nPosX = pattern[i].nPosX + pUnit->GetPos().nPosX;
	//		tmp.nPosY = pattern[i].nPosY + pUnit->GetPos().nPosY;
	//		TilePos.push_back(tmp);
	//	}
	//}
	//else if( face == 1 ) // N
	//{
		for( unsigned int i = 0; i < pattern.size(); i++ )
		{
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX + pTile->GetPosition().nPosX;
			tmp.nPosY = pattern[i].nPosY + pTile->GetPosition().nPosY;
			TilePos.push_back(tmp);
		}
	//}
	//else if( face == 2 ) // E
	//{
	//	for( unsigned int i = 0; i < pattern.size(); i++ )
	//	{
	//		int x = pattern[i].nPosX;
	//		pattern[i].nPosX = -pattern[i].nPosY;
	//		pattern[i].nPosY = x;
	//		Vec2D tmp;
	//		tmp.nPosX = pattern[i].nPosX + pUnit->GetPos().nPosX;
	//		tmp.nPosY = pattern[i].nPosY + pUnit->GetPos().nPosY;
	//		TilePos.push_back(tmp);
	//	}
	//}
	//else if( face == 3 ) // W
	//{
	//	for( unsigned int i = 0; i < pattern.size(); i++ )
	//	{
	//		int x = pattern[i].nPosX;
	//		pattern[i].nPosX = pattern[i].nPosY;
	//		pattern[i].nPosY = -x;
	//		Vec2D tmp;
	//		tmp.nPosX = pattern[i].nPosX + pUnit->GetPos().nPosX;
	//		tmp.nPosY = pattern[i].nPosY + pUnit->GetPos().nPosY;
	//		TilePos.push_back(tmp);
	//	}
	//}

	return TilePos;
}

std::vector< Vec2D > CAbilityManager::GetRange( int range )
{
	if( range == 1 )
		return m_vRange1;
	else if( range == 2 )
		return m_vRange2;
	else if( range == 3 )
		return m_vRange3;
	else
		return m_vRange4;
}
