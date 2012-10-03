#pragma once

#include "StdAfx.h"
#include "Unit.h"

class CAIManager
{

private:

	static CAIManager* GetInstance(void);
	static void DeleteInstance(void);	

	void RemoveObject(CUnit* obj);
	void RemoveAllObjects(void);
	void UpdateAI(float fElapsedTime);
	void AddObject(CUnit* obj);

private:

	CAIManager(void);
	~CAIManager(void);
	CAIManager(const CAIManager&);
	CAIManager& operator=(const CAIManager&);

	static CAIManager* s_Instance;

};

