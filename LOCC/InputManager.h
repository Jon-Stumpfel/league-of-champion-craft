#pragma once

enum INPUT_ENUM { INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, 
				  INPUT_ACCEPT, INPUT_CANCEL, INPUT_START, INPUT_CAM_UP, INPUT_CAM_DOWN, INPUT_CAM_LEFT, INPUT_CAM_RIGHT };


class CInputManager
{

public:

	static CInputManager* GetInstance(void);
	static void DeleteInstance(void);

	void Update(float fElapsedTime);
	void Input(void);

private:

	CInputManager(void);
	~CInputManager(void);
	CInputManager(const CInputManager&);
	CInputManager& operator=(const CInputManager&);

	static CInputManager* s_Instance;

};

