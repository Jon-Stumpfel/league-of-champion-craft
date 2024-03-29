#include "StdAfx.h"
#include "AnimationManager.h"

CAnimationManager* CAnimationManager::s_Instance = nullptr;


CAnimationManager::CAnimationManager(void)
{
	for(unsigned int i = 0; i < (int)AT_DEATH+1; i++)
	{
		m_vSwordsmanBools.push_back(false);
		m_vArcherBools.push_back(false);
		m_vCalvaryBools.push_back(false);
		m_vSkeletonBools.push_back(false);
		m_vChampionBools.push_back(false);
		m_vCastleBools.push_back(false);
		m_vIceBlockBools.push_back(false);
	}
}

CAnimationManager::~CAnimationManager(void)
{
}

void CAnimationManager::Update( float fElapsedTime )
{
	if(m_vSwordsmanAnims.size() > 0)
	{
		for(unsigned int i = 0; i < m_vSwordsmanAnims.size(); i++)
		{
			int tempb = (int)m_vSwordsmanAnims[i].GetAnimType();
			if(m_vSwordsmanBools[tempb] == true)
			{
				m_vSwordsmanAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].GetTimePlayed() < m_vSwordsmanAnims[i].GetElapsedTime()
					&& (unsigned) m_vSwordsmanAnims[i].GetCurrFrame() < m_vSwordsmanAnims[i].GetFrameVec().size()-1)
				{
					m_vSwordsmanAnims[i].SetCurrFrame(m_vSwordsmanAnims[i].GetCurrFrame()+1);
					m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].SetFrameNumber(m_vSwordsmanAnims[i].GetCurrFrame());
					m_vSwordsmanAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].GetTimePlayed() < m_vSwordsmanAnims[i].GetElapsedTime()
					&& (unsigned) m_vSwordsmanAnims[i].GetCurrFrame() >= m_vSwordsmanAnims[i].GetFrameVec().size()-1)
				{
					if(m_vSwordsmanAnims[i].GetLooping() == true)
					{
						m_vSwordsmanAnims[i].SetCurrFrame(0);
						m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].SetFrameNumber(m_vSwordsmanAnims[i].GetCurrFrame());
					}
					else if(m_vSwordsmanAnims[i].GetLooping() == false)
					{
						m_vSwordsmanAnims[i].SetCurrFrame(m_vSwordsmanAnims[i].GetFrameVec().size()-1);
						m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].SetFrameNumber(m_vSwordsmanAnims[i].GetCurrFrame());
					}
					m_vSwordsmanAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vArcherAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vArcherAnims.size(); i++)
		{
			if(m_vArcherBools[(int)m_vArcherAnims[i].GetAnimType()] == true)
			{
				m_vArcherAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].GetTimePlayed() < m_vArcherAnims[i].GetElapsedTime()
					&& (unsigned) m_vArcherAnims[i].GetCurrFrame() < m_vArcherAnims[i].GetFrameVec().size()-1)
				{
					m_vArcherAnims[i].SetCurrFrame(m_vArcherAnims[i].GetCurrFrame()+1);
					m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].SetFrameNumber(m_vArcherAnims[i].GetCurrFrame());
					m_vArcherAnims[i].SetElapsedTime(0.0f);
				}
				if(m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].GetTimePlayed() < m_vArcherAnims[i].GetElapsedTime()
					&& (unsigned) m_vArcherAnims[i].GetCurrFrame() >= m_vArcherAnims[i].GetFrameVec().size()-1)
				{
					if(m_vArcherAnims[i].GetLooping() == true)
					{
						m_vArcherAnims[i].SetCurrFrame(0);
						m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].SetFrameNumber(m_vArcherAnims[i].GetCurrFrame());
					}
					else if(m_vArcherAnims[i].GetLooping() == false)
					{
						m_vArcherAnims[i].SetCurrFrame(m_vArcherAnims[i].GetFrameVec().size()-1);
						m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].SetFrameNumber(m_vArcherAnims[i].GetCurrFrame());
					}
					m_vArcherAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vCalvaryAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vCalvaryAnims.size(); i++)
		{
			if(m_vCalvaryBools[(int)m_vCalvaryAnims[i].GetAnimType()] == true)
			{
				m_vCalvaryAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].GetTimePlayed() < m_vCalvaryAnims[i].GetElapsedTime()
					&& (unsigned) m_vCalvaryAnims[i].GetCurrFrame() < m_vCalvaryAnims[i].GetFrameVec().size()-1)
				{
					m_vCalvaryAnims[i].SetCurrFrame(m_vCalvaryAnims[i].GetCurrFrame()+1);
					m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].SetFrameNumber(m_vCalvaryAnims[i].GetCurrFrame());
					m_vCalvaryAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].GetTimePlayed() < m_vCalvaryAnims[i].GetElapsedTime()
					&& (unsigned) m_vCalvaryAnims[i].GetCurrFrame() >= m_vCalvaryAnims[i].GetFrameVec().size()-1)
				{
					if(m_vCalvaryAnims[i].GetLooping() == true)
					{
						m_vCalvaryAnims[i].SetCurrFrame(0);
						m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].SetFrameNumber(m_vCalvaryAnims[i].GetCurrFrame());
					}
					else if(m_vCalvaryAnims[i].GetLooping() == false)
					{
						m_vCalvaryAnims[i].SetCurrFrame(m_vCalvaryAnims[i].GetFrameVec().size()-1);
						m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].SetFrameNumber(m_vCalvaryAnims[i].GetCurrFrame());
					}
					m_vCalvaryAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vSkeletonAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vSkeletonAnims.size(); i++)
		{
			if(m_vSkeletonBools[(int)m_vSkeletonAnims[i].GetAnimType()] == true)
			{
				m_vSkeletonAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].GetTimePlayed() < m_vSkeletonAnims[i].GetElapsedTime()
					&& (unsigned) m_vSkeletonAnims[i].GetCurrFrame() < m_vSkeletonAnims[i].GetFrameVec().size()-1)
				{
					m_vSkeletonAnims[i].SetCurrFrame(m_vSkeletonAnims[i].GetCurrFrame()+1);
					m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].SetFrameNumber(m_vSkeletonAnims[i].GetCurrFrame());
					m_vSkeletonAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].GetTimePlayed() < m_vSkeletonAnims[i].GetElapsedTime()
					&& (unsigned) m_vSkeletonAnims[i].GetCurrFrame() >= m_vSkeletonAnims[i].GetFrameVec().size()-1)
				{
					if(m_vSkeletonAnims[i].GetLooping() == true)
					{
						m_vSkeletonAnims[i].SetCurrFrame(0);
						m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].SetFrameNumber(m_vSkeletonAnims[i].GetCurrFrame());
					}
					else if(m_vSkeletonAnims[i].GetLooping() == false)
					{
						m_vSkeletonAnims[i].SetCurrFrame(m_vSkeletonAnims[i].GetFrameVec().size()-1);
						m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].SetFrameNumber(m_vSkeletonAnims[i].GetCurrFrame());
					}
					m_vSkeletonAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vChampionAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vChampionAnims.size(); i++)
		{
			if(m_vChampionBools[(int)m_vChampionAnims[i].GetAnimType()] == true)
			{
				m_vChampionAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].GetTimePlayed() < m_vChampionAnims[i].GetElapsedTime()
					&& (unsigned) m_vChampionAnims[i].GetCurrFrame() < m_vChampionAnims[i].GetFrameVec().size()-1)
				{
					m_vChampionAnims[i].SetCurrFrame(m_vChampionAnims[i].GetCurrFrame()+1);
					m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].SetFrameNumber(m_vChampionAnims[i].GetCurrFrame());
					m_vChampionAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].GetTimePlayed() < m_vChampionAnims[i].GetElapsedTime()
					&& (unsigned) m_vChampionAnims[i].GetCurrFrame() >= m_vChampionAnims[i].GetFrameVec().size()-1)
				{
					if(m_vChampionAnims[i].GetLooping() == true)
					{
						m_vChampionAnims[i].SetCurrFrame(0);
						m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].SetFrameNumber(m_vChampionAnims[i].GetCurrFrame());
					}
					else if(m_vChampionAnims[i].GetLooping() == false)
					{
						m_vChampionAnims[i].SetCurrFrame(m_vChampionAnims[i].GetFrameVec().size()-1);
						m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].SetFrameNumber(m_vChampionAnims[i].GetCurrFrame());
					}
					m_vChampionAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vCastleAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vCastleAnims.size(); i++)
		{
			if(m_vCastleBools[(int)m_vCastleAnims[i].GetAnimType()] == true)
			{
				m_vCastleAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].GetTimePlayed() < m_vCastleAnims[i].GetElapsedTime()
					&& (unsigned) m_vCastleAnims[i].GetCurrFrame() < m_vCastleAnims[i].GetFrameVec().size()-1)
				{
					m_vCastleAnims[i].SetCurrFrame(m_vCastleAnims[i].GetCurrFrame()+1);
					m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(m_vCastleAnims[i].GetCurrFrame());
					m_vCastleAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].GetTimePlayed() < m_vCastleAnims[i].GetElapsedTime()
					&& (unsigned) m_vCastleAnims[i].GetCurrFrame() >= m_vCastleAnims[i].GetFrameVec().size()-1)
				{
					if(m_vCastleAnims[i].GetLooping() == true && m_vCastleAnims[i].GetFrameVec().size() > 1)
					{
						m_vCastleAnims[i].SetCurrFrame(5);
						m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(5);
					}
					if(m_vCastleAnims[i].GetLooping() == true && m_vCastleAnims[i].GetFrameVec().size() > 1)
					{
						m_vCastleAnims[i].SetCurrFrame(13);
						m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(13);
					}
					if(m_vCastleAnims[i].GetLooping() == true)
					{
						m_vCastleAnims[i].SetCurrFrame(0);
						m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(m_vCastleAnims[i].GetCurrFrame());
					}
					else if(m_vCastleAnims[i].GetLooping() == false)
					{
						m_vCastleAnims[i].SetCurrFrame(m_vCastleAnims[i].GetFrameVec().size()-1);
						m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(m_vCastleAnims[i].GetCurrFrame());
					}
					m_vCastleAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
	if(m_vIceBlockAnims.size() >0)
	{
		for(unsigned int i = 0; i < m_vIceBlockAnims.size(); i++)
		{
			if(m_vIceBlockBools[(int)m_vIceBlockAnims[i].GetAnimType()] == true)
			{
				m_vIceBlockAnims[i].AddElapsedTime(fElapsedTime);
				if(m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].GetTimePlayed() < m_vIceBlockAnims[i].GetElapsedTime()
					&& (unsigned) m_vIceBlockAnims[i].GetCurrFrame() < m_vIceBlockAnims[i].GetFrameVec().size()-1)
				{
					m_vIceBlockAnims[i].SetCurrFrame(m_vIceBlockAnims[i].GetCurrFrame()+1);
					m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].SetFrameNumber(m_vIceBlockAnims[i].GetCurrFrame());
					m_vIceBlockAnims[i].SetElapsedTime(0.0f);
				}
				else if(m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].GetTimePlayed() < m_vIceBlockAnims[i].GetElapsedTime()
					&& (unsigned) m_vIceBlockAnims[i].GetCurrFrame() >= m_vIceBlockAnims[i].GetFrameVec().size()-1)
				{
					if(m_vIceBlockAnims[i].GetLooping() == true)
					{
						m_vIceBlockAnims[i].SetCurrFrame(0);
						m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].SetFrameNumber(m_vIceBlockAnims[i].GetCurrFrame());
					}
					else if(m_vIceBlockAnims[i].GetLooping() == false)
					{
						m_vIceBlockAnims[i].SetCurrFrame(m_vIceBlockAnims[i].GetFrameVec().size()-1);
						m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].SetFrameNumber(m_vIceBlockAnims[i].GetCurrFrame());
					}
					m_vIceBlockAnims[i].SetElapsedTime(0.0f);
				}
			}
		}
	}
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
		int tempunit;
		int tempanimtype;
		Animation->Attribute("UnitType", &tempunit);
		UNIT_TYPE temp1 = static_cast<UNIT_TYPE>(tempunit);
		tempanim.SetUnitType(temp1);
		Animation->Attribute("AnimType", &tempanimtype);
		ANIM_TYPE temp2 = static_cast<ANIM_TYPE>(tempanimtype);
		tempanim.SetAnimType(temp2);
		int temp = 0;
		Animation->Attribute("IsLooping", &temp);
		if(temp == 0)
			tempanim.SetLooping(false);
		else
			tempanim.SetLooping(true);
		tempanim.SetPath(Animation->Attribute("ImgName"));
		int tempframe;
		Animation->Attribute("CurrFrame", &tempframe);
		tempanim.SetCurrFrame(tempframe);
		TiXmlElement* Frame = Animation->FirstChildElement("Frame");
		while(Frame != nullptr)
		{
			CFrame tempframe;
			//setting which order the frames render
			int tempframenum;
			Frame->Attribute("FrameNumber", &tempframenum);
			tempframe.SetFrameNumber(tempframenum);
			//setting the time each frame runs
			double temptime;
			Frame->Attribute("TimeForFrameToRun", &temptime);
			tempframe.SetTimePlayed((float)temptime/100);
			//setting the image's rect on the sprite sheet
			RECT temprect; int tempright; int templeft; int temptop; int tempbottom;
			Frame->Attribute("top", &temptop);
			Frame->Attribute("right", &tempright);
			Frame->Attribute("bottom", &tempbottom);
			Frame->Attribute("left", &templeft);
			temprect.top = temptop; temprect.bottom = tempbottom;
			temprect.right = tempright; temprect.left = templeft;
			tempframe.SetImageRect(temprect);
			Vec2D tempvec; int vecx; int vecy;
			Frame->Attribute("AnchorX", &vecx);
			Frame->Attribute("AnchorY", &vecy);
			tempvec.nPosX = vecx;
			tempvec.nPosY = vecy;
			tempframe.SetAnchorPoint(tempvec);
			tempanim.SetFrame(tempframe);
			Frame = Frame->NextSiblingElement("Frame");
		}
		//The below code checks the name of the animation for the type of
		//unit, so it can save to the right vector
		if(tempanim.GetUnitType() == UT_SWORDSMAN)
		{
			m_vSwordsmanAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_HERO)
		{
			m_vChampionAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_ARCHER)
		{
			m_vArcherAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_CASTLE)
		{
			m_vCastleAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_CAVALRY)
		{
			m_vCalvaryAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_SKELETON)
		{
			m_vSkeletonAnims.push_back(tempanim);
		}
		else if(tempanim.GetUnitType() == UT_ICEBLOCK)
		{
			m_vIceBlockAnims.push_back(tempanim);
		}
		Animation = Animation->NextSiblingElement("Animation");
	}
	return true;
}

