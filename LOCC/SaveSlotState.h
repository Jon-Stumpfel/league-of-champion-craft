#pragma once

#include "IGameState.h"


class CSaveSlotState : public IGameState
{
public:
	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Input(INPUT_ENUM input);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	static CSaveSlotState* GetInstance();

private:

	int m_nHighlightedSlot;
	int m_nMenuChoice;
	int m_nConfirmChoice;
	bool m_bShowMenu;
	bool m_bConfirm;
	void ReadSlot(int nSlot);

	bool m_bFromMainMenu;
	CSaveSlotState(void);
	virtual ~CSaveSlotState(void);
	CSaveSlotState(const CSaveSlotState&);
	CSaveSlotState* operator=( CSaveSlotState& );
};

