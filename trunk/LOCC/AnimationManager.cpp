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
		CAnimation tempanim;
		std::string tempchar;
		tempchar = Animation->Attribute("Name");
		int temp = 0;
		Animation->Attribute("IsLooping", &temp);
		if(temp == 0)
			tempanim.SetLooping(false);
		else
			tempanim.SetLooping(true);
		tempanim.SetPath(Animation->Attribute("ImgName"));
		if(tempchar.find("Swordsman"))
		{
			m_vSwordsmanAnims.push_back(tempanim);
		}
		else if(tempchar.find("Champion"))
		{
			m_vChampionAnims.push_back(tempanim);
		}
		else if(tempchar.find("Archer"))
		{
			m_vArcherAnims.push_back(tempanim);
		}
		else if(tempchar.find("Castle"))
		{
			m_vCastleAnims.push_back(tempanim);
		}
	}
	return true;
}

RECT CAnimationManager::GetFrame(UnitAnimation STheAnimStruct)
{
	/*okay, a quick explanation of this cluster-fuckery....
	so, to render the animations, I set it up so the unit will call this function, sending
	in a struct called UnitStruct. This stores a few variables that are used to
	A.) tell this function what animation the unit wants,
	B.) keep the animation updated, and
	C.) keep track of the frame it wants.
	so, this function does this:
	switch (what unit wants the rect?)
	{
		case: THE UNIT WE WANT
		{
			switch (what animation does the unit want?)
			{
				case: THE ANIM WE WANT
				{
					in here, we flip through the unit-specific vector of animations,
					looking for the correct type.
					Once we find that, we find the current frame, as determined by the struct,
					and return the rect.
				}
			}
		}
	}
	*/
	switch (STheAnimStruct.unitType)
	{
	case UT_CASTLE:
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
	case UT_HERO:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
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
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
	case UT_ARCHER:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
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
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
	case UT_SWORDSMAN:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
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
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
		case UT_CAVALRY:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
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
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
		case UT_SKELETON:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
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
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							tempiter->GetFrameVec()[STheAnimStruct.nCurrentFrame]->GetRect();
						}
					}
				}
			}
		}
		case UT_ICEBLOCK:
		{
			switch (STheAnimStruct.animationType)
			{
			case AT_IDLE:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
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