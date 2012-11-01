#include "StdAfx.h"
#include "SoundManager.h"
#include <vector>
#include "SGD Wrappers\CSGD_XAudio2.h"

CSoundManager* CSoundManager::s_Instance = nullptr;

CSoundManager::CSoundManager(void)
{
}


CSoundManager::~CSoundManager(void)
{
}

CSoundManager* CSoundManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CSoundManager;

	return s_Instance;
}

void CSoundManager::DeleteInstance( void )
{
	s_Instance->Shutdown();
	delete s_Instance;
}

void CSoundManager::Shutdown(void)
{
	CSGD_XAudio2* pXA = CSGD_XAudio2::GetInstance();
	pXA->ShutdownXAudio2();
}

int CSoundManager::GetID( TSTRING szSoundID )
{
	int returnID = -1;

	if( szSoundID != _T("") )
	{
		for( unsigned int i = 0; i < m_vSoundIDs.size(); ++i )
		{
			if( m_vSoundIDs[i].first == szSoundID )
				return m_vSoundIDs[i].second;
		}
	}

	return returnID;
}

void CSoundManager::LoadSound( TSTRING szFilename, TSTRING szReference, bool isMusic )
{
	CSGD_XAudio2* pXA = CSGD_XAudio2::GetInstance();
	int newID;
	if( isMusic )
		newID = pXA->MusicLoadSong(szFilename.c_str());
	else
		newID = pXA->SFXLoadSound(szFilename.c_str());

	SoundID newSoundID;
	newSoundID.first = szReference;
	newSoundID.second = newID;

	m_vSoundIDs.push_back(newSoundID);
}

void CSoundManager::RemoveSound(TSTRING szReference, bool isMusic, int ID)
{
	CSGD_XAudio2* pXA = CSGD_XAudio2::GetInstance();
	
	int newID = ID;
	if( newID == -1 )
	{
		for( unsigned int i = 0; i < m_vSoundIDs.size(); i++ )
		{
			if( m_vSoundIDs[i].first == szReference )
			{
				newID = m_vSoundIDs[i].second;
				break;
			}
		}
	}

	if( isMusic )
	{
		pXA->MusicStopSong(newID);
		pXA->MusicUnloadSong(newID);
	}
	else
	{
		pXA->SFXStopSound(newID);
		pXA->SFXUnloadSound(newID);
	}
}

void CSoundManager::Play( int ID, bool isLooping, bool isMusic )
{
	CSGD_XAudio2* pXA = CSGD_XAudio2::GetInstance();
	if( ID == -1 )
		return;

	if( isMusic )
	{
		if( pXA->MusicIsSongPlaying(ID) == false )
			pXA->MusicPlaySong(ID, isLooping);
	}
	else
	{
		if( pXA->SFXIsSoundPlaying(ID) == false )
			pXA->SFXPlaySound(ID, isLooping);
	}
}

void CSoundManager::Stop( int ID, bool isMusic )
{
	CSGD_XAudio2* pXA = CSGD_XAudio2::GetInstance();
	if( ID == -1 )
		return;

	if( isMusic )
		pXA->MusicStopSong(ID);
	else
		pXA->SFXStopSound(ID);
}
