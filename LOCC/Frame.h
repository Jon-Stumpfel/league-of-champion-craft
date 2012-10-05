#pragma once

class CFrame
{
public:

	CFrame(void);
	~CFrame(void);

private:

	int m_nImgID;
	float m_fTimePlayed;

	Vec2D m_sPos;
	Vec2D m_sAnchorPos;

};

