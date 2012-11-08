#include "StdAfx.h"
#include "TutorialTextState.h"
#include "StateStack.h"
#include "GraphicsManager.h"


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
	
}

void CTutorialTextState::Exit()
{
	++m_nNextText;
}

void CTutorialTextState::Input(INPUT_ENUM input)
{
	if( input== INPUT_ACCEPT)
		CStateStack::GetInstance()->Pop();
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
			m_cFont.Print("League of champion craft is a turned based battle arena game.",170,150,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("The game is broken up into two phases: Movement and Attack.",170,200,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("During each phase, You will use Action Points, or AP, to make decisions on which units to move and which units to attack.",170,250,.4f,D3DCOLOR_XRGB(210,210,210),440);
			m_cFont.Print("Each Player starts with 30 AP. Action Points are deducted for every action the he or she makes during his or her turn.",170,330,.4f,D3DCOLOR_XRGB(210,210,210),440);
			m_cFont.Print("All units are in the phase together: all units will always move first, then after the movement, they will attack. ",170,410,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All battles start with a coin toss to see who goes first...",170,500,.4f,D3DCOLOR_XRGB(210,210,210),430);
			
				
			break;
		}
	case TTU_MOVEMENT:
		{
			m_cFont.Print("MOVEMENT",340,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("Movement is done by selected a unit: move the cursor over the unit you wish to move, then hit accept.",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("With the unit selected, select the unit's move icon, this changes the color of the cursor. ",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Now you can move the cursor to see the path the unit will move:",170,250,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Green tiles are where the unit can move and red tiles are outside the unit’s speed and can’t be moved to.",170,295,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All units have a speed, which allows them to a certain amount of tiles, regardless of how much it costs to move across them.",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Each tile’s AP cost is based on how difficult it is for a unit to navigate across the tile.",170,430,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Plains cost one AP. Forests cost two AP. Mountains cost three AP.",170,490,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	case TTU_ATTACK:
		{
			m_cFont.Print("ATTACKING",340,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("During the attack phase, Your units can attack ANY units in range, including allies. ",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Basic attacks are done by selecting the attack icon, moving the Cursor on the unit you wish to attack, and then hit accept to attack that unit",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("All units have a special ability that can only be performed during the attack phase, each with special conditions about their use. ",170,280,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("If the range indictor is red, it means that the attack or ability is not currently available, because of special conditions, being the wrong state",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			m_cFont.Print("Sometimes you won’t have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,450,.4f,D3DCOLOR_XRGB(210,210,210),430);
			
			break;
		}
	case TTU_SPELLS:
		{
			m_cFont.Print("SPELL Panel",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			m_cFont.Print("During the either phase, You can buy spells for your champion from the Champion Spell Panel",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Basic attacks are done by selecting the attack icon, moving the Cursor on the unit you wish to attack, and then hit accept to attack that unit",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("All units have a special ability that can only be performed during the attack phase, each with special conditions about their use. ",170,280,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("If the range indictor is red, it means that the attack or ability is not currently available, because of special conditions, being the wrong state",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Sometimes you won’t have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,450,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	case TTU_MOVETACTICS:
		{
			m_cFont.Print("MOVE TACTICS",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			//m_cFont.Print("During the either phase, You can buy spells for your champion from the Champion Spell Panel",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Basic attacks are done by selecting the attack icon, moving the Cursor on the unit you wish to attack, and then hit accept to attack that unit",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("All units have a special ability that can only be performed during the attack phase, each with special conditions about their use. ",170,280,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("If the range indictor is red, it means that the attack or ability is not currently available, because of special conditions, being the wrong state",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Sometimes you won’t have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,450,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	case TTU_ATTACKTACTICS:
		{
			m_cFont.Print("ATTACK TACTICS",320,100,.4f,D3DCOLOR_XRGB(210,210,210));
			//m_cFont.Print("During the either phase, You can buy spells for your champion from the Champion Spell Panel",170,120,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Basic attacks are done by selecting the attack icon, moving the Cursor on the unit you wish to attack, and then hit accept to attack that unit",170,190,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("All units have a special ability that can only be performed during the attack phase, each with special conditions about their use. ",170,280,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("If the range indictor is red, it means that the attack or ability is not currently available, because of special conditions, being the wrong state",170,360,.4f,D3DCOLOR_XRGB(210,210,210),430);
			//m_cFont.Print("Sometimes you won’t have any units in range of the enemy, causing you to skip over the attack phase, like now ...",170,450,.4f,D3DCOLOR_XRGB(210,210,210),430);
			break;
		}
	}	
}

void CTutorialTextState::Update(float fElapsedTime)
{

}