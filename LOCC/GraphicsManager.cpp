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
	int returnID = -1;

	if (szGraphicsID != _T(""))
	{
		for (decltype(m_vImageIDs.size()) i = 0; i < m_vImageIDs.size(); ++i)
		{
			if (m_vImageIDs[i].first == szGraphicsID)
				return m_vImageIDs[i].second;
		}
	}

	assert(returnID != -1 && "TextureManager GetTexture returnID found to be -1");

	return returnID;
}

void CGraphicsManager::LoadImage( TSTRING szFilename, TSTRING szReferenceName, DWORD colorKey )
{
	int newID = CSGD_TextureManager::GetInstance()->LoadTexture(szFilename.c_str(), colorKey);

	ImageID newImageID;
	newImageID.first = szReferenceName;
	newImageID.second = newID;

	m_vImageIDs.push_back(newImageID);
}

void CGraphicsManager::RemoveImage(TSTRING szReferenceName, int ID)
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
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
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
	while (m_vImageIDs.size() != 0)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_vImageIDs.back().second);
		m_vImageIDs.pop_back();
	}
}

void CGraphicsManager::DrawWireframeRect(RECT r, int red, int green, int blue)
{
	CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top, r.left, r.top + r.bottom, red, green, blue);
	CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top, r.left + r.right, r.top, red, green, blue);
	CSGD_Direct3D::GetInstance()->DrawLine(r.left + r.right, r.top, r.left + r.right, r.top + r.bottom, red, green, blue);
	CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top + r.bottom, r.left + r.right, r.top + r.bottom, red, green, blue);
}