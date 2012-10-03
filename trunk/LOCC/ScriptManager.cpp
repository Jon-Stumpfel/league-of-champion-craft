#include "StdAfx.h"
#include "ScriptManager.h"
#include "Ability.h"
#include "Tile.h"

CScriptManager* CScriptManager::s_Instance = nullptr;

CScriptManager::CScriptManager(void)
{
}

CScriptManager::~CScriptManager(void)
{
}

CScriptManager* CScriptManager::GetInstance( void )
{
	if( s_Instance == nullptr )
		s_Instance = new CScriptManager;

	return s_Instance;
}

void CScriptManager::LoadScript( std::string szFilename, SCRIPT_TYPE eScript )
{

}

void CScriptManager::ExecuteTile( CAbility* pAbility, CTile* pTile )
{

}

void CScriptManager::ExecuteUnit( CAbility* pAbility, CUnit* pUnit )
{

}

void CScriptManager::Initialize( void )
{

}

void CScriptManager::Shutdown( void )
{

}
