#pragma once
class CSoundManager
{

public:

	int GetID( TSTRING szSoundID );
	void LoadSound( TSTRING szFilename, TSTRING szReference, bool isMusic = true );
	void RemoveSound( TSTRING szReference, bool isMusic = true, int ID = -1 );
	static CSoundManager* GetInstance( void );
	static void DeleteInstance( void );
	void Shutdown( void );
	void Play( int ID, bool isLooping = false, bool isMusic = true );
	void Stop( int ID, bool isMusic = true );

private:

	CSoundManager(void);
	~CSoundManager(void);
	CSoundManager(const CSoundManager&);
	CSoundManager& operator=(const CSoundManager&);

	typedef std::pair<TSTRING, int> SoundID;
	std::vector<SoundID> m_vSoundIDs;

	static CSoundManager* s_Instance;
};

