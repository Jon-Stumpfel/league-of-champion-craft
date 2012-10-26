#include "StdAfx.h"
#include "AbilityManager.h"
#include "Ability.h"
#include "ScriptManager.h"
#include "TileManager.h"
#include "GameplayState.h"
#include "GraphicsManager.h"
#include "Unit.h"
#include "SoundManager.h"

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

void CAbilityManager::UseAbility(CAbility* pToUse, CTile* pTargetTile, CUnit* pCaster, CTile* TileCharged)
{
	// Tells the scriptmanager to run the lua code for the specified spell
	CScriptManager* pSM = CScriptManager::GetInstance();
	pSM->Execute(pToUse, pTargetTile, pCaster, TileCharged);
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

		case SP_TEST:
			{
				if(doc.LoadFile("Assets/Ability/test.xml") == false)
					return;
			}
			break;

		case SP_CHARGE:
			{
				if(doc.LoadFile("Assets/Ability/Charge.xml") == false)
					return;
			}
			break;
		case SP_CARTOGRAPHY:
			{
				if(doc.LoadFile("Assets/Ability/cartography.xml") == false)
					return;
			}
			break;
		case SP_DESTROYFOREST:
			{
				if(doc.LoadFile("Assets/Ability/destroyforest.xml") == false)
					return;
			}
			break;
		case SP_HEALBURST:
			{
				if(doc.LoadFile("Assets/Ability/healburst.xml") == false)
					return;
			}
			break;
		case SP_RALLY:
			{
				if(doc.LoadFile("Assets/Ability/rally.xml") == false)
					return;
			}
			break;
		case SP_PATHFINDER:
			{
				if(doc.LoadFile("Assets/Ability/pathfinder.xml") == false)
					return;
			}
			break;
		case SP_RAISEMOUNTAIN:
			{
				if(doc.LoadFile("Assets/Ability/raisemountain.xml") == false)
					return;
			}
			break;

		case SP_STAND:
			{
				if( doc.LoadFile("Assets/Ability/Stand.xml") == false )
					return;
			}
			break;
		case SP_RAISEDEAD:
			{
				if( doc.LoadFile("Assets/Ability/raisedead.xml") == false )
					return;
			}
			break;
			case SP_VOLLEY:
			{
				if( doc.LoadFile("Assets/Ability/volley.xml") == false )
					return;
			}
			break;

			case SP_ICEBOLT:
			{
				if( doc.LoadFile("Assets/Ability/icebolt.xml") == false )
					return;
			}
			break;

			case SP_MAGIC:
				{
					if( doc.LoadFile("Assets/Ability/magicmissile.xml") == false )
						return;
				}
				break;

			case SP_LIGHTBOLT:
			{
				if( doc.LoadFile("Assets/Ability/lightningbolt.xml") == false )
					return;
			}
			break;

			case SP_FIREWEP:
				{
					if( doc.LoadFile("Assets/Ability/firewep.xml") == false )
						return;
				}
				break;

			case SP_LIGHTSTRIKE:
				{
					if( doc.LoadFile("Assets/Ability/lightningstrike.xml") == false )
						return;
				}
				break;
			case SP_EXPSHOT:
				{
					if( doc.LoadFile("Assets/Ability/ExplosiveShot.xml") == false )
						return;
				}
				break;

		default:
			continue;
		}

		TiXmlElement* pRoot = doc.RootElement();
		if( pRoot == nullptr )
			return;

		int phase, attack, target, cooldown, ap, range, ID, face;
		const char* spellname, *luaFile, *particleFile, *iconFile, *soundFile;

		pRoot->Attribute("Phase", &phase);
		pRoot->Attribute("Attack", &attack);
		spellname = pRoot->Attribute("SpellName");
		pRoot->Attribute("Target", &target);
		pRoot->Attribute("Cooldown", &cooldown);
		pRoot->Attribute("APCost", &ap);
		pRoot->Attribute("Range", &range);
		luaFile = pRoot->Attribute("LuaPath");
		particleFile = pRoot->Attribute("ParticlePath");
		iconFile = pRoot->Attribute("IconPath");
		soundFile = pRoot->Attribute("SoundPath");
		pRoot->Attribute("Facing", &face);
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

		
		CGraphicsManager *pGM = CGraphicsManager::GetInstance();
		TCHAR conversion[100];	
		mbstowcs_s(nullptr, conversion, iconFile, _TRUNCATE);
		TSTRING img = conversion;

		TCHAR conversion2[100];	
		mbstowcs_s(nullptr, conversion2, spellname, _TRUNCATE);
		TSTRING name = conversion2;

		pGM->LoadImageW( _T("Assets/HUD/") + img, name, D3DCOLOR_ARGB(255, 255, 255, 255) );
		ID = pGM->GetID(name);
		
		TCHAR conversion3[100];	
		mbstowcs_s(nullptr, conversion3, soundFile, _TRUNCATE);
		TSTRING sound = conversion3;

		CSoundManager* pSM = CSoundManager::GetInstance();
		pSM->LoadSound(_T("Assets/Sounds/") + sound, name, false);

		GAME_PHASE gPhase;
		if( phase == 0 )
			gPhase = GP_ATTACK;
		else
			gPhase = GP_MOVE;

		bool Face;
		if( face == 0 )
			Face = false;
		else
			Face = true;

		bool bAttack;
		if( attack == 0 )
			bAttack = false;
		else
			bAttack = true;

		CAbility* ab = new CAbility(pos, ap, cooldown, range, target,
			gPhase, bAttack, luaFile, particleFile, spellname, ID);

		ab->SetSound(pSM->GetID(name));
		ab->SetIfFacing(Face);

		switch(i)
		{
			case SP_FIREBALL:
				{	
					ab->SetIsMove(false);
					ab->SetType(SP_FIREBALL);
						ab->m_szInterfaceIcon = name;
					ab->SetParticleType(PT_FIRE);
					ab->SetDamage(15);
					ab->SetDescription("You Know it, You love it, The fireball! This ones burns up most targets.");
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_FIREBALL;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_HEAL:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_HEAL);
					ab->SetParticleType(TEST);
					ab->m_szInterfaceIcon = name;
					ab->SetDamage(-8);
					ab->SetDescription("The Champion closes the wounds of a select unit, channeling the  healing mysticism");
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_HEAL;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_SHIELD:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_SHIELD);
					ab->SetParticleType(TEST);
					ab->m_szInterfaceIcon = name;
					ab->SetDamage(0);
					ab->SetDescription("The Champion puts a magical barrier around a unit, protecting it from damage");
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_SHIELD;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_SPEED:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_SPEED);
					ab->SetParticleType(TEST);
					ab->SetDamage(0);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("The Champion shifts the ground under his unit's feet, causing them to be able to move faster");
					std::pair<SPELL_TYPE,CAbility*> tmp;
					tmp.first = SP_SPEED;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_TEST:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_TEST);
					ab->SetParticleType(TEST);
					ab->m_szInterfaceIcon = name;
					ab->SetDamage(10);
					ab->SetDescription("Test spell for testing");
					std::pair<SPELL_TYPE,CAbility*> tmp;
					tmp.first = SP_TEST;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_CHARGE:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_CHARGE);
					ab->SetParticleType(TEST);
					ab->m_szInterfaceIcon = name;
					ab->SetDamage(6);
					ab->SetDescription("CHARGE!!! The Cavalry rushes straight into the enemy ranks, crushing many units as they speed up");
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_CHARGE;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_CARTOGRAPHY:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_CARTOGRAPHY);
					ab->SetParticleType(PT_CARTOGRAPHY);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Create a map and give it to target unit, letting the unit move through forests and mountains with ease");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_CARTOGRAPHY;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_DESTROYFOREST:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_DESTROYFOREST);
					ab->SetParticleType(PT_DESTROYFOREST);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Chop down a forest to raze it down to simple plains");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_DESTROYFOREST;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_HEALBURST:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_HEALBURST);
					ab->SetParticleType(PT_HEALCROSS);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Release a burst of holy energy, healing all units around you. Heals 8 HP to all units in range.");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_HEALBURST;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);

				}
				break;
			case SP_RALLY:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_RALLY);
					ab->SetParticleType(PT_RALLY);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Give a rousing speech to motivate units to fight harder! +2 Damage to all friendly units in range.");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_RALLY;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_PATHFINDER:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_PATHFINDER);
					ab->SetParticleType(PT_PATHFINDER);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Teaches nearby units the art of locating ideal paths through rough terrain. Friendly units in range move through forest and mountain for 1 AP.");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_PATHFINDER;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);

				}
				break;
			case SP_RAISEMOUNTAIN:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_RAISEMOUNTAIN);
					ab->SetParticleType(PT_RAISEMOUNTAIN);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Calls forth the rock and the dirt from the earth, raising a mountain from any non-resource tile.");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_RAISEMOUNTAIN;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);

				}
				break;

			case SP_STAND:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_STAND);
					ab->SetParticleType(PT_STAND);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Guy stands still for a little while");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_STAND;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

				case SP_VOLLEY:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_VOLLEY);
					ab->SetParticleType(PT_BLOOD);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("shit being shot at other shit");
					ab->SetDamage(12);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_VOLLEY;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
			case SP_RAISEDEAD:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_RAISEDEAD);
					ab->SetParticleType(PT_RAISEDEAD);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Brings any unit back to life as a skeleton. Can only be cast on a tile with a tombstone");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_RAISEDEAD;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_MAGIC:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_MAGIC);
					ab->SetParticleType(PT_MAGIC);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("Its a missile made of magic.");
					ab->SetDamage(8);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_MAGIC;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_ICEBOLT:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_ICEBOLT);
					ab->SetParticleType(PT_ICEBOLT);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("A chilling icicle shot from the fingertips of a champion, freezing foes in the tracks.");
					ab->SetDamage(6);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_ICEBOLT;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_LIGHTBOLT:
			{
					ab->SetIsMove(false);
					ab->SetType(SP_LIGHTBOLT);
					ab->SetParticleType(PT_LIGHTBOLT);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("The hero calls down a bolt of lightning down on a targeted tile.");
					ab->SetDamage(9);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_LIGHTBOLT;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
			break;

			case SP_FIREWEP:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_FIREWEP);
					ab->SetParticleType(PT_FIREWEP);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("The hero sets fire to his allies weapons.");
					ab->SetDamage(0);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_FIREWEP;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_LIGHTSTRIKE:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_LIGHTSTRIKE);
					ab->SetParticleType(PT_LIGHTBOLT);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("The hero uses a powerful lightning strike to stun the enemy for the turn.");
					ab->SetDamage(12);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_LIGHTSTRIKE;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;

			case SP_EXPSHOT:
				{
					ab->SetIsMove(false);
					ab->SetType(SP_EXPSHOT);
					ab->SetParticleType(PT_EXPLODE);
					ab->m_szInterfaceIcon = name;
					ab->SetDescription("The hero uses a powerful explosive Arrow");
					ab->SetDamage(8);
					std::pair<SPELL_TYPE, CAbility*> tmp;
					tmp.first = SP_EXPSHOT;
					tmp.second = ab;
					m_vAbilities.push_back(tmp);
				}
				break;
		}
	}

	// Custom melee attack
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
	pAbility->SetParticleType(TEST);
	pAbility->SetDescription("I don't know what to say. Invoking Unit's damage and range is used to caluaute the range of attack as well as the damage done");
	int zz = CGraphicsManager::GetInstance()->GetID(_T("meleeattackicon"));
	pAbility->SetIconID(zz);
	std::pair<SPELL_TYPE, CAbility*> tmp;
	tmp.first = SP_MELEEATTACK;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// Custom range attack
	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_bIsMove = false;
	pAbility->m_bIsAttack = true;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nPhase = GP_ATTACK;
	pAbility->m_nRange = 3;
	pAbility->m_nCooldown = 0;
	pAbility->SetParticleType(TEST);
	pAbility->m_vPattern.push_back(Vec2D(0, 0));
	pAbility->m_szInterfaceIcon = TSTRING(_T("rangeattackicon"));
	pAbility->SetType(SP_ARCHERRANGEDATTACK);
	pAbility->SetDescription("I don't know what to say. Invoking Unit's damage and range is used to caluaute the range of attack as well as the damage done");
	zz = CGraphicsManager::GetInstance()->GetID(_T("rangeattackicon"));
	pAbility->SetIconID(zz);
	tmp.first = SP_ARCHERRANGEDATTACK;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// Custom move ability
	pAbility = new CAbility();
	pAbility->m_nAPCost = 0;
	pAbility->m_bIsMove = true;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_szInterfaceIcon = TSTRING(_T("moveicon"));
	pAbility->SetType(SP_MOVE);
	pAbility->SetDamage(0);
	pAbility->SetDescription("Allows you to move things from places");
	zz = CGraphicsManager::GetInstance()->GetID(_T("moveicon"));
	pAbility->SetIconID(zz);
	tmp.first = SP_MOVE;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// custom champ bar ability
	pAbility = new CAbility();
	pAbility->m_nAPCost = 0;
	pAbility->m_nNumTargets = -1;
	pAbility->m_szInterfaceIcon = TSTRING(_T("champspellicon"));
	pAbility->SetParticleType(TEST);
	pAbility->SetType(SP_CHAMPSPELL);
	pAbility->SetDamage(0);
	pAbility->SetDescription("The delicous pie of spells");
	pAbility->m_nRange = 0;
	zz = CGraphicsManager::GetInstance()->GetID(_T("champspellicon"));
	pAbility->SetIconID(zz);
	tmp.first = SP_CHAMPSPELL;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// custom archer spawn ability
	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nRange = 2;
	pAbility->m_bIsMove = false;
	pAbility->SetDamage(0);
	pAbility->m_nPhase = GP_MOVE;
	pAbility->SetParticleType(TEST);
	pAbility->SetDescription("");
	pAbility->m_szInterfaceIcon = TSTRING(_T("archerportrait"));
	zz = CGraphicsManager::GetInstance()->GetID(_T("archerportrait"));
	pAbility->SetIconID(zz);
	pAbility->SetType(SP_SPAWNARCHER);
	tmp.first = SP_SPAWNARCHER;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// custom swordsman spawn ability
	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_nNumTargets = 1;
	pAbility->m_bIsMove = false;
	pAbility->SetDamage(0);
	pAbility->m_nRange = 2;
	pAbility->SetParticleType(TEST);
	pAbility->m_nPhase = GP_MOVE;
	pAbility->m_szInterfaceIcon = TSTRING(_T("swordsmanportrait"));
	pAbility->SetDescription("");
	zz = CGraphicsManager::GetInstance()->GetID(_T("swordsmanportrait"));
	pAbility->SetIconID(zz);
	pAbility->SetType(SP_SPAWNSWORD);
	tmp.first = SP_SPAWNSWORD;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	// custom calvery spawn ability
	pAbility = new CAbility();
	pAbility->m_nAPCost = 1;
	pAbility->m_nNumTargets = 1;
	pAbility->m_nRange = 2;
	pAbility->SetDamage(0);
	pAbility->m_bIsMove = false;
	pAbility->m_nPhase = GP_MOVE;
	pAbility->SetParticleType(TEST);
	pAbility->m_szInterfaceIcon = TSTRING(_T("cavalryportrait"));
	pAbility->SetDescription("");
	zz = CGraphicsManager::GetInstance()->GetID(_T("cavalryportrait"));
	pAbility->SetIconID(zz);
	pAbility->SetType(SP_SPAWNCALV);
	tmp.first = SP_SPAWNCALV;
	tmp.second = pAbility;
	m_vAbilities.push_back(tmp);

	//// custom calvery spawn ability
	//pAbility = new CAbility();
	//pAbility->m_nAPCost = 5;
	//pAbility->m_nNumTargets = 1;
	//pAbility->m_nRange = 2;
	//pAbility->SetDamage(0);
	//pAbility->m_bIsMove = false;
	//pAbility->m_nPhase = GP_MOVE;
	//pAbility->SetParticleType(TEST);
	//pAbility->m_szInterfaceIcon = TSTRING(_T("iceblockportrait"));
	//pAbility->SetDescription("The hero uses his power of freezing stuff to make an iceblock");
	//zz = CGraphicsManager::GetInstance()->GetID(_T("iceblockportrait"));
	//pAbility->SetIconID(zz);
	//pAbility->SetType(SP_ICEBLOCK);
	//tmp.first = SP_SPAWNCALV;
	//tmp.second = pAbility;
	//m_vAbilities.push_back(tmp);

	SetRanges();
}

