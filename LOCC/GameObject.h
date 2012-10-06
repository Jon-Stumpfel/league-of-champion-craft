#pragma once

class CGameObject 
{
	Vec2D m_sWorldPos; // pixel position
	unsigned int m_unRefCount;
public:
	CGameObject(void);
	virtual ~CGameObject(void);

	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	virtual void AddRef(void);
	virtual void Release(void);
};