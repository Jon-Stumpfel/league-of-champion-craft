#include "StdAfx.h"
#include "TutorialTextState.h"
#include "StateStack.h"
#include "GraphicsManager.h"
#include "SoundManager.h"


CTutorialTextState::CTutorialTextState(void)
{
	m_nNextText=0;
}


CTutorialTextState::~CTutorialTextState(void)
{
}

CTutorialTextState* CTutorialTextState::GetInstance()
{
	static CTutorialTextState s_Instance;
	return &s_Instance;
}

void CTutorialTextState::Enter()
{
	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-034
	// BUG FIX START
	/////////////////////////////////////////////////////////////////
	//turn the music down while I'm talking, and turned my voice up, just in case...
	CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(0.0f);
	CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(0.6f);

	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-034
	/////////////////////////////////////////////////////////////////
}

void CTutorialTextState::Exit()
{
	m_nNextText++;
}

void CTutorialTextState::Input(INPUT_ENUM input)
{
	switch(input)
	{
	default:
		break;
	case INPUT_ACCEPT:
	{
		switch (m_nNextText)
		{
		case TTU_INTRO:// if the intro clip is still playing, stop it
			if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Intro"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("Intro")));
			break;
		case TTU_MOVEMENT:
				if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Move"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("Move")));
			break;
		case TTU_ATTACK:
				if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Attack"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("Attack")));
			break;
		case TTU_SPELLS:
				if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Spell"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("Spell")));
			break;
		case TTU_MOVETACTICS:
				if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("MTactics"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("MTactics")));
			break;
		case TTU_ATTACKTACTICS:
				if (CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("ATactics"))))
				CSGD_XAudio2::GetInstance()->SFXStopSound(CSoundManager::GetInstance()->GetID(_T("ATactics")));
			break;

		}
	}
		CStateStack::GetInstance()->Pop();
	}
}


void CTutorialTextState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 80, -10, 1.3f, 1.2f);
	m_cFont.Print("Press Accept to continue",400,550,.3f,D3DCOLOR_XRGB(210,210,210));

	switch (m_nNextText)
	{
	case TTU_INTRO:
		{
			m_cFont.Print("WELCOME CHAMPIONS TO THE LEAGUE",180,100,.4f,D3DCOLOR_XRGB(210,210,210));
/////////////////////////////////////////////////////////////////
// BUG FIX
// Reference Bug # BB-007
// BUG FIX START
/////////////////////////////////////////////////////////////////
			m_cFont.Print("League of champion craft is a turn based battle arena, where the objective is to defeat the enemy champion or destroy his base.",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
											     // fixed  ^ That
/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-007
/////////////////////////////////////////////////////////////////
			m_cFont.Print("The game is broken up into two phases: Movement and Attack.",170,200,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("During each phase, You will use action points, or AP, to make decisions on which units to move and which units to attack with. ",170,250,.4f,D3DCOLOR_XRGB(210,210,210),440);

/////////////////////////////////////////////////////////////////
// BUG FIX
// Reference Bug # BB-010
// BUG FIX START
/////////////////////////////////////////////////////////////////			
			m_cFont.Print("Each Player starts with 30 AP. Action Points are deducted for every action that he or she makes during his or her turn.",170,330,.4f,D3DCOLOR_XRGB(210,210,210),440);
																								//fixed ^ this
/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-010
/////////////////////////////////////////////////////////////////
			m_cFont.Print("The game is broken up into two phases: Movement and Attack.",170,200,.4f,D3DCOLOR_XRGB(210,210,210),430);
			
			m_cFont.Print("All units are in the phase together: all units will always move first, then after the movement, they will attack. ",170,410,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All battles start with a coin toss to see who goes first...",170,500,.4f,D3DCOLOR_XRGB(210,210,210),430);	
			break;
		}
	case TTU_MOVEMENT:
		{
			m_cFont.Print("MOVEMENT",340,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("Movement is done by selecting a unit: move the cursor over the unit you wish to move, then hit accept.",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("With the unit selected, his ability icons will show up on the HUD.",170,170,.4f,D3DCOLOR_XRGB(210,210,210),430);
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-013
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("Select the unit's move icon... this will change the color of the cursor.",170,220,.4f,D3DCOLOR_XRGB(210,210,210),430); // Replaced a funky ' with an actual ' here...
			m_cFont.Print("Now you can move the cursor to see the path the unit will travel:",170,260,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Green tiles are where the unit can traverse and red tiles are outside the unit's movement speed and can't be moved to.",170,310,.4f,D3DCOLOR_XRGB(210,210,210),430); // ... and here.
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-013
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("All units have a speed rating, which allows them to move a certain amount of tiles, regardless of how much it costs to traverse them. ",170,390,.4f,D3DCOLOR_XRGB(210,210,210),430);
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-015
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-022
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("Units can't move if the player runs out of AP. Each tile's AP cost is based on how difficult it is for a unit to navigate across the tile. ",170,470,.4f,D3DCOLOR_XRGB(210,210,210),430); // Replaced a funky ' with an actual '
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-015
			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-022
			/////////////////////////////////////////////////////////////////
			break;
		}
	case TTU_ATTACK:
		{
			m_cFont.Print("ATTACKING",340,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("During the attack phase, Your units can attack ANY units in range, including allies. ",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Basic attacks are done by selecting the attack icon, moving the cursor on the unit you wish to attack, and then pressing accept to attack that unit",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All units have a special ability that can only be performed during the attack phase, each with special conditions about their use. ",170,280,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("If the range indictor is red, it means that the attack or ability is not currently available, because of special conditions, being the wrong state",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-027
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("Sometimes you won't have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,460,.4f,D3DCOLOR_XRGB(210,210,210),430);
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-027
			/////////////////////////////////////////////////////////////////
			break;
		}
	case TTU_SPELLS:
		{
			m_cFont.Print("ABILITIES",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("During the either phase, you can buy spells for him from the Champion Abilities Panel.",170,130,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("To open the Abilities Panel: select your champion and select his Special Ability.",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);

/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-030
/////////////////////////////////////////////////////////////////			
			m_cFont.Print("Champion start out with four blank scroll slots, selecting one will open the Ability-Book You can choose from four diverse spell trees: Elemental, Physical, Support and Epic. ",170,250,.4f,D3DCOLOR_XRGB(210,210,210),430);
																													//deleted word  ^ here
/////////////////////////////////////////////////////////////////
// BUG FIX END  Reference # BB-030
/////////////////////////////////////////////////////////////////			
			m_cFont.Print("Ability have an AP cost, a cool-down, and a phase that the spell can be used in.",170,370,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Abilities can do damage, heal Allies, hinder enemies, and change the world around you. ",170,440,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	case TTU_MOVETACTICS:
		{
			m_cFont.Print("MOVE TACTICS",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("You should spend movement positioning unit for an attack and Capturing buildings to add to your resources. Wood and Metal are used to make more troops.  ",170,130,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("More Units can be summoned from the castle, at a cost of resources.",170,250,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Most Champion Spells that buff units are done during the movement phase.",170,320,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Archer receive a range in increase on mountain tiles",170,400,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All units get a chance to dodge on forest tiles",170,460,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	case TTU_ATTACKTACTICS:
		{
			m_cFont.Print("ATTACK TACTICS",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			/////////////////////////////////////////////////////////////////
			// BUG FIX
			// Reference Bug # BB-032
			// BUG FIX START
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("Archer's Volley can only be done if the archer doesn't move during the movement phase.",170,150,.4f,D3DCOLOR_XRGB(210,210,210),430); // Replaced a funky ' with an actual '
			/////////////////////////////////////////////////////////////////
			// BUG FIX END  Reference # BB-032
			/////////////////////////////////////////////////////////////////
			m_cFont.Print("Most Champion Spells allow the Champion to attack outside of his basic melee range.",170,230,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Cavalry's Charge moves the unit as well as does damage to all in his path, but the last tile moved must be open.",170,300,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Champion Spell can be replaced for other spells from the book by pressing the swap spell button",170,380,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Owned spells will start in cool-down if they are swap out for another spell. ",170,460,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Sometimes you won't have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,450,.4f,D3DCOLOR_XRGB(210,210,210),430);
			
			break;
		}
	}	
}

void CTutorialTextState::Update(float fElapsedTime)
{
	switch (m_nNextText)
	{
	case TTU_INTRO:
		{	
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Intro"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("Intro")), false);
			break;
		}
	case TTU_MOVEMENT:
		{
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Move"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("Move")), false);
			break;
		}
	case TTU_ATTACK:
		{
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Attack"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("Attack")), false);
			break;
		}
	case TTU_SPELLS:
		{
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("Spell"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("Spell")), false);
			
			break;
		}
	case TTU_MOVETACTICS:
		{
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("MTactics"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("MTactics")), false);
			
			break;
		}
	case TTU_ATTACKTACTICS:
		{
			if(!CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(CSoundManager::GetInstance()->GetID(_T("ATactics"))))
				CSGD_XAudio2::GetInstance()->SFXPlaySound(CSoundManager::GetInstance()->GetID(_T("ATactics")), false);
			
			break;
		}
	}
}