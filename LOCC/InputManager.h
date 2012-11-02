#pragma once

#include "StdAfx.h"
enum INPUT_ENUM { INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, 
				  INPUT_ACCEPT, INPUT_CANCEL, INPUT_START, INPUT_CAM_UP, INPUT_CAM_DOWN,
				  INPUT_CAM_LEFT, INPUT_CAM_RIGHT, INPUT_SELECT, 
				  INPUT_AI_CLEAR, INPUT_AI_SELECTED, INPUT_AI_MOVED, INPUT_AI_ATTACKED,
				  INPUT_AI_SELECTABILITY_1, INPUT_AI_SELECTABILITY_2, INPUT_AI_SELECTABILITY_3, INPUT_AI_CHAMPSPELL, 
					INPUT_AI_SELECTSPELL1, INPUT_AI_SELECTSPELL2, INPUT_AI_SELECTSPELL3, INPUT_AI_SELECTSPELL4, 
					INPUT_AI_ORDERFINISHED, INPUT_BUMPERLEFT, INPUT_BUMPERRIGHT};


class CInputManager
{

public:

	static CInputManager* GetInstance(void);
	static void DeleteInstance(void);

	void Update(float fElapsedTime);
	bool Input(void);

	void Initialize(HWND hWnd, HINSTANCE hInstance);

	void Shutdown(void);
	void SetRunning(bool running) {Running = running;}
	void SetInMenu(bool b);


	void* m_pJoy1;
	void* m_pJoy2;
	void* m_pJoyThatIsUnplugged;

	int m_nNumJoys;

private:



	bool Running;

	bool m_bInMenu;
	CInputManager(void);
	~CInputManager(void);
	CInputManager(const CInputManager&);
	CInputManager& operator=(const CInputManager&);

	static CInputManager* s_Instance;


};