CFrame* CAnimationManager::GetFrame(UnitAnimation STheAnimStruct)
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCastleAnims.begin();tempiter!=m_vCastleAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vChampionAnims.begin();tempiter!=m_vChampionAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vArcherAnims.begin();tempiter!=m_vArcherAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSwordsmanAnims.begin();tempiter!=m_vSwordsmanAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vCalvaryAnims.begin();tempiter!=m_vCalvaryAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vSkeletonAnims.begin();tempiter!=m_vSkeletonAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
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
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_WALK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_WALK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ATTACK_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ATTACK_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_N:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_N)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_S:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_S)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_E:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_E)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_ABILITY_W:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_ABILITY_W)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			case AT_DEATH:
				{
					std::vector<CAnimation>::iterator tempiter;
					for(tempiter=m_vIceBlockAnims.begin();tempiter!=m_vIceBlockAnims.end();tempiter++)
					{
						if(tempiter->GetAnimType() == AT_DEATH)
						{
							return &tempiter->GetFrameVec()[tempiter->GetCurrFrame()];
						}
					}
					break;
				}
			}
			break;
		}
	}
	CFrame* failframe = new CFrame();
	RECT failrect; failrect.bottom = -1; failrect.left = -1;
	failrect.right = -1; failrect.top = -1;
	failframe->SetAnchorPoint(Vec2D(-1,-1));
	failframe->SetFrameNumber(-1);
	failframe->SetImageRect(failrect);
	failframe->SetTimePlayed(-1.0f);
	return failframe;
}

void CAnimationManager::Shutdown()
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

CAnimation* CAnimationManager::GetAnimation(UNIT_TYPE ut, ANIM_TYPE at)
{
	switch (ut)
	{
	case UT_CASTLE:
		{
			for(unsigned int i = 0; i < m_vCastleAnims.size(); i++)
			{
				if(m_vCastleAnims[i].GetAnimType() == at)
				{
					return &m_vCastleAnims[i];
				}
			}
			break;
		}
	case UT_HERO:
		{
			for(unsigned int i = 0; i < m_vChampionAnims.size(); i++)
			{
				if(m_vChampionAnims[i].GetAnimType() == at)
				{
					return &m_vChampionAnims[i];
				}
			}
			break;
		}
	case UT_ARCHER:
		{
			for(unsigned int i = 0; i < m_vArcherAnims.size(); i++)
			{
				if(m_vArcherAnims[i].GetAnimType() == at)
				{
					return &m_vArcherAnims[i];
				}
			}
			break;
		}
	case UT_SWORDSMAN:
		{
			for(unsigned int i = 0; i < m_vSwordsmanAnims.size(); i++)
			{
				if(m_vSwordsmanAnims[i].GetAnimType() == at)
				{
					return &m_vSwordsmanAnims[i];
				}
			}
			break;
		}
	case UT_CAVALRY:
		{
			for(unsigned int i = 0; i < m_vCalvaryAnims.size(); i++)
			{
				if(m_vCalvaryAnims[i].GetAnimType() == at)
				{
					return &m_vCalvaryAnims[i];
				}
			}
			break;
		}
	case UT_SKELETON:
		{
			for(unsigned int i = 0; i < m_vSkeletonAnims.size(); i++)
			{
				if(m_vSkeletonAnims[i].GetAnimType() == at)
				{
					return &m_vSkeletonAnims[i];
				}
			}
			break;
		}
	case UT_ICEBLOCK:
		{
			for(unsigned int i = 0; i < m_vIceBlockAnims.size(); i++)
			{
				if(m_vIceBlockAnims[i].GetAnimType() == at)
				{
					return &m_vIceBlockAnims[i];
				}
			}
			break;
		}
	}
	return &m_vIceBlockAnims[0];
}

