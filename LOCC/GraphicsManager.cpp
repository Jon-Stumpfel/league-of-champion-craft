#include "StdAfx.h"
#include "GraphicsManager.h"

CGraphicsManager* CGraphicsManager::s_Instance = nullptr;


CGraphicsManager::CGraphicsManager(void)
{
}


CGraphicsManager::~CGraphicsManager(void)
{
}

int CGraphicsManager::GetID( std::string szGraphicsID )
{
	return -1;
}

void CGraphicsManager::LoadImage( std::string szFilename )
{
	
}

CGraphicsManager* CGraphicsManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CGraphicsManager();

	return s_Instance;
}

void CGraphicsManager::Initialize( void )
{

}

void CGraphicsManager::Shutdown( void )
{

}