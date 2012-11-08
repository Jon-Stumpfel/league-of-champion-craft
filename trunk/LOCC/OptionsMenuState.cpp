#include "StdAfx.h"
#include "OptionsMenuState.h"
#include "StateStack.h"
#include "StringTable.h"
#include "AbilityManager.h"
#include "SoundManager.h"
#include "GraphicsManager.h"
COptionsMenuState::COptionsMenuState(void)
{
}
COptionsMenuState::~COptionsMenuState(void)
{
}
void COptionsMenuState::Enter(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	m_pBitmapFont = new CBitmapFont();
	pTM = CSGD_TextureManager::GetInstance();
	jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\options_menu.png"), D3DXCOLOR(255,255,255,255));
	Scroll = pTM->LoadTexture(_T("Assets\\Menus\\scroll.png"), D3DXCOLOR(255,255,255,255));
	TiXmlDocument doc;
	doc.LoadFile("Assets\\Menus\\Options.xml");
	TiXmlElement* pRoot = doc.RootElement();
	TiXmlElement* Option = pRoot->FirstChildElement("Option");
	while(Option != nullptr)
	{
		Option->Attribute("SoundVolume", &soundvolume);
		Option->Attribute("MusicVolume", &musicvolume);
		int temp = 0;
		Option->Attribute("Fullscreen", &temp);
		if(temp == 0)
			windowed = false;
		else
			windowed = true;
		temp = 0;
		Option->Attribute("IsModern", &temp);
		if(temp == 0)
			IsModern = false;
		else
			IsModern = true;
		Option = Option->NextSiblingElement("Option");
	}
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume*0.01f));
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume*0.01f));
}
void COptionsMenuState::Exit(void)
{
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );  
	doc.LinkEndChild( decl );  

	TiXmlElement * root = new TiXmlElement( "Options" );  
	doc.LinkEndChild( root );  
	TiXmlElement* Options = new TiXmlElement("Option");
	root->LinkEndChild(Options);
	Options->SetAttribute("SoundVolume", soundvolume);
	Options->SetAttribute("MusicVolume", musicvolume);
	if(windowed == false)
		Options->SetAttribute("Fullscreen", 0);
	else
		Options->SetAttribute("Fullscreen", 1);
	if(IsModern == false)
		Options->SetAttribute("IsModern", 0);
	else
		Options->SetAttribute("IsModern", 1);
	doc.SaveFile("Assets\\Menus\\Options.xml");
	int temp = NUMSPELLS;
	for(int i = 0; i < temp; i++)
	{
		switch(i)
		{
		case SP_FIREBALL:
			{	
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion hurls a ball of fire at a target."));
			}
			break;

		case SP_HEAL:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion closes the wounds of a selected unit."));
			}
			break;

		case SP_SHIELD:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion shields his target, preventing damage for a turn."));
			}
			break;
		case SP_SPEED:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion increases the speed of a selected unit for a turn."));
			}
			break;

		case SP_TEST:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("Test spell for testing"));
			}
			break;

		case SP_CHARGE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Calvary rushes forward, dealing more damage for every unit hit in a line."));
			}
			break;
		case SP_CARTOGRAPHY:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("Reduces the cost of moving to one for a target unit."));
			}
			break;
		case SP_DESTROYFOREST:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion turns a target forest into a plain."));
			}
			break;
		case SP_HEALBURST:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion heals the wounds of everyone around him."));
			}
			break;
		case SP_RALLY:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("Rally the troops, increasing thier damage by 2 for a turn."));
			}
			break;

		case SP_PATHFINDER:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("Nearby units have the cost to move reduced to 1 until the end of the turn."));
			}
			break;
		case SP_RAISEMOUNTAIN:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion creates a mountain tile from any non-resource tile."));
			}
			break;
		case SP_STAND:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Swordsman gives up movement for a turn to reduce his damage by half."));
			}
			break;
		case SP_VOLLEY:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("If the Archer hasn't moved, he can prepare a shot that deals double his damage."));
			}
			break;
		case SP_RAISEDEAD:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("Brings any unit back to life as a skeleton. It can only be cast on a tile with a tombstone."));
			}
			break;
		case SP_MAGIC:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("It's a missile made of magic."));
			}
			break;
		case SP_ICEBOLT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The champion hurls a bolt of ice at a target, reducing their speed by 2 for the next turn."));
			}
			break;
		case SP_LIGHTBOLT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The hero calls a bolt of lightning down on a targeted tile."));
			}
			break;
		case SP_FIREWEP:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion sets a targets weapon ablaze, increasing thier damage by 2."));
			}
			break;
		case SP_LIGHTSTRIKE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion uses a powerful lightning strike to stun the enemy for the next turn."));
			}
			break;
		case SP_EXPSHOT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion uses a powerful explosive arrow."));
			}
			break;
		case SP_ICEAGE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion freezes all the tiles in front of him."));
			}
			break;
		case SP_HEAVYBLOW:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion strikes a target with a heavy blow."));
			}
			break;
		case SP_FIRENOVA:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion engulfs himself in flames and explodes into an unholy napalm bloom of death."));
			}
			break;
		case SP_SKILLSHOT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion uses his bow to attack a target from afar."));
			}
			break;
		case SP_LIGHTCHAIN:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion pushes lightning through all conductive targets."));
			}
			break;
		case SP_WHIRLWIND:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("A spinning attack so fast that the Champion's sheer velocity throws back units."));
			}
			break;
		case SP_PSHOT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion uses his bow to hit all targets in a line, doing 2 less damage for each target hit."));
			}
			break;
		case SP_CLEAVE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion swings his sword, hitting all targets in front of him."));
			}
			break;
		case SP_BLADESTORM:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion spins, hitting all targets in front of him."));
			}
			break;
		case SP_SWORDDANCE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion stabs all units around him."));
			}
			break;
		case SP_RUSH:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion rushes forward in a direction, dealing 2 extra damage for every unit hit."));
			}
			break;

		case SP_KILL:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion does massive damage to an enemy near him."));
			}
			break;
		case SP_FORT:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion shields his allies, decreasing their damage taken by 70% for 2 turns."));
			}
			break;

		case SP_DEATH:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion uses his secret technique to stop a target in its tracks and kills all units if they move. Champion units take 10 damage."));
			}
			break;

		case SP_MIND:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion steals the mind of one of his enemies. Doesn't work on Champion units."));
			}
			break;

		case SP_TELE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion moves a unit from one place to another."));
			}
			break;

		case SP_SAC:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion sacrifices a unit to gain an extra turn."));
			}
			break;

		case SP_MASSRAISE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion raises all dead around him."));
			}
			break;

		case SP_VAMP:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion turns his allies into vampires for a turn, letting them heal half thier basic attack damage back when they attack."));
			}
			break;

		case SP_ENCASE:
			{
				CAbilityManager::GetInstance()->GetAbility(SPELL_TYPE(i))->SetDescription(StringTable::GetInstance()->GetString("The Champion sends a wall of ice down from the sky, damaging enemies they hit."));
			}
			break;
		}
		CAbilityManager::GetInstance()->GetAbility(SP_MELEEATTACK)->SetDescription(StringTable::GetInstance()->GetString("This unit attacks with a melee weapon."));
		CAbilityManager::GetInstance()->GetAbility(SP_ARCHERRANGEDATTACK)->SetDescription(StringTable::GetInstance()->GetString("This unit attacks with a ranged weapon."));
		CAbilityManager::GetInstance()->GetAbility(SP_MOVE)->SetDescription(StringTable::GetInstance()->GetString("Allows you to move things to places."));
		CAbilityManager::GetInstance()->GetAbility(SP_MELEEATTACK)->m_strName = StringTable::GetInstance()->GetString("Melee Attack");
		CAbilityManager::GetInstance()->GetAbility(SP_ARCHERRANGEDATTACK)->m_strName = StringTable::GetInstance()->GetString("Range Attack");
		CAbilityManager::GetInstance()->GetAbility(SP_MOVE)->m_strName = StringTable::GetInstance()->GetString("Move");
		CAbilityManager::GetInstance()->GetAbility(SP_CHAMPSPELL)->m_strName = StringTable::GetInstance()->GetString("Spells");
		CAbilityManager::GetInstance()->GetAbility(SP_SPAWNARCHER)->m_strName = StringTable::GetInstance()->GetString("Spawn Archer");
		CAbilityManager::GetInstance()->GetAbility(SP_SPAWNSWORD)->m_strName = StringTable::GetInstance()->GetString("Spawn Swordsman");
		CAbilityManager::GetInstance()->GetAbility(SP_SPAWNCALV)->m_strName = StringTable::GetInstance()->GetString("Spawn Calvary");
		CAbilityManager::GetInstance()->GetAbility(SP_ICEBLOCK)->m_strName = StringTable::GetInstance()->GetString("Ice Block");
		CAbilityManager::GetInstance()->GetAbility(SP_ICEBLOCK)->SetDescription("The hero uses his power of freezing stuff to make an ice block");
		CAbilityManager::GetInstance()->GetAbility(SP_BLANK)->SetDescription(StringTable::GetInstance()->GetString("Blank parchment is blank"));
		CAbilityManager::GetInstance()->GetAbility(SP_BLANK)->m_strName = StringTable::GetInstance()->GetString("Blank Scroll");
	}
}
void COptionsMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		{
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			CStateStack::GetInstance()->Pop();
		}
		break;
	case INPUT_DOWN:
		{
			if(selected != 4)
				selected++;
			else
				selected = 0;
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_UP:
		{
			if(selected !=0)
				selected--;
			else
				selected = 4;
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_LEFT:
		{
			if(selected == 0 && soundvolume >= 0)
			{
				soundvolume-=5;
				float temp = soundvolume*0.01f;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(temp);
			}
			else if(selected == 1 && musicvolume >= 0)
			{
				musicvolume-=5;
				float temp = musicvolume*0.01f;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(temp);
			}
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_RIGHT:
		{
			if(selected == 0 && soundvolume <= 100)
			{
				soundvolume+=5;
				float temp = soundvolume*0.01f;
				CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(temp);
			}
			else if(selected == 1 && musicvolume <= 100)
			{
				musicvolume+=5;
				float temp = musicvolume*0.01f;
				CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(temp);
			}
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_ACCEPT:
		{
			if(selected == 2)
			{
				if(windowed == false)
					windowed = true;
				else
					windowed = false;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				CGame::GetInstance()->SetIsWindowed(windowed);
			}
			else if(selected == 3)
			{
				if(IsModern == false)
					IsModern = true;
				else
					IsModern = false;
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				StringTable::GetInstance()->SetLanguage(IsModern);
			}
			else if(selected == 4)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				CStateStack::GetInstance()->Pop();
			}
			break;
		}
	}
}
void COptionsMenuState::Update(float fElapsedTime)
{
}
void COptionsMenuState::Render(void)
{
	RECT* toprect = new RECT();
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 50, 30, 1.3f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, D3DXCOLOR(255,255,255,255));
	toprect->bottom = 77;
	toprect->top = 56;
	toprect->left = 152;
	toprect->right = 402;
	pTM->Draw(jcs_nImageID,275,170,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,275,270,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 89;
	toprect->bottom = 108;
	toprect->left = 184;
	toprect->right = 188;
	pTM->Draw(jcs_nImageID,303+int(1.86f*soundvolume),170,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,303+int(1.86f*musicvolume),270,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	toprect->top = 345;
	toprect->left = 254;
	toprect->bottom = 386;
	toprect->right = 295;
	pTM->Draw(jcs_nImageID,480,305,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	pTM->Draw(jcs_nImageID,480,360,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	if(windowed == false)
	{
		toprect->top = 336;
		toprect->left = 324;
		toprect->bottom = 385;
		toprect->right = 377;
		pTM->Draw(jcs_nImageID,480,305,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	}
	else
	{

	}
	if(IsModern)
	{
		toprect->top = 336;
		toprect->left = 324;
		toprect->bottom = 385;
		toprect->right = 377;
		pTM->Draw(jcs_nImageID,480,360,1.0f,1.0f,toprect,0,0,0,D3DXCOLOR(255,255,255,255));
	}
	else
	{

	}
	delete toprect;
	toprect = nullptr;
	if(selected == 0)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275,110,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275,110,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275,110,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Sound Volume").c_str(),275,110,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	if(selected == 1)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278,210,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278,210,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278,210,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Music Volume").c_str(),278,210,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 2)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),278,310,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),298,310,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),278,310,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Fullscreen").c_str(),298,310,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 3)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),178,365,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),198,365,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),178,365,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Modern English?").c_str(),198,365,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
	if(selected == 4)
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350,440,0.6f,D3DXCOLOR(150,150,0,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350,440,0.6f,D3DXCOLOR(150,150,0,255));
		}
	}
	else
	{
		if(StringTable::GetInstance()->GetIsItModern())
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350,440,0.6f,D3DXCOLOR(255,255,255,255));
		}
		else
		{
			m_pBitmapFont->Print(StringTable::GetInstance()->GetString
				("Back").c_str(),350,440,0.6f,D3DXCOLOR(255,255,255,255));
		}
	}
}
COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState s_Instance;
	return &s_Instance;
}