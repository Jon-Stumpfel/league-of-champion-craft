#pragma once

class CGraphicsManager
{

public:

	int GetID( std::string szGraphicsID );
	void LoadImage( std::string szFilename, std::string szReferenceName );

	static CGraphicsManager* GetInstance( void );
	static void DeleteInstance(void);
	void Initialize( HWND hWnd, HINSTANCE hInstance,
				int nScreenWidth, int nScreenHeight,
				bool bIsWindowed );
	void Shutdown( void );

private:

	
	CGraphicsManager(void);
	~CGraphicsManager(void);
	CGraphicsManager(const CGraphicsManager&);
	CGraphicsManager& operator=(const CGraphicsManager&);

	static CGraphicsManager* s_Instance;

};

