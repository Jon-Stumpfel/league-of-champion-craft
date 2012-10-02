#pragma once
#include "StdAfx.h"
#include "Unit.h"
class CPlayer;

class CGameManager
{
	static CGameManager* GetInstance(void);
	static void DeleteInstance(void);	

	CPlayer* CreatePlayer(bool bAIControlled = false);
	CPlayer* GetPlayer(int nPlayerID);

	void MoveUnit(CUnit* u, int nDirection);

	int GetLevel(void);
	void LoadLevel(std::string sFileName);
	void LoadLevel(int nLevelNum);

	void LoadSave(int nSlot);

	void Reset(void);
	void NewGame(void);

private:

	CGameManager(void);
	~CGameManager(void);
	CGameManager(const CGameManager&);
	CGameManager& operator=(const CGameManager&);

	static CGameManager* s_Instance;

	CPlayer* m_pCurrentPlayer;
	CPlayer* m_pNextPlayer;
	std::vector<CPlayer*> m_vPlayers;

	std::vector<CUnit*> m_vUnits;

	int m_nCurrentLevel;
	int m_nSaveSlot;

	bool m_bNewGame;

	
};

