#pragma once

class CFrame;

// Had to put in some values change to what is needed ~Ryan

class CAnimation
{

public:

	CAnimation(void);
	~CAnimation(void);
	void Render( void );
	void Update( float fElapsedTime );
	void SetLooping(bool m_bSetByThis) { m_bLooping = m_bSetByThis;}
	bool GetLooping() {return m_bLooping;}
	void SetPath(const char*m_ccSetByThis) {m_ccImagePath = m_ccSetByThis;}
	const char* GetPath() {return m_ccImagePath;}
private:
	std::vector< CFrame* > m_vAnimVec;
	bool m_bLooping;
	const char* m_ccImagePath;
};

