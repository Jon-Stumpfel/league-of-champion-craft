#pragma once

#include "StdAfx.h"

class CAudioManager
{
	static CAudioManager* GetInstance(void);
	static void DeleteInstance(void);	

	int GetID(std::string sSoundName);
	void LoadSound(std::string sFilename);
	void UnloadSound(std::string sFilename);
	void PlaySound(std::string sSoundName, bool bLoop);
	void StopSound(std::string sSoundName);

	void Initialize(void);
	void Shutdown(void);

private:

	CAudioManager(void);
	~CAudioManager(void);
	CAudioManager(const CAudioManager&);
	CAudioManager& operator=(const CAudioManager&);

	static CAudioManager* s_Instance;

	typedef std::pair<std::string, int> SoundID;

	std::vector<SoundID> m_vSoundIDs;
};

