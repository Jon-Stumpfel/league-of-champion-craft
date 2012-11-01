#include "StdAfx.h"
#include "HUD.h"
#include "GraphicsManager.h"

CHUD::CHUD(void)
{
}


CHUD::~CHUD(void)
{
}

CHUD* CHUD::GetInstance(void)
{
	static CHUD s_Instance;
	return &s_Instance;
}

void CHUD::Initialize(void)
{
	m_nHudPartsID = -1;

	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\HUDnoguides.png"), _T("hudparts"), D3DCOLOR_XRGB(255, 0, 255));
	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\healthbar.png"), _T("healthbar"), D3DCOLOR_XRGB(255, 255, 255));
}
RECT CHUD::GetHealthbar(void)
{
	RECT rect;
	rect.left = 17;
	rect.top = 62;
	rect.right = 111;
	rect.bottom = 71;

	return rect;
}

RECT CHUD::GetPortrait(UNIT_TYPE unit)
{
	RECT rect;
	switch (unit)
	{
	case UT_HERO:
		{
			rect.left = 633;
			rect.top = 506;
			rect.right = 717;
			rect.bottom = 586;
		}
		break;
	case UT_SWORDSMAN:
		{
			rect.left = 530;
			rect.top = 505;
			rect.right = 614;
			rect.bottom = 586;
		}
		break;
	case UT_ARCHER:
		{
			rect.left = 229;
			rect.top = 505;
			rect.right = 312;
			rect.bottom = 588;
		}
		break;
	case UT_ICEBLOCK:
		{
			rect.left = 130;
			rect.top = 505;
			rect.right = 213;
			rect.bottom = 588;
		}
		break;
	case UT_CASTLE:
		{
			rect.left = 27;
			rect.top = 505;
			rect.right = 111;
			rect.bottom = 589;
		}
		break;
	case UT_SKELETON:
		{
			rect.left = 427;
			rect.top = 505;
			rect.right = 511;
			rect.bottom = 589;
		}
		break;
	case UT_CAVALRY:
		{
			rect.left = 328;
			rect.top = 505;
			rect.right = 410;
			rect.bottom = 588;
		}
		break;
	}
	return rect;
}
RECT CHUD::GetRect(HUD_PART part)
{
	RECT rect;

	switch (part)
	{
	case HP_STATUSBAR:
		{
			rect.left = 56;
			rect.top = 763;
			rect.right = 858;
			rect.bottom = 804;
		}
		break;
	case HP_HIGHLIGHTCARD:
		{
			rect.left = 571;
			rect.top = 71;
			rect.right = 735;
			rect.bottom = 155;
		}
		break;

	case HP_BORDERBAR:
		{
			rect.left = 29;
			rect.top = 609;
			rect.right = 717;
			rect.bottom = 693;

		}
		break;
	case HP_MINIMAP:
		{
			rect.left = 40;
			rect.top = 48;
			rect.right = 194;
			rect.bottom = 202;
		}
		break;
	case HP_MAINBAR:
		{
			rect.left = 46;
			rect.top = 266;
			rect.right = 413;
			rect.bottom = 372;

		}
		break;
	case HP_SPELLBAR:
		{
			rect.left = 46;
			rect.top = 379;
			rect.right = 413;
			rect.bottom = 486;
		}
		break;
	case HP_TURNWINDOW:
		{
			rect.left = 245;
			rect.top = 33;
			rect.right = 500;
			rect.bottom = 117;
		}
		break;
	case HP_UNITCARD:
		{
			rect.left = 441;
			rect.top = 317;
			rect.right = 605;
			rect.bottom = 491;
		}
		break;
	case HP_SELECTICON:
		{
			rect.left = 361;
			rect.top = 142;
			rect.right = 431;
			rect.bottom = 212;
		}
		break;
	};

	return rect;
}