#include "StdAfx.h"
#include "Player.h"


CPlayer::CPlayer(int nPlayerID)
{
	m_nPlayerID = nPlayerID;
	SetAP(30);
	SetMetal(20);
	SetWood(20);
	SetPopCap(12);
	SetExp(0);
}


CPlayer::~CPlayer(void)
{
}
