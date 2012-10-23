// Precompiled headers

#pragma once
#include <windows.h>	//	Needed for Windows Applications.
#include <tchar.h>
#include <vld.h>
#include "Game.h"
#include "SGD Wrappers\CSGD_Direct3D.h"
#include "SGD Wrappers\CSGD_DirectInput.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "SGD Wrappers\CSGD_XAudio2.h"
#include "SGD Wrappers\SGD_Math.h"
#include "SGD Wrappers\SGD_String.h"
#include "SGD Wrappers\SGD_Util.h"
#include "SGD Wrappers\tinystr.h"
#include "SGD Wrappers\tinyxml.h"
#include "BitmapFont.h"
#include <dbghelp.h>	//	Used for Dump File
#pragma comment(lib, "dbghelp.lib")

#include "lib\lua.hpp" // lua 5.1
#pragma comment(lib, "lib\\lua5.1.lib")
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
using std::ostringstream;
using std::vector;
using std::string;


	enum ANIM_TYPE { AT_IDLE, AT_WALK_N, AT_WALK_S, AT_WALK_E, AT_WALK_W, AT_ATTACK_N, 
		AT_ATTACK_S, AT_ATTACK_E, AT_ATTACK_W, AT_ABILITY_N, AT_ABILITY_S, AT_ABILITY_E, AT_ABILITY_W, AT_DEATH };

	enum UNIT_TYPE { UT_CASTLE, UT_HERO, UT_ARCHER, UT_SWORDSMAN, UT_CAVALRY, UT_SKELETON, UT_ICEBLOCK }; 

	enum MSG_TYPE { MSG_SPAWNUNIT, MSG_DESPAWNUNIT, MSG_ADDRESOURCE };

	enum TILE_TYPE		{ TT_PLAINS, TT_FOREST, TT_MOUNTAINS, TT_WATER, TT_FARM, TT_MILL, TT_MINE, TT_CASTLE };
	enum TILE_STATUS	{ TS_FROZEN, TS_RESOURCETILE, TS_OCCUPIED, TS_CAPTURING, TS_CAPTURED, TS_IS_DEAD, TS_ISPASSABLE};

	enum SPELL_TYPE { SP_FIREBALL, SP_CHARGE, SP_TEST, SP_SPAWNARCHER, SP_SPAWNSWORD, SP_SPAWNCALV, SP_HEAL,
		SP_SHIELD, SP_SPEED, SP_MELEEATTACK, SP_ARCHERRANGEDATTACK, SP_MOVE, SP_CHAMPSPELL, 
		SP_CARTOGRAPHY, SP_DESTROYFOREST, SP_HEALBURST, SP_RALLY,  SP_NUMSPELLS};

	enum SCRIPT_TYPE { ST_LEVEL };

	enum PRTCL_TYPE { TEST, TESTSECOND, PT_FIRE, PT_CARTOGRAPHY, PT_DESTROYFOREST, PT_HEALCROSS, PT_RALLY };

	enum GAME_PHASE { GP_MOVE, GP_ATTACK };


	// resource amounts
	const int POP_PER_FARM = 6;
	const int METAL_PER_MINE = 10;
	const int WOOD_PER_MILL = 10;
	const int AP_PER_CAPTURE = 2;
	const int nStartingAP = 30;

	// fake tile stuff
	const int nFakeTileWidth = 64 +26;
	const int nFakeTileHeight = 64 + 27;
	const int nMouseSensitivity = 55555555;	
	const int nCameraScrollSpeed = 2;
	

	// Gameplay stuff
	struct Vec2D
	{
		int nPosX;
		int nPosY;
		inline Vec2D(void) { }
		inline Vec2D(int x, int y) { nPosX = x; nPosY = y;}
		inline friend bool operator==(const Vec2D& rhs, const Vec2D& lhs){ return ((rhs.nPosX == lhs.nPosX) && ( rhs.nPosY == lhs.nPosY));}
	};

	struct Vec2Df
	{
		float fVecX;
		float fVecY;
		inline Vec2Df( void ) { }
		inline Vec2Df( float x, float y ) { fVecY = y; fVecX = x; }
	};
	
	inline Vec2D TranslateToPixel(Vec2D gamePosition)
	{
		int x = (nFakeTileWidth / 2 * gamePosition.nPosX) - (nFakeTileHeight / 2 * gamePosition.nPosY);
		int y = (nFakeTileWidth / 2 * gamePosition.nPosX) + (nFakeTileHeight  / 2 * gamePosition.nPosY);

		return Vec2D(x, y);
	}
	inline int TranslateToPixel(lua_State* L)
	{
		int n = lua_gettop(L);
		int x = (int)lua_tonumber(L, 1);
		int y = (int)lua_tonumber(L, 2);

		Vec2D vec = TranslateToPixel(Vec2D(x, y));

		lua_pushnumber(L, vec.nPosX);
		lua_pushnumber(L, vec.nPosY);

		return 2;

	}

	struct UnitAnimation
	{
		UNIT_TYPE unitType;
		ANIM_TYPE animationType;
		float fCurrentTime;
	};
	
