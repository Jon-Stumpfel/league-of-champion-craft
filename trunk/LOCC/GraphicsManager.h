#pragma once

class CGraphicsManager
{

public:

	CGraphicsManager(void);
	~CGraphicsManager(void);

	int GetID( std::string szGraphicsID );
	void LoadImage( std::string szFilename );

	CGraphicsManager* GetInstance( void );

	void Initialize( void );
	void Shutdown( void );

};

