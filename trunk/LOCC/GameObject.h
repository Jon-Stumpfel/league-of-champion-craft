#pragma once

class CGameObject 
{
	Vec2D m_sWorldPos; // pixel position

public:

	virtual ~CGameObject(void);

	virtual void Update(float fElapsedTime);
	virtual void Render(void);

};