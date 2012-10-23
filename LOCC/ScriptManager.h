#pragma once

#include "Unit.h"
class CTile;
class CAbility;
class CUnit;


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

struct MapModification
{
	int posX;
	int posY;
	SPELL_TYPE modType;
};
typedef std::pair<int, ScriptSpawnData> ScriptedSpawn;
typedef std::pair<int, ScriptMessageData> ScriptedMessage;

class CScriptManager
{

public:

	void LoadScript( std::string szFilename, SCRIPT_TYPE eScript );
	void Execute( CAbility* pAbility, CTile* pTile, CUnit* pCaster);
	void Initialize( void );
	void Shutdown( void );
	
	static CScriptManager* GetInstance( void );
	static void DeleteInstance(void);

private:

			lua_State* L;

	CScriptManager(void);
	~CScriptManager(void);
	CScriptManager(const CScriptManager&);
	CScriptManager& operator=(const CScriptManager&);

	static CScriptManager* s_Instance;


	std::pair< ScriptMessageData, int > m_pScriptedMessage;

};

