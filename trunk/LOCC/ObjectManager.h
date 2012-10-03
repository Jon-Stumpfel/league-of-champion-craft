#pragma once

#include "Unit.h"
#include <list>

class CObjectManager
{

public:

	CObjectManager(void);
	~CObjectManager(void);

	void AddObject( CUnit* pUnit );
	void RemoveObject( CUnit* pUnit );
	void RemoveAllObjects( void );
	
	CObjectManager* GetInstance( void );
	void DeleteInstance( void );

private:

	std::list< CUnit* > m_pObjectList;

};

