#include "StdAfx.h"
#include "InputManager.h"
#include "ControllerUnpluggedState.h"
#include "GameManager.h"
#include "StateStack.h"
#include "Player.h"
#include "SocketServer.h"

CInputManager* CInputManager::s_Instance = nullptr;

CInputManager::CInputManager(void)
{
	m_nNumJoys = 0;
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
void CInputManager::SetInMenu(bool b)
{ 
	m_bInMenu = b;
}


void CInputManager::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	CSGD_DirectInput::GetInstance()->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS);
	Running = true;
	m_bInMenu = false;

	m_nNumJoys = CSGD_DirectInput::GetInstance()->m_vpJoysticks.size();


	if (m_nNumJoys == 1)
	{
		m_pJoy1 = CSGD_DirectInput::GetInstance()->m_vpJoysticks[0];
		m_pJoyThatIsUnplugged = CSGD_DirectInput::GetInstance()->m_vpJoysticks[0];
	}
	else if (m_nNumJoys == 2)
	{
		m_pJoy1 = CSGD_DirectInput::GetInstance()->m_vpJoysticks[0];
		m_pJoyThatIsUnplugged = CSGD_DirectInput::GetInstance()->m_vpJoysticks[0];

		m_pJoy2 = CSGD_DirectInput::GetInstance()->m_vpJoysticks[1];
	}

}
void CInputManager::Shutdown(void)
{
	CSGD_DirectInput::GetInstance()->ShutdownDirectInput();
}
void CInputManager::Update(float fElapsedTime)
{
}
bool CInputManager::Input(void)
{
	
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();


	CSGD_DIJoystick* joy2 = reinterpret_cast<CSGD_DIJoystick*>(m_pJoy2);

	if (m_nNumJoys == 1)
	{
		CSGD_DIJoystick* joy1 = reinterpret_cast<CSGD_DIJoystick*>(m_pJoy1);
		if (joy1->IsUnplugged())
		{
			if (CStateStack::GetInstance()->FindState(CControllerUnpluggedState::GetInstance()) == false)
			{
				CStateStack::GetInstance()->Push(CControllerUnpluggedState::GetInstance());
				CControllerUnpluggedState::GetInstance()->SetJoyToPlug(1);

				m_pJoyThatIsUnplugged = joy1;
			}
		}
		if (reinterpret_cast<CSGD_DIJoystick*>(m_pJoyThatIsUnplugged)->IsUnplugged() == false)
		{
			if (CStateStack::GetInstance()->FindState(CControllerUnpluggedState::GetInstance()) == true)
			{
				CStateStack::GetInstance()->Pop();
			}
		}
	}
	else if (m_nNumJoys == 2)
	{
		CSGD_DIJoystick* joy1 = reinterpret_cast<CSGD_DIJoystick*>(m_pJoy1);
		CSGD_DIJoystick* joy2 = reinterpret_cast<CSGD_DIJoystick*>(m_pJoy2);

		if (joy1->IsUnplugged())
		{
			if (CStateStack::GetInstance()->FindState(CControllerUnpluggedState::GetInstance()) == false)
			{
				CStateStack::GetInstance()->Push(CControllerUnpluggedState::GetInstance());
				CControllerUnpluggedState::GetInstance()->SetJoyToPlug(1);
				m_pJoyThatIsUnplugged = joy1;
			}
		}
		else if (joy2->IsUnplugged())
		{
			if (CStateStack::GetInstance()->FindState(CControllerUnpluggedState::GetInstance()) == false)
			{
				CStateStack::GetInstance()->Push(CControllerUnpluggedState::GetInstance());
				CControllerUnpluggedState::GetInstance()->SetJoyToPlug(2);

				m_pJoyThatIsUnplugged = joy2;
			}
		}

		if (reinterpret_cast<CSGD_DIJoystick*>(m_pJoyThatIsUnplugged)->IsUnplugged() == false)
		{
			if (CStateStack::GetInstance()->FindState(CControllerUnpluggedState::GetInstance()) == true)
			{
				CStateStack::GetInstance()->Pop();
			}
		}


	}
	int nCurrentPlayerID;
	if( CGameManager::GetInstance()->GetCurrentPlayer() != nullptr )
		nCurrentPlayerID = CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID();
	else
		nCurrentPlayerID = 1;
	if (m_bInMenu)

		nCurrentPlayerID = 0;
	int nRAmount = pDI->JoystickGetRStickYAmount(0);
	if (CGameManager::GetInstance()->GetNetworkGame())
	{
		if (CGameManager::GetInstance()->GetCurrentPlayer()->GetPlayerID() != CSocketClient::GetInstance()->m_nNetworkPlayerID)
			return true;
	}
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
				if (CGameManager::GetInstance()->GetNetworkGame())
		{
		char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_UP, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
				}
		CStateStack::GetInstance()->GetTop()->Input(INPUT_UP);
		nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_LEFT) || pDI->JoystickGetLStickDirPressed(DIR_LEFT, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_LEFT, nCurrentPlayerID))
	{
				if (CGameManager::GetInstance()->GetNetworkGame())
		{
		char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_LEFT, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
				}

		std::wostringstream oss;
		oss << "InputManager: Left Key @ " << GetTickCount() << '\n';
		OutputDebugString((LPCWSTR)oss.str().c_str());
		CStateStack::GetInstance()->GetTop()->Input(INPUT_LEFT);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_RIGHT) || pDI->JoystickGetLStickDirPressed(DIR_RIGHT, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_RIGHT, nCurrentPlayerID))
	{
			if (CGameManager::GetInstance()->GetNetworkGame())
		{
			char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_RIGHT, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
			}
		std::wostringstream oss;
		oss << "InputManager: Right Key @ " << GetTickCount() << '\n';
		OutputDebugString((LPCWSTR)oss.str().c_str());
		CStateStack::GetInstance()->GetTop()->Input(INPUT_RIGHT);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN, nCurrentPlayerID) || pDI->JoystickDPadPressed(DIR_DOWN, nCurrentPlayerID))
	{
				if (CGameManager::GetInstance()->GetNetworkGame())
		{
		char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_DOWN, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
				}
		CStateStack::GetInstance()->GetTop()->Input(INPUT_DOWN);
				nYValue = 0;
		nXValue = 0;
	}
	if (pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(0, nCurrentPlayerID))
	{
		if (CGameManager::GetInstance()->GetNetworkGame())
		{
		char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_ACCEPT, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
		}
		CStateStack::GetInstance()->GetTop()->Input(INPUT_ACCEPT);
	}
	if (pDI->KeyPressed(DIK_L) || pDI->JoystickButtonPressed(4, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_BUMPERLEFT);
	}
	if (pDI->KeyPressed(DIK_R) || pDI->JoystickButtonPressed(5, nCurrentPlayerID))
	{
		CStateStack::GetInstance()->GetTop()->Input(INPUT_BUMPERRIGHT);
	}
	if (pDI->KeyPressed(DIK_Z) || pDI->KeyPressed(DIK_ESCAPE) || pDI->JoystickButtonPressed(1, nCurrentPlayerID))
	{
		if (CGameManager::GetInstance()->GetNetworkGame())
		{
		char txtbuffer[80];
		sprintf_s(txtbuffer, "%c%d", NET_INPUT_CANCEL, 0);
		send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
		}
		CStateStack::GetInstance()->GetTop()->Input(INPUT_CANCEL);
	}
	if (pDI->KeyPressed(DIK_BACKSPACE) || pDI->JoystickButtonPressed(7, nCurrentPlayerID))
	{
		if (CGameManager::GetInstance()->GetNetworkGame())
		{
			char txtbuffer[80];
			sprintf_s(txtbuffer, "%c%d", NET_INPUT_START, 0);
			send(CSocketClient::GetInstance()->m_sClientSocket, txtbuffer, 2, 0);
		}
		CStateStack::GetInstance()->GetTop()->Input(INPUT_START);
	}
	if (pDI->KeyPressed(DIK_SPACE) || pDI->JoystickButtonPressed(3, nCurrentPlayerID))
		CStateStack::GetInstance()->GetTop()->Input(INPUT_SELECT);

	return Running;
}