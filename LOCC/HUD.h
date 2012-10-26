#pragma once
#include "StdAfx.h"

enum HUD_PART { HP_MINIMAP, HP_MAINBAR, HP_SPELLBAR, HP_TURNWINDOW, HP_UNITCARD };
class CHUD
{

public:
	static CHUD* GetInstance(void);
	
	void Initialize(void);

	RECT GetRect(HUD_PART part);
	RECT GetPortrait(UNIT_TYPE unit);
	RECT GetHealthbar(void);
private:
	CHUD(void);
	~CHUD(void);
	CHUD(const CHUD&);
	CHUD& operator=(const CHUD&);

	int m_nHudPartsID;
};

