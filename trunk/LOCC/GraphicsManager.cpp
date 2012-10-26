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


void CGraphicsManager::DrawArrow(int x, int y, int red, int green, int blue)
{
	CSGD_Direct3D::GetInstance()->DrawLine(x - 10, y, x + 10, y, red, green, blue);
	CSGD_Direct3D::GetInstance()->DrawLine(x, y - 3, x + 10, y, red, green, blue);
	CSGD_Direct3D::GetInstance()->DrawLine(x, y + 3, x + 10, y, red, green, blue);

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

	CSGD_TextureManager::GetInstance()->ShutdownTextureManager();
	CSGD_Direct3D::GetInstance()->ShutdownDirect3D();
}

	void CGraphicsManager::DrawWireframeDiag(RECT r, int red, int green, int blue)
	{
		int nWidth = r.right;
		int nHeight = r.bottom;
		CSGD_Direct3D::GetInstance()->DrawLine((int)(r.left + nWidth * 0.5f), (int)r.top, (int)(r.left + nWidth), (int)(r.top +nHeight * 0.5f), red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine((int)(r.left + nWidth), (int)(r.top + nHeight * 0.5f), (int)(r.left + nWidth * 0.5f), (int)( r.top +nHeight), red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine((int)(r.left + nWidth * 0.5f), (int)(r.top + nHeight), (int)(r.left), (int)(r.top +nHeight * 0.5f), red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine((int)(r.left), (int)(r.top + nHeight * 0.5f), (int)(r.left + nWidth * 0.5f), r.top, red, green, blue);
	}

void CGraphicsManager::DrawWireframeRect(RECT r, int red, int green, int blue, bool bDirect)
{
	if (bDirect)
	{
		CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top, r.right, r.top);
		CSGD_Direct3D::GetInstance()->DrawLine(r.right, r.top, r.right, r.bottom);
		CSGD_Direct3D::GetInstance()->DrawLine(r.right, r.bottom, r.left, r.bottom);
		CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.bottom, r.left, r.top);
	
	}
	else
	{
		CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top, r.left, r.top + r.bottom, red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top, r.left + r.right, r.top, red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine(r.left + r.right, r.top, r.left + r.right, r.top + r.bottom, red, green, blue);
		CSGD_Direct3D::GetInstance()->DrawLine(r.left, r.top + r.bottom, r.left + r.right, r.top + r.bottom, red, green, blue);
	}
}