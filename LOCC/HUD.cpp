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

	CGraphicsManager::GetInstance()->LoadImageW(_T("Assets\\HUD\\hud_parts.png"), _T("hudparts"), D3DCOLOR_XRGB(255, 0, 255));
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
	case HP_MINIMAP:
		{
			rect.left = 27;
			rect.top = 23;
			rect.right = 233;
			rect.bottom = 212;
		}
		break;
	case HP_MAINBAR:
		{
			rect.left = 26;
			rect.top = 230;
			rect.right = 429;
			rect.bottom = 376;

		}
		break;
	case HP_SPELLBAR:
		{
			rect.left = 26;
			rect.top = 382;
			rect.right = 429;
			rect.bottom = 491;
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
			rect.top = 314;
			rect.right = 629;
			rect.bottom = 492;
		}
		break;
	};

	return rect;
}