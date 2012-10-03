#pragma once

#include "Unit.h"
class CTile;
class CAbility;

enum SCRIPT_TYPE {  }; 

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

class CScriptManager
{

public:

	void LoadScript( std::string szFilename, SCRIPT_TYPE eScript );
	void ExecuteTile( CAbility* pAbility, CTile* pTile );
	void ExecuteUnit( CAbility* pAbility, CUnit* pUnit );
	void Initialize( void );
	void Shutdown( void );
	
	static CScriptManager* GetInstance( void );

private:

	CScriptManager(void);
	~CScriptManager(void);
	CScriptManager(const CScriptManager&);
	CScriptManager& operator=(const CScriptManager&);

	static CScriptManager* s_Instance;

	std::pair< ScriptSpawnData, int > m_pScriptedSpawn;
	std::pair< ScriptMessageData, int > m_pScriptedMessage;

};

