#pragma once

#include "Unit.h"
#include <list>

class CObjectManager
{

public:

	void AddObject( CGameObject* pObject );
	void RemoveObject( CGameObject* pObject );
	void RemoveAllObjects( void );
	void UpdateAllObjects(float fElapsedTime);
	void RenderAllObjects(void);

	static CObjectManager* GetInstance( void );
	static void DeleteInstance( void );

	CGameObject* CreateObject(UNIT_TYPE type, int nPlayerID);
private:

	CObjectManager(void);
	~CObjectManager(void);
	CObjectManager(const CObjectManager&);
	CObjectManager& operator=(const CObjectManager&);

	static CObjectManager* s_Instance;

	typedef std::list<CGameObject*>		ObjectList;
	typedef	ObjectList::iterator	OListIterator;

	ObjectList m_pObjectList;

};

