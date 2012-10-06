#pragma once

class CFrame
{
public:

	CFrame(void);
	~CFrame(void);

private:
	Vec2D Position;
	int width;
	int height;
	RECT m_rImageRect;
	int m_iFrameNumber;
	float m_fTimePlayed;
};

