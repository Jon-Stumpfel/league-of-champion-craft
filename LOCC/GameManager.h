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
	CPlayer* GetCurrentPlayer(void);
	void SetCurrentPlayer(int nPlayerID) { m_pCurrentPlayer = m_vPlayers[nPlayerID];}
	CPlayer* GetPlayer(int nPlayerID);

	void AddUnit(CUnit* pUnit);
	void RemoveUnit(CUnit* pUnit);

	CUnit* GetChampion(int nPlayerID);
	CUnit* FindUnit(int posX, int posY);
	CUnit* FindUnit(Vec2D pos);

	int GetLevel(void);
	void LoadLevel(std::string sFileName);
	void LoadLevel(int nLevelNum);
	void LoadSave(int nSlot);

	void Reset(void);
	void NewGame(void);
	void NextPhase(void);

	int GetCurrentTurn(void) { return m_nTurnCount;}

	void Update(float fElapsedTime);

	void SetNextPlayer(int nPlayerID);

	void ShutDown(void);


	static void MessageProc(IMessage* pMsg);

	GAME_PHASE GetCurrentPhase(void) { return m_nCurrentPhase;}

	// This is only for GameplayState to render minimap circles for units. Please do not use it
	// to modify anything inside this array
	const std::vector<CUnit*> GetUnits(void) { return m_vUnits;}

	void AddScriptSpawn(ScriptedSpawn data) { m_vScriptSpawns.push_back(data);}
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
	std::vector< ScriptedMessage > m_vScriptMessage;
	std::vector< ScriptedSpawn > m_vScriptSpawns;

	void LoadUnitsFromScript(void);

	int m_nCurrentLevel;
	int m_nSaveSlot;

	GAME_PHASE m_nCurrentPhase;
	int m_nTurnCount;

	bool m_bNewGame;


	int m_nNewPlayerID;

	
};