void CAbilityManager::SetRanges( void )
{
	// Set range of 0 pattern
	m_vRange0.push_back(Vec2D(0, 0));
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

	int size = (int)pattern.size()-1;
	if( face == 2 ) // S
	{
		for( int i = size; i >= 0; i-- )
		{
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX;
			tmp.nPosY = -pattern[i].nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 0 ) // N
	{
		for( int i = size; i >= 0; i-- )
		{
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX;
			tmp.nPosY = pattern[i].nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 1 ) // E
	{
		for( int i = size; i >= 0; i-- )
		{
			int x = pattern[i].nPosX;
			pattern[i].nPosX = pattern[i].nPosY;
			pattern[i].nPosY = x;
			Vec2D tmp;
			tmp.nPosX = -pattern[i].nPosX;
			tmp.nPosY = pattern[i].nPosY;
			TilePos.push_back(tmp);
		}
	}
	else if( face == 3 ) // W
	{
		for( int i = size; i >= 0; i-- )
		{
			int x = pattern[i].nPosX;
			pattern[i].nPosX = pattern[i].nPosY;
			pattern[i].nPosY = x;
			Vec2D tmp;
			tmp.nPosX = pattern[i].nPosX;
			tmp.nPosY = -pattern[i].nPosY;
			TilePos.push_back(tmp);
		}
	}

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
	else if (range == 4 )
		return m_vRange4;
	else if (range == 0 )
		return m_vRange0;
	else 
		return m_vRange0;
}
