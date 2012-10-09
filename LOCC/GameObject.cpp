#include "StdAfx.h"
#include "GameObject.h"

CGameObject::CGameObject(void)
{
	m_sWorldPos.nPosY = 6;
	m_sWorldPos.nPosX = 12;
	m_unRefCount = 0;
}

CGameObject::~CGameObject(void)
{
}

void CGameObject::Update(float fElapsedTime)
{
}
void CGameObject::Render(void)
{
}



void CGameObject::AddRef(void)
{
	// increase our reference count
	++m_unRefCount;
}
void CGameObject::Release(void)
{
	// Decrease our reference count
	--m_unRefCount;

	//Self-destruct?
	if (m_unRefCount == 0)
		delete this;
}