#include "StdAfx.h"
#include "AbilityManager.h"
#include "Ability.h"

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
}


bool CAbilityManager::UseAbility(CAbility* pToUse, CTile* pTargetTile)
{
	
	return false;
}

void CAbilityManager::LoadAbilities( void )
{
	int num = NUMSPELLS;
	for( int i = 0; i < num; i++ )
	{
		TiXmlDocument doc;
		switch(i)
		{
		case SP_TESTSPELL:
			{
				if( doc.LoadFile( "Assets/Ability/test.xml") == false )
					return;
			}
			break;
		}

		TiXmlElement* pRoot = doc.RootElement();
		if( pRoot == nullptr )
			return;

		m_vAbilities.clear();

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

			pTile = pRoot->NextSiblingElement("Tile");
		}

		GAME_PHASE gPhase;
		if( phase == 0 )
			gPhase = GP_ATTACK;
		else
			gPhase = GP_MOVE;

		bool bAttack;
		if( attack == 0 )
			bAttack = true;
		else
			bAttack = false;

		CAbility* ab = new CAbility(pos, ap, cooldown, range, target,
			gPhase, bAttack, luaFile, particleFile, spellname);
		
		switch(i)
		{
		case SP_TESTSPELL:
			{
				std::pair<SPELL_TYPE, CAbility*> tmp;
				tmp.first = SP_TESTSPELL;
				tmp.second = ab;
				m_vAbilities.push_back(tmp);
			}
			break;
		}
	}
}

void CAbilityManager::Initialize(void)
{
}
void CAbilityManager::Shutdown(void)
{
}