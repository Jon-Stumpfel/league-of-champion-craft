#include "StdAfx.h"
#include "AudioManager.h"

CAudioManager* CAudioManager::s_Instance = nullptr;

CAudioManager::CAudioManager(void)
{
}


CAudioManager::~CAudioManager(void)
{
}


CAudioManager* CAudioManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CAudioManager();
	return s_Instance;
}
void CAudioManager::DeleteInstance(void)
{

}

int CAudioManager::GetID(std::string sSoundName)
{
	return -1;
}
void CAudioManager::LoadSound(std::string sFilename)
{
}
void CAudioManager::UnloadSound(std::string sFilename)
{
}
void CAudioManager::PlaySound(std::string sSoundName, bool bLoop)
{
}
void CAudioManager::StopSound(std::string sSoundName)
{
}

void CAudioManager::Initialize(void)
{
}
void CAudioManager::Shutdown(void)
{
}