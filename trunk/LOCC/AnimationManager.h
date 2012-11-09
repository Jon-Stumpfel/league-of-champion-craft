#pragma once
#include "Unit.h"
#include "Animation.h"

class CAnimationManager
{

public:

	void Update( float fElapsedTime );
	bool Load(const char* strName);
	static CAnimationManager* GetInstance( void );
	CFrame* GetFrame(UnitAnimation STheAnimStruct);
	void Shutdown();
	CAnimation* GetAnimation(UNIT_TYPE ut, ANIM_TYPE at);
	void SetCoinFrame(int temp);
	void SetAnimBool(UNIT_TYPE ut, int at, bool temp);
private:
	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager(const CAnimationManager&);
	CAnimationManager& operator=(const CAnimationManager&);
	static CAnimationManager* s_Instance;
	std::vector<CAnimation> m_vSwordsmanAnims;
	std::vector<bool> m_vSwordsmanBools;
	std::vector<CAnimation> m_vArcherAnims;
	std::vector<bool> m_vArcherBools;
	std::vector<CAnimation> m_vCalvaryAnims;
	std::vector<bool> m_vCalvaryBools;
	std::vector<CAnimation> m_vSkeletonAnims;
	std::vector<bool> m_vSkeletonBools;
	std::vector<CAnimation> m_vChampionAnims;
	std::vector<bool> m_vChampionBools;
	std::vector<CAnimation> m_vCastleAnims;
	std::vector<bool> m_vCastleBools;
	std::vector<CAnimation> m_vIceBlockAnims;
	std::vector<bool> m_vIceBlockBools;
};

