#pragma once
#include "Unit.h"
#include "Animation.h"

class CAnimationManager
{

public:

	void Update( float fElapsedTime );
	bool Load(const char* strName);
	static CAnimationManager* GetInstance( void );
	RECT GetFrame(UnitAnimation STheAnimStruct);
private:

	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager(const CAnimationManager&);
	CAnimationManager& operator=(const CAnimationManager&);
	static CAnimationManager* s_Instance;
	std::vector<CAnimation> m_vSwordsmanAnims;
	std::vector<CAnimation> m_vArcherAnims;
	std::vector<CAnimation> m_vCalvaryAnims;
	std::vector<CAnimation> m_vSkeletonAnims;
	std::vector<CAnimation> m_vChampionAnims;
	std::vector<CAnimation> m_vCastleAnims;
	std::vector<CAnimation> m_vIceBlockAnims;
};
