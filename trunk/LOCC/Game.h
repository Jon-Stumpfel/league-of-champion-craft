#pragma once

#include "StdAfx.h"
#include "IGameState.h"
class CGame
{

public:

	static CGame* GetInstance(void);

	void Initialize(HWND hWnd, HINSTANCE hInstance,
				int nScreenWidth, int nScreenHeight,
				bool bIsWindowed);

	bool Main(void);
	void Shutdown(void);

	int GetWindowWidth(void) { return m_nWidth;}
	int GetWindowHeight(void) { return m_nHeight;}
private:

	CGame(void);
	~CGame(void);
	CGame(const CGame&);
	CGame& operator=(const CGame&);


	// 3 actions for each frame:
		bool Input(void);
		void Update(void);
		void Render(void);

	int m_nWidth;		
	int m_nHeight;		
	HWND m_hWnd;
	bool m_bIsWindowed;
	DWORD m_dwCurrTime;
	IGameState* currentState;


};