void CAnimationManager::SetCoinFrame(int temp)
{
	if(m_vCastleAnims[4].GetAnimType() != NULL)
	{
		m_vCastleAnims[4].SetCurrFrame(temp);
	}
}

void CAnimationManager::SetAnimBool(UNIT_TYPE ut, int at, bool temp)
{
	switch (ut)
	{
	case UT_CASTLE:
		{
			m_vCastleBools[at]= temp;
			for(unsigned int i = 0; i < m_vCastleAnims.size();i++)
			{
				if((int)m_vCastleAnims[i].GetAnimType() == at && temp == false)
				{
					m_vCastleAnims[i].SetCurrFrame(0);
					m_vCastleAnims[i].SetElapsedTime(0.0f);
					m_vCastleAnims[i].GetFrameVec()[m_vCastleAnims[i].GetCurrFrame()].SetFrameNumber(m_vCastleAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_HERO:
		{
			m_vChampionBools[at]= temp;
			for(unsigned int i = 0; i < m_vChampionAnims.size();i++)
			{
				if((int)m_vChampionAnims[i].GetAnimType() == at && temp == false)
				{
					m_vChampionAnims[i].SetCurrFrame(0);
					m_vChampionAnims[i].SetElapsedTime(0.0f);
					m_vChampionAnims[i].GetFrameVec()[m_vChampionAnims[i].GetCurrFrame()].SetFrameNumber(m_vChampionAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_ARCHER:
		{
			m_vArcherBools[at]= temp;
			for(unsigned int i = 0; i < m_vArcherAnims.size();i++)
			{
				if((int)m_vArcherAnims[i].GetAnimType() == at && temp == false)
				{
					m_vArcherAnims[i].SetCurrFrame(0);
					m_vArcherAnims[i].SetElapsedTime(0.0f);
					m_vArcherAnims[i].GetFrameVec()[m_vArcherAnims[i].GetCurrFrame()].SetFrameNumber(m_vArcherAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_SWORDSMAN:
		{
			m_vSwordsmanBools[at]= temp;
			for(unsigned int i = 0; i < m_vSwordsmanAnims.size();i++)
			{
				if((int)m_vSwordsmanAnims[i].GetAnimType() == at && temp == false)
				{
					m_vSwordsmanAnims[i].SetCurrFrame(0);
					m_vSwordsmanAnims[i].SetElapsedTime(0.0f);
					m_vSwordsmanAnims[i].GetFrameVec()[m_vSwordsmanAnims[i].GetCurrFrame()].SetFrameNumber(m_vSwordsmanAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_CAVALRY:
		{
			m_vCalvaryBools[at]= temp;
			for(unsigned int i = 0; i < m_vCalvaryAnims.size();i++)
			{
				if((int)m_vCalvaryAnims[i].GetAnimType() == at && temp == false)
				{
					m_vCalvaryAnims[i].SetCurrFrame(0);
					m_vCalvaryAnims[i].SetElapsedTime(0.0f);
					m_vCalvaryAnims[i].GetFrameVec()[m_vCalvaryAnims[i].GetCurrFrame()].SetFrameNumber(m_vCalvaryAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_SKELETON:
		{
			m_vSkeletonBools[at]= temp;
			for(unsigned int i = 0; i < m_vSkeletonAnims.size();i++)
			{
				if((int)m_vSkeletonAnims[i].GetAnimType() == at && temp == false)
				{
					m_vSkeletonAnims[i].SetCurrFrame(0);
					m_vSkeletonAnims[i].SetElapsedTime(0.0f);
					m_vSkeletonAnims[i].GetFrameVec()[m_vSkeletonAnims[i].GetCurrFrame()].SetFrameNumber(m_vSkeletonAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	case UT_ICEBLOCK:
		{
			m_vIceBlockBools[at-1]= temp;
			for(unsigned int i = 0; i < m_vIceBlockAnims.size();i++)
			{
				if((int)m_vIceBlockAnims[i].GetAnimType() == at && temp == false)
				{
					m_vIceBlockAnims[i].SetCurrFrame(0);
					m_vIceBlockAnims[i].SetElapsedTime(0.0f);
					m_vIceBlockAnims[i].GetFrameVec()[m_vIceBlockAnims[i].GetCurrFrame()].SetFrameNumber(m_vIceBlockAnims[i].GetCurrFrame());
				}
			}
			break;
		}
	}
}