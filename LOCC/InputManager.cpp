#include "StdAfx.h"
#include "InputManager.h"

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

void CInputManager::Update(float fElapsedTime)
{
}
void CInputManager::Input(void)
{

}