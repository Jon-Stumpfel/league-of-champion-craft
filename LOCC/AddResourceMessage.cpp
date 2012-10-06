#include "StdAfx.h"
#include "AddResourceMessage.h"


CAddResourceMessage::CAddResourceMessage(TILE_TYPE tile, int playerID) : CMessage(MSG_ADDRESOURCE)
{
	m_eTile = tile;
	m_nPlayerID = playerID;
}

CAddResourceMessage::~CAddResourceMessage(void)
{
}
