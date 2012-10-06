#pragma once

class CGraphicsManager
{

public:

	int GetID( TSTRING szGraphicsID );
	void LoadImage( TSTRING szFilename, TSTRING szReferenceName, DWORD colorKey );
	void RemoveImage(TSTRING szReferenceName, int ID = -1);
	static CGraphicsManager* GetInstance( void );
	static void DeleteInstance(void);
	void Initialize( HWND hWnd, HINSTANCE hInstance,
				int nScreenWidth, int nScreenHeight,
				bool bIsWindowed );
	void Shutdown( void );

	void CGraphicsManager::DrawWireframeRect(RECT r, int red, int green, int blue);

private:

	
	CGraphicsManager(void);
	~CGraphicsManager(void);
	CGraphicsManager(const CGraphicsManager&);
	CGraphicsManager& operator=(const CGraphicsManager&);


	typedef std::pair<TSTRING, int> ImageID;
	std::vector<ImageID> m_vImageIDs;


	static CGraphicsManager* s_Instance;

};

