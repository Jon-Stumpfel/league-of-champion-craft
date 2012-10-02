#include "StdAfx.h"
#include "Game.h"


CGame* CGame::GetInstance(void)
{	
	static CGame s_Instance;

	return &s_Instance;

}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance,
	int nScreenWidth, int nScreenHeight,
	bool bIsWindowed)
{

}

bool CGame::Main(void)
{
	return true;
}
void CGame::Shutdown(void)
{

}

CGame::CGame(void)
{

}
CGame::~CGame(void)
{

}



// 3 actions for each frame:
bool CGame::Input(void)
{
	return true;
}
void CGame::Update(void)
{
}
void CGame::Render(void)
{
}