#pragma once

#include "Unit.h"
class CTile;
class CAbility;



struct ScriptSpawnData
{
	UNIT_TYPE eType;
	int nFacing;
	Vec2D sPos;
	int nPlayerID;
};
	
struct ScriptMessageData
{
	std::string szMessage;
};

typedef std::pair<int, ScriptSpawnData> ScriptedSpawn;
typedef std::pair<int, ScriptMessageData> ScriptedMessage;

class CScriptManager
{

public:

	void LoadScript( std::string szFilename, SCRIPT_TYPE eScript );
	void ExecuteTile( CAbility* pAbility, CTile* pTile );
	void ExecuteUnit( CAbility* pAbility, CUnit* pUnit );
	void Initialize( void );
	void Shutdown( void );
	
	static CScriptManager* GetInstance( void );
	static void DeleteInstance(void);
private:

	CScriptManager(void);
	~CScriptManager(void);
	CScriptManager(const CScriptManager&);
	CScriptManager& operator=(const CScriptManager&);

	static CScriptManager* s_Instance;


	std::pair< ScriptMessageData, int > m_pScriptedMessage;

};

