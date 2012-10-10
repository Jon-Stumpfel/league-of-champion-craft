#pragma once

class CFrame
{
public:

	CFrame(void);
	~CFrame(void);
	RECT GetRect() {return m_rImageRect;}
	int GetFrame() {return m_iFrameNumber;}
	float GetTimePlayed() {return m_fTimePlayed;}
	void SetImageRect(RECT temprect) {m_rImageRect = temprect;}
	void SetFrameNumber(int tempframenum) {m_iFrameNumber = tempframenum;}
	void SetTimePlayed(float temptime) {m_fTimePlayed = temptime;}
	Vec2D GetAnchorPoint() {return AnchorPoint;}
	void SetAnchorPoint(Vec2D temppoint) {AnchorPoint = temppoint;}
private:
	RECT m_rImageRect;
	int m_iFrameNumber;
	float m_fTimePlayed;
	Vec2D AnchorPoint;
};