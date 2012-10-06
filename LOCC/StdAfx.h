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

#include <cassert>

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
};
