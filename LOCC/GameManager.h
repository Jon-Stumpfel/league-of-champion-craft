#pragma once
#include "StdAfx.h"
#include "Unit.h"
#include "ScriptManager.h"
#include "IMessage.h"
class CPlayer;

class CGameManager
{

public:

	static CGameManager* GetInstance(void);
	static void DeleteInstance(void);	

	CPlayer* CreatePlayer(bool bAIControlled = false);
	CPlayer* GetPlayer(int nPlayerID);

	void MoveUnit(CUnit* u, int nDirection);
	void AddUnit(CUnit* pUnit);
	void RemoveUnit(CUnit* pUnit);

	int GetLevel(void);
	void LoadLevel(std::string sFileName);
	void LoadLevel(int nLevelNum);

	void LoadSave(int nSlot);

	void Reset(void);
	void NewGame(void);

	void Update(float fElapsedTime);

	void SetNextPlayer(int nPlayerID);

	void ShutDown(void);


	static void MessageProc(IMessage* pMsg);
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
	std::vector< ScriptMessageData > m_vScriptMessage;
	std::vector< ScriptSpawnData > m_vScritpSpawns;

	int m_nCurrentLevel;
	int m_nCurrentPhase;
	int m_nSaveSlot;

	bool m_bNewGame;


	int m_nNewPlayerID;

	
};

