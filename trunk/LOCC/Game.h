#include "StdAfx.h"


#pragma once
class CGame
{
public:

	static CGame* GetInstance(void);

	void Initialize(HWND hWnd, HINSTANCE hInstance,
				int nScreenWidth, int nScreenHeight,
				bool bIsWindowed);

	bool Main(void);
	void Shutdown(void);

private:
	CGame(void);
	~CGame(void);
	CGame(const CGame&);
	CGame& operator=(const CGame&);


	// 3 actions for each frame:
		bool Input(void);
		void Update(void);
		void Render(void);
};

