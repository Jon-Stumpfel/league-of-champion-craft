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

#include <dbghelp.h>	//	Used for Dump File
#pragma comment(lib, "dbghelp.lib")

#include "lib\lua.hpp" // lua 5.1
#pragma comment(lib, "lib\\lua5.1.lib")
#include <vector>
#include <string>
using std::vector;
using std::string;

// Gameplay stuff
struct Vec2D
{
	int nPosX;
	int nPosY;
	inline Vec2D(void) { }
	inline Vec2D(int x, int y) { nPosX = x; nPosY = y;}
};

enum ANIM_TYPE { AT_IDLE, AT_WALK_N, AT_WALK_S, AT_WALK_E, AT_WALK_W, AT_ATTACK_N, 
	AT_ATTACK_S, AT_ATTACK_E, AT_ATTACK_W, AT_ABILITY_N, AT_ABILITY_S, AT_ABILITY_E, AT_ABILITY_W };

enum UNIT_TYPE { UT_CASTLE, UT_HERO, UT_ARCHER, UT_SWORDSMAN, UT_CAVALRY, UT_SKELETON, UT_ICEBLOCK }; 

enum MSG_TYPE { MSG_SPAWNUNIT, MSG_DESPAWNUNIT, MSG_ADDRESOURCE };

enum TILE_TYPE		{ TT_PLAINS, TT_FOREST, TT_MOUNTAINS, TT_FARM, TT_MILL, TT_MINE, TT_WATER };
enum TILE_STATUS	{ TS_FROZEN, TS_RESOURCETILE, TS_OCCUPIED, TS_CAPTURING, TS_CAPTURED, TS_IS_DEAD, TS_ISPASSABLE};

// resource amounts
const int POP_PER_FARM = 6;
const int METAL_PER_MINE = 10;
const int WOOD_PER_MILL = 10;
const int AP_PER_CAPTURE = 2;