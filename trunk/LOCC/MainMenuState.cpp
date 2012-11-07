#include "StdAfx.h"
#include "MainMenuState.h"
#include "StateStack.h"
#include "GameplayState.h"
#include "GameManager.h"
#include "SaveSlotState.h"
#include "OptionsMenuState.h"
#include "CreditsState.h"
#include "HelpMenuState.h"
#include "MultiplayerState.h"
#include "SocketServer.h"
#include "StringTable.h"
#include "SoundManager.h"
#include "GameModeState.h"
#include "AbilityManager.h"
//CMainMenuState* CMainMenuState::s_Instance = nullptr;

CMainMenuState::CMainMenuState(void)
{

}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	selected = 0;
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	swordid = CGraphicsManager::GetInstance()->GetID(_T("mainmenubg"));
	blueguyid = CGraphicsManager::GetInstance()->GetID(_T("warriorblue"));
	redguyid = CGraphicsManager::GetInstance()->GetID(_T("warriorred"));
	//m_pBitmapFont = new CBitmapFont();
	CInputManager::GetInstance()->SetInMenu(true);
	CStateStack::GetInstance()->SetRenderTopOnly(true);
	m_pBitmapFont = new CBitmapFont();
	int soundvolume = 0;
	int musicvolume = 0;
	bool windowed = false;
	bool IsModern = true;
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
#ifdef ARCADE_BUILD
	windowed = false;
#endif
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(float(musicvolume*0.01f));
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(float(soundvolume*0.01f));
	CGame::GetInstance()->SetIsWindowed(windowed);
	StringTable::GetInstance()->SetLanguage(IsModern);
	if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CSoundManager::
		GetInstance()->GetID(_T("MainMenuMusic"))))
	{
		CSoundManager::GetInstance()->Stop(CSoundManager::GetInstance()->
			GetID(_T("AttackPhaseMusic")));
		CSoundManager::GetInstance()->Stop(CSoundManager::GetInstance()->
			GetID(_T("MovementPhaseMusic")));
		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->
			GetID(_T("MainMenuMusic")),true,true);
	}
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
void CMainMenuState::Exit(void)
{
	delete m_pBitmapFont;
	m_pBitmapFont = nullptr;
	CStateStack::GetInstance()->SetRenderTopOnly(false);
	CInputManager::GetInstance()->SetInMenu(false);
}

void CMainMenuState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_ACCEPT:
		{
			if(selected == 0)
			{
				CStateStack::GetInstance()->Push(CGameModeState::GetInstance());
			}
			else if(selected == 1)
			{
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 2)
			{
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else if(selected == 3)
			{
				CStateStack::GetInstance()->Push(CCreditsState::GetInstance());
			}
			else if(selected == 4)
			{
				CStateStack::GetInstance()->Push(CHelpMenuState::GetInstance());
				CStateStack::GetInstance()->SetRenderTopOnly(true);
			}
			else
			{
				CInputManager::GetInstance()->SetRunning(false);
				CStateStack::GetInstance()->Pop();
			}
			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_UP:
		{
			if(selected != 0)
				selected--;
			else
				selected = 5;

		CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	case INPUT_DOWN:
		{
			if(selected != 5)
				selected++;
			else
				selected = 0;

			CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
			break;
		}
	}
}

void CMainMenuState::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if (pDI->KeyPressed(DIK_G))
	{
		CSocketClient::GetInstance()->Initialize();
	}
	else if (pDI->KeyPressed(DIK_H))
	{
		CSocketClient::GetInstance()->Shutdown();
	}
	else if (pDI->KeyPressed(DIK_M))
	{
		CStateStack::GetInstance()->Push(CMultiplayerState::GetInstance());
	}
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);

	CSGD_TextureManager::GetInstance()->Draw(blueguyid,0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(redguyid,290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(swordid,15,-5,0.7f,0.7f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	if(selected == 0)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Start").c_str(),360,200,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Start").c_str(),360,200,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 1)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Load").c_str(),364,250,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Load").c_str(),364,250,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 2)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Options").c_str(),343,300,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Options").c_str(),343,300,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 3)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Credits").c_str(),348,350,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Credits").c_str(),348,350,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 4)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Help").c_str(),365,400,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Help").c_str(),365,400,0.7f,D3DXCOLOR(255,255,255,255));
	}
	if(selected == 5)
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Exit").c_str(),364,450,0.7f,D3DXCOLOR(150,150,0,255));
	}
	else
	{
		m_pBitmapFont->Print(StringTable::GetInstance()->GetString
		("Exit").c_str(),364,450,0.7f,D3DXCOLOR(255,255,255,255));
	}

}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState s_Instance;
	return &s_Instance;
}
