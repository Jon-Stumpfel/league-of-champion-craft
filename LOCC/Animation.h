#pragma once

class CFrame;

// Had to put in some values change to what is needed ~Ryan
enum UnitType { Archer, Calvery, Swordsmen, Skeleton  };
enum AnimType { Walk, Attack };

class CAnimation
{

public:

	CAnimation(void);
	~CAnimation(void);
	void Render( void );
	void Update( float fElapsedTime );

private:

	std::vector< CFrame* > m_vAnimVec;
	bool m_bLooping;

};

