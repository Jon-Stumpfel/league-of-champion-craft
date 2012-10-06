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
		CAnimation* tempanim;
		const char* tempchar;
		tempchar = Animation->Attribute("Name");
		if(tempchar == "FootmanWalking")
		{
			
		}
	}
}