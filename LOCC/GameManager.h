#pragma once
#include "Unit.h"
#include "ScriptManager.h"
#include "IMessage.h"
#include "StateStack.h"
#include "GameOverState.h"
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

	void SetCurrentPhase(GAME_PHASE phase) { m_nCurrentPhase = phase;}
	void SetPhaseCount(int count) { m_nPhaseCount = count;}

	void AddUnit(CUnit* pUnit);
	void RemoveUnit(CUnit* pUnit);

	CUnit* GetChampion(int nPlayerID);
	CUnit* FindUnit(int posX, int posY);
	CUnit* FindUnit(Vec2D pos);

	int GetLevel(void);
	void LoadLevel(std::string sFileName);
	void LoadMap(int nLevelNum);
	void LoadSave(int nSlot);

	void Reset(void);
	void NewGame(void);
	void NextPhase(void);

	int GetCurrentTurn(void); // This splits it up so a "turn" is techcnially 1 phase

	void Update(float fElapsedTime);

	void SetNextPlayer(int nPlayerID);

	void ShutDown(void);


	static void MessageProc(IMessage* pMsg);

	GAME_PHASE GetCurrentPhase(void) { return m_nCurrentPhase;}

	// This is only for GameplayState to render minimap circles for units. Please do not use it
	// to modify anything inside this array
	const std::vector<CUnit*> GetUnits(void) { return m_vUnits;}

	void AddScriptSpawn(ScriptedSpawn data) { m_vScriptSpawns.push_back(data);}

	void SaveGame(int nSlot);
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
	int m_nPhaseCount;

	bool m_bNewGame;


	int m_nNewPlayerID;

	
};

