#pragma once

#include "Unit.h"
#include <list>

class CObjectManager
{

public:

	void AddObject( CUnit* pUnit );
	void RemoveObject( CUnit* pUnit );
	void RemoveAllObjects( void );
	
	CObjectManager* GetInstance( void );
	void DeleteInstance( void );

private:

	CObjectManager(void);
	~CObjectManager(void);
	CObjectManager(const CObjectManager&);
	CObjectManager& operator=(const CObjectManager&);

	static CObjectManager* s_Instance;

	std::list< CUnit* > m_pObjectList;

};

