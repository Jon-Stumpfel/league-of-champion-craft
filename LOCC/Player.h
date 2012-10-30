#pragma once

struct GameStats
{
	int nChampionDamageDone;
	int nChampionHealingDone;
	int nPlayerEXPEarned;
	int nPlayerWoodEarned;
	int nPlayerMetalEarned;
	int nPlayerWoodSpent;
	int nPlayerMetalSpent;
	int nPlayerAPSpent;

	int nSwordsmanCreated;
	int nArcherCreated;
	int nCalvaryCreated;

	int nSwordsmanDamageDone;
	int nArcherDamageDone;
	int nCalvaryDamageDone;

	int nSwordsmanKilled;
	int nArcherKilled;
	int nCavalryKilled;
};
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

	int m_nMillsOwned;
	int m_nMinesOwned;

	GameStats m_tStats;
public:

	CPlayer(int nPlayerID);
	~CPlayer(void);

	int GetMillsOwned(void) { return m_nMillsOwned;}
	void SetMillsOwned(int i) { m_nMillsOwned = i;}
	int GetMinesOwned(void) { return m_nMinesOwned;}
	void SetMinesOwned(int i ) { m_nMinesOwned = i;}

	static int GetMillsOwned(lua_State* L);
	static int GetMinesOwned(lua_State* L);

	GameStats* GetStats(void) { return &m_tStats;}

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

