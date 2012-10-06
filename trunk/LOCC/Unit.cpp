#include "StdAfx.h"
#include "Unit.h"
#include "GraphicsManager.h"

CUnit::CUnit(UNIT_TYPE type) : m_eType(type)
{
}


CUnit::~CUnit(void)
{
}


void CUnit::Update(float fElapsedTime)
{
	// move me along the route!
	if (m_vWaypoints.size() != 0)
	{
		
	}
}
void CUnit::Render(void)
{
	//CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->LoadImage(_T("
}