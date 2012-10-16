#include "StdAfx.h"
#include "InputManager.h"
#include "GameManager.h"
#include "StateStack.h"
#include "Player.h"

CInputManager* CInputManager::s_Instance = nullptr;

CInputManager::CInputManager(void)
{
}


CInputManager::~CInputManager(void)
{
}


CInputManager* CInputManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CInputManager();
	return s_Instance;
}
void CInputManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
}
void CInputManager::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	CSGD_DirectInput::GetInstance()->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS);
}
void CInputManager::Shutdown(void)
{

}
void CInputManager::Update(float fElapsedTime)
{
}
bool CInputManager::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	int nCurrentPlayerID = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
	int nRAmount = pDI->JoystickGetRStickYAmount(0);
	if (nRAmount > 0)
	{
		int x = 9;
	}
	if (pDI->KeyDown(DIK_W) || pDI->JoystickGetRStickDirDown (DIR_UP, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_UP);
	}
	if (pDI->KeyDown(DIK_S) || pDI->JoystickGetRStickDirDown(DIR_DOWN, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_DOWN);
	}
	if (pDI->KeyDown(DIK_A) || pDI->JoystickGetRStickDirDown(DIR_LEFT, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_LEFT);
	}
	if (pDI->KeyDown(DIK_D) || pDI->JoystickGetRStickDirDown(DIR_RIGHT, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementX() < -nMouseSensitivity)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_LEFT);
	}
	else if (pDI->MouseMovementX() > nMouseSensitivity)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_RIGHT);
	}
	if (pDI->MouseMovementY() < -nMouseSensitivity)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_UP);
	}
	else if (pDI->MouseMovementY() > nMouseSensitivity)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CAM_DOWN);
	}

	static int nYValue = 0;

	nYValue += pDI->JoystickGetLStickYAmount(nCurrentPlayerID);
	if (nYValue > 13000)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_DOWN);
		nYValue = 0;
	}
	if (nYValue < -13000)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_UP);
		nYValue = 0;
	}

	static int nXValue = 0;

	nXValue += pDI->JoystickGetLStickXAmount(nCurrentPlayerID);
	if (nXValue > 13000)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_RIGHT);
		nXValue = 0;
	}
	if (nXValue < -13000)
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_LEFT);
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_UP, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_UP);
		nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_LEFT) || pDI->JoystickGetLStickDirPressed(DIR_LEFT, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_LEFT, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_LEFT);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_RIGHT) || pDI->JoystickGetLStickDirPressed(DIR_RIGHT, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_RIGHT, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_RIGHT);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_DOWN, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_DOWN);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(0, nCurrentPlayerID))
		CStateStack::GetInstance()->GetTop()->Input(INPUT_ACCEPT);
	if (pDI->KeyPressed(DIK_Z) || pDI->JoystickButtonPressed(1, nCurrentPlayerID))
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CANCEL);
	if (pDI->KeyPressed(DIK_I) || pDI->JoystickButtonPressed(7, nCurrentPlayerID))
		CStateStack::GetInstance()->GetTop()->Input(INPUT_START);
	if (pDI->KeyPressed(DIK_SPACE) || pDI->JoystickButtonPressed(3, nCurrentPlayerID))
		CStateStack::GetInstance()->GetTop()->Input(INPUT_SELECT);

	return true;
}