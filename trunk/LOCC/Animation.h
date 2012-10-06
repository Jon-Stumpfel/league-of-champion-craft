#pragma once
#include "Frame.h"
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
	void SetAnimType(ANIM_TYPE temptype) {m_eAnimType = temptype;}
	ANIM_TYPE GetAnimType() {return m_eAnimType;}
	void SetUnitType(UNIT_TYPE tempunittype) {m_eUnitType = tempunittype;}
	UNIT_TYPE GetUnitType() {return m_eUnitType;}
	void SetFrame(CFrame* tempframe) {m_vAnimVec[tempframe->GetFrame()] = tempframe;}
	std::vector<CFrame*> GetFrameVec() {return m_vAnimVec;}
private:
	std::vector< CFrame* > m_vAnimVec;
	bool m_bLooping;
	const char* m_ccImagePath;
	UNIT_TYPE m_eUnitType;
	ANIM_TYPE m_eAnimType;
};

