#include "StdAfx.h"
#include "SaveSlotState.h"
#include "StateStack.h"


CSaveSlotState::CSaveSlotState(void)
{
}


CSaveSlotState::~CSaveSlotState(void)
{
}

CSaveSlotState* CSaveSlotState::GetInstance()
{
	static CSaveSlotState s_Instance;
	return &s_Instance;
}

void CSaveSlotState::Enter(void)
{
}
void CSaveSlotState::Exit(void)
{
}
void CSaveSlotState::Input(INPUT_ENUM input)
{
	switch (input)
	{
	case INPUT_CANCEL:
		CStateStack::GetInstance()->Pop();
		break;

	}
}
void CSaveSlotState::Update(float fElapsedTime)
{
}
void CSaveSlotState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 255, 0);
}