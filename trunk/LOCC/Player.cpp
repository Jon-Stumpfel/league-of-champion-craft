#include "StdAfx.h"
#include "Player.h"


CPlayer::CPlayer(int nPlayerID)
{
	m_nPlayerID = nPlayerID;
	SetAP(nStartingAP);
	SetMetal(20);
	SetWood(20);
	SetPopCap(0);
	SetMaxPopCap(12);
	SetExp(0);
}


CPlayer::~CPlayer(void)
{
}
