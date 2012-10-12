#pragma once

class CPlayer
{
private:

	int m_nPlayerID;
	int m_nAP;
	int m_nMetal;
	int m_nWood;
	int m_nPopCap;
	int m_nMaxPopCap;
	int m_nExp;
	int m_nJoystickNum;
	bool m_bAI;
public:

	CPlayer(int nPlayerID);
	~CPlayer(void);

	bool GetAI(void) { return m_bAI;}
	void SetAI(bool b) { m_bAI = b;}

	int GetAP(void) { return m_nAP;}
	void SetAP(int AP){m_nAP = AP;}

	int GetMetal(void) { return m_nMetal;}
	void SetMetal(int m) { m_nMetal = m;}

	int GetWood(void) { return m_nWood;}
	void SetWood(int w){ m_nWood = w;}

	int GetPopCap(void) { return m_nPopCap;}
	void SetPopCap(int p) { m_nPopCap = p;}

	int GetMaxPopCap(void) { return m_nMaxPopCap;}
	void SetMaxPopCap(int p) { m_nMaxPopCap = p;}

	int GetExp(void) { return m_nExp;}
	void SetExp(int e) { m_nExp = e;}

	int GetJoyNum(void) { return m_nJoystickNum;}
	void SetJoyNum(int j) { m_nJoystickNum = j;}

	int GetPlayerID(void) { return m_nPlayerID;}

};

