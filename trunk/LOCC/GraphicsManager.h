#pragma once

class CGraphicsManager
{

public:

	int GetID( std::string szGraphicsID );
	void LoadImage( std::string szFilename );

	CGraphicsManager* GetInstance( void );

	void Initialize( void );
	void Shutdown( void );

private:

	
	CGraphicsManager(void);
	~CGraphicsManager(void);
	CGraphicsManager(const CGraphicsManager&);
	CGraphicsManager& operator=(const CGraphicsManager&);

	static CGraphicsManager* s_Instance;

};

