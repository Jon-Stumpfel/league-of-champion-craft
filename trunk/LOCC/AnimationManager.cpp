#include "StdAfx.h"
#include "AnimationManager.h"

CAnimationManager* CAnimationManager::s_Instance = nullptr;


CAnimationManager::CAnimationManager(void)
{
}


CAnimationManager::~CAnimationManager(void)
{
}

void CAnimationManager::Update( float fElapsedTime )
{

}

void CAnimationManager::Render( void )
{

}

CAnimationManager* CAnimationManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CAnimationManager();

	return s_Instance;
}

bool CAnimationManager::Load(const char* strName)
{
	TiXmlDocument doc;
	if(doc.LoadFile(strName) == false)
		return false;
	TiXmlElement* pRoot = doc.RootElement();
	if(pRoot == nullptr)
		return false;
	TiXmlElement* Animation = pRoot->FirstChildElement("Animation");
	while(Animation != nullptr)
	{
		CAnimation* tempanim = new CAnimation();
		const char* tempchar;
		tempchar = Animation->Attribute("Name");
		tempanim->SetLooping(Animation->Attribute("IsLooping"));
		tempanim->SetPath(Animation->Attribute("ImgName"));
		if(tempchar == "SwordsmanWalking")
		{
			return true;
		}
	}
	return true;
}

RECT CAnimationManager::GetFrame(UnitAnimation STheAnimStruct)
{
	switch (STheAnimStruct.unitType)
	{
	case UT_HERO:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_IDLE)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
				case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
	}
	RECT failrect; failrect.top = 0; failrect.bottom = 0; failrect.left = 0; failrect.right = 0;
	return failrect;
}