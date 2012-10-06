#include "StdAfx.h"
#include "GraphicsManager.h"
//#include "SGD Wrappers\CSGD_TextureManager.h"
//#include "SGD Wrappers\CSGD_Direct3D.h"
CGraphicsManager* CGraphicsManager::s_Instance = nullptr;


CGraphicsManager::CGraphicsManager(void)
{
}


CGraphicsManager::~CGraphicsManager(void)
{
}

int CGraphicsManager::GetID( TSTRING szGraphicsID )
{
	return -1;
}

void CGraphicsManager::LoadImage( TSTRING szFilename, TSTRING szReferenceName, DWORD colorKey )
{
	int newID = CSGD_TextureManager::GetInstance()->LoadTexture(szFilename.c_str(), colorKey);

	ImageID newImageID;
	newImageID.first = szFilename;
	newImageID.second = newID;

	m_vImageIDs.push_back(newImageID);
}

void CGraphicsManager::RemoveImage(TSTRING szReferenceName, int ID = -1)
{

}
CGraphicsManager* CGraphicsManager::GetInstance( void )
{
	if (s_Instance == nullptr)
		s_Instance = new CGraphicsManager();

	return s_Instance;
}

void CGraphicsManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
		delete s_Instance;
	s_Instance = nullptr;
}

void CGraphicsManager::Initialize( HWND hWnd, HINSTANCE hInstance,
	int nScreenWidth, int nScreenHeight,
	bool bIsWindowed )
{
	CSGD_Direct3D::GetInstance()->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed);	
	CSGD_TextureManager::GetInstance()->InitTextureManager(CSGD_Direct3D::GetInstance()->GetDirect3DDevice(), 
		CSGD_Direct3D::GetInstance()->GetSprite());

}

void CGraphicsManager::Shutdown( void )
{
}