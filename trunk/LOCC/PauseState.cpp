#include "StdAfx.h"
#include "PauseState.h"
#include "SaveSlotState.h"
#include "OptionsMenuState.h"
#include "MainMenuState.h"

#include "StateStack.h"
CPauseState::CPauseState(void)
{
}


CPauseState::~CPauseState(void)
{
}

CPauseState* CPauseState::GetInstance()
{
	static CPauseState s_Instance;
	return &s_Instance;
}

void CPauseState::Enter(void)
{
	m_nVerticalChoice = 0;
}
void CPauseState::Exit(void)
{
}
void CPauseState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_DOWN:
		{
			m_nVerticalChoice++;
			if (m_nVerticalChoice > 3)
				m_nVerticalChoice = 0;
		}
		break;
	case INPUT_UP:
		{
			m_nVerticalChoice--;
			if (m_nVerticalChoice < 0)
				m_nVerticalChoice = 3;
		}
		break;
	case INPUT_ACCEPT:
		{
			switch (m_nVerticalChoice)
			{
			case 0:
				CStateStack::GetInstance()->Pop();
				break;
			case 1:
				CStateStack::GetInstance()->Push(COptionsMenuState::GetInstance());
				break;
			case 2:
				CStateStack::GetInstance()->Push(CSaveSlotState::GetInstance());
				break;
			case 3:
				CStateStack::GetInstance()->Switch(CMainMenuState::GetInstance());
				break;
			}
		}
		break;
	case INPUT_CANCEL:
		CStateStack::GetInstance()->Pop();
		break;
	}
}
void CPauseState::Update(float fElapsedTime)
{
}
void CPauseState::Render(void)
{

	// lol rainbow text just for the time being
	std::wostringstream woss;
	woss << "GAME PAUSED    currentMenuCHoice: " << m_nVerticalChoice;
	static int r = 255, g = 0,b = 255;
	r -= 1;
	g += 1;
	b -= 1;

	if (r < 0)
		r = 255;
	if (g > 255)
		g = 0;
	if (b < 0)
		b = 255;

	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 350, 120, r, g,b);
}