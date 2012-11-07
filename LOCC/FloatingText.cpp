#include "StdAfx.h"
#include "FloatingText.h"
#include "BitmapFont.h"
#include "GameplayState.h"
CFloatingText* CFloatingText::s_Instance = nullptr;

CFloatingText::CFloatingText(void)
{
}


CFloatingText::~CFloatingText(void)
{
}

CFloatingText* CFloatingText::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CFloatingText();
	return s_Instance;
}
void CFloatingText::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->Shutdown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CFloatingText::Initialize(void)
{

}
void CFloatingText::Shutdown(void)
{

}

void CFloatingText::AddText(std::string str, Vec2Df position, Vec2Df velocity, float fLife, float fScale, DWORD color)
{
	FloatText txt;
	txt.str = str;
	txt.position = position;
	txt.velocity = velocity;
	txt.fLife = fLife;
	txt.fMaxlife = fLife;
	txt.color = color;
	txt.fScale = fScale;
	txt.color.a = 255;
	m_vText.push_back(txt);
}

void CFloatingText::AddScreenText(std::string str, Vec2Df position, Vec2Df velocity, float fLife, float fScale, DWORD color)
{
	FloatText txt;
	txt.str = str;
	txt.position = position;
	txt.velocity = velocity;
	txt.fLife = fLife;
	txt.fMaxlife = fLife;
	txt.color = color;
	txt.fScale = fScale;
	txt.color.a = 255;
	m_vScreenText.push_back(txt);
}

void CFloatingText::Update(float fElapsedTime)
{
	for (unsigned int i = 0; i < m_vText.size(); ++i)
	{
		m_vText[i].fLife -= fElapsedTime;
		m_vText[i].velocity.fVecX;

		m_vText[i].position.fVecX = (m_vText[i].position.fVecX + (m_vText[i].velocity.fVecX * fElapsedTime));
		m_vText[i].position.fVecY = (m_vText[i].position.fVecY + (m_vText[i].velocity.fVecY * fElapsedTime));

		m_vText[i].color.a = 3.0f * (m_vText[i].fLife / m_vText[i].fMaxlife);
		if (m_vText[i].fLife <= 0.0f)
		{
			m_vText.erase(m_vText.begin() + i--);
			continue;
		}
	}

	for (unsigned int i = 0; i < m_vScreenText.size(); ++i)
	{
		m_vScreenText[i].fLife -= fElapsedTime;
		m_vScreenText[i].velocity.fVecX;

		m_vScreenText[i].position.fVecX = (m_vScreenText[i].position.fVecX + (m_vScreenText[i].velocity.fVecX * fElapsedTime));
		m_vScreenText[i].position.fVecY = (m_vScreenText[i].position.fVecY + (m_vScreenText[i].velocity.fVecY * fElapsedTime));

		m_vScreenText[i].color.a = 3.0f * (m_vScreenText[i].fLife / m_vScreenText[i].fMaxlife);
		if (m_vScreenText[i].fLife <= 0.0f)
		{
			m_vScreenText.erase(m_vScreenText.begin() + i--);
			continue;
		}
	}
}

void CFloatingText::Render(void)
{
	CBitmapFont tBitmapFont;
	for (unsigned int i = 0; i < m_vText.size(); ++i)
	{
		tBitmapFont.Print(m_vText[i].str.c_str(), (int)m_vText[i].position.fVecX - CGameplayState::GetInstance()->GetCamOffsetX(), 
			(int)m_vText[i].position.fVecY - CGameplayState::GetInstance()->GetCamOffsetY(), m_vText[i].fScale, m_vText[i].color);
	}
	for (unsigned int i = 0; i < m_vScreenText.size(); ++i)
	{
		tBitmapFont.Print(m_vScreenText[i].str.c_str(), (int)m_vScreenText[i].position.fVecX, (int)m_vScreenText[i].position.fVecY,
			m_vScreenText[i].fScale, m_vScreenText[i].color);
	}
}

// LUA Text helper!
int CFloatingText::AddText(lua_State *L)
{
	int n = lua_gettop(L);

	std::string str = lua_tostring(L, 1); // catch the text
	float fPosX = (float)lua_tonumber(L, 2); // catch posX
	float fPosY = (float)lua_tonumber(L, 3); // catch posX
	float fVecX = (float)lua_tonumber(L, 4); // catch posX
	float fVecY = (float)lua_tonumber(L, 5); // catch posX
	float fLife = (float)lua_tonumber(L, 6); // catch posX
	float fScale = (float)lua_tonumber(L, 7); // catch posX
	int nRed = (int)lua_tonumber(L, 8); // catch posX
	int nGreen = (int)lua_tonumber(L, 9); // catch posX
	int nBlue = (int)lua_tonumber(L, 10); // catch posX

	CFloatingText::GetInstance()->AddText(str, Vec2Df(fPosX + 38, fPosY), Vec2Df(fVecX, fVecY), fLife, fScale, D3DCOLOR_XRGB(nRed, nGreen, nBlue));
	return 0;
}


