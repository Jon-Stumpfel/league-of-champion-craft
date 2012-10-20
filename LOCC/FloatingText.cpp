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

void CFloatingText::Update(float fElapsedTime)
{
	for (unsigned int i = 0; i < m_vText.size(); ++i)
	{
		m_vText[i].fLife -= fElapsedTime;
		m_vText[i].velocity.fVecX;
		std::wostringstream woss;
		woss << "PosY: " << m_vText[i].position.fVecY << ", Vel Y: " << m_vText[i].velocity.fVecY << ", fElapsedtime: " << fElapsedTime << ", Change: " << (m_vText[i].velocity.fVecY * fElapsedTime) << '\n';
		OutputDebugString(woss.str().c_str());

		m_vText[i].position.fVecX = (m_vText[i].position.fVecX + (m_vText[i].velocity.fVecX * fElapsedTime));
		m_vText[i].position.fVecY = (m_vText[i].position.fVecY + (m_vText[i].velocity.fVecY * fElapsedTime));

		m_vText[i].color.a = 3.0f * (m_vText[i].fLife / m_vText[i].fMaxlife);
		if (m_vText[i].fLife <= 0.0f)
		{
			m_vText.erase(m_vText.begin() + i--);
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
}