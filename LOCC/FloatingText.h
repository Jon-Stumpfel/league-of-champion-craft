#pragma once
#include "StdAfx.h"

class CFloatingText
{
public:
	static CFloatingText* GetInstance(void);
	static void DeleteInstance(void);	
	void Initialize(void);
	void Shutdown(void);
	void Update(float fElapsedTime);
	void Render(void);

	void AddText(std::string str, Vec2Df position, Vec2Df velocity, float fLife, float fScale, DWORD color = D3DCOLOR_XRGB(255, 255, 255));
	void AddScreenText(std::string str, Vec2Df position, Vec2Df velocity, float fLife, float fScale, DWORD color = D3DCOLOR_XRGB(255, 255 ,255));
	static int AddText(lua_State *L);
private:

	struct FloatText
	{
		Vec2Df position;
		Vec2Df velocity;
		std::string str;
		D3DXCOLOR color;
		float fLife;
		float fMaxlife;
		float fScale;
		int nAlpha;
	};

	CFloatingText(void);
	~CFloatingText(void);
	CFloatingText(const CFloatingText&);
	CFloatingText& operator=(const CFloatingText&);
	static CFloatingText* s_Instance;

	std::vector<FloatText> m_vText;
	std::vector<FloatText> m_vScreenText;

};

