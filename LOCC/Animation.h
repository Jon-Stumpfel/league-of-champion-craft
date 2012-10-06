#pragma once

class CFrame;

// Had to put in some values change to what is needed ~Ryan
enum UnitType { Archer, Calvary, Swordsmen, Skeleton, Champion };
enum AnimType { Walk, Attack, Cast_Spell_1, Cast_Spell_2 };

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

