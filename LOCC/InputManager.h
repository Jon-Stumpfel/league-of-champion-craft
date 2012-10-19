#pragma once

enum INPUT_ENUM { INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, 
				  INPUT_ACCEPT, INPUT_CANCEL, INPUT_START, INPUT_CAM_UP, INPUT_CAM_DOWN,
				  INPUT_CAM_LEFT, INPUT_CAM_RIGHT, INPUT_SELECT, 
				  INPUT_AI_CLEAR, INPUT_AI_SELECTED, INPUT_AI_MOVED, INPUT_AI_ATTACKED,
				  INPUT_AI_SELECTABILITY_1, INPUT_AI_SELECTABILITY_2};


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
private:
	bool Running;
	CInputManager(void);
	~CInputManager(void);
	CInputManager(const CInputManager&);
	CInputManager& operator=(const CInputManager&);

	static CInputManager* s_Instance;

};

