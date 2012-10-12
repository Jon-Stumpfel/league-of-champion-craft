#include "StdAfx.h"
#include "PauseState.h"
#include "SaveSlotState.h"
#include "OptionsMenuState.h"
#include "MainMenuState.h"
#include "GraphicsManager.h"
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
	woss << "GAME PAUSED";
	static int r = 255, g = 0,b = 255;
	static int redAmt = 1, greenAmt = 1;
	r -= redAmt;
	g += greenAmt;
	//b -= 1;

	if (r < 1 || r > 254)
		redAmt *= -1;
	if (g < 1 || g > 254)
		greenAmt *= -1;
	if (b < 0)
		b = 255;

	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 335, 150, r, g,b);

	CSGD_Direct3D::GetInstance()->DrawTextW(_T("Resume Game"), 350, 180, 255, 255, 255);
	CSGD_Direct3D::GetInstance()->DrawTextW(_T("Options"), 350, 210, 255, 255, 255);

	CSGD_Direct3D::GetInstance()->DrawTextW(_T("Save/Load"), 350, 240, 255, 255, 255);
	CSGD_Direct3D::GetInstance()->DrawTextW(_T("Exit to Menu"), 350, 270, 255, 255, 255);
	CGraphicsManager::GetInstance()->DrawArrow(330, 190 + m_nVerticalChoice * 30, 255, 255, 255);
}
