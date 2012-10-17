#include "StdAfx.h"
#include "SaveSlotState.h"
#include "StateStack.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "Hero.h"
#include "Player.h"

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
	m_bShowMenu = false;
	m_bConfirm = false;
	m_nConfirmChoice = 0;
	m_nHighlightedSlot = 1;
	m_nMenuChoice = 0;

	CStateStack::GetInstance()->SetRenderTopOnly(true);
}
void CSaveSlotState::Exit(void)
{
	CStateStack::GetInstance()->SetRenderTopOnly(false);

}
void CSaveSlotState::Input(INPUT_ENUM input)
{
	std::wostringstream woss;
	woss << "SaveState Input: " << input << " at " << GetTickCount() << "\n";
	OutputDebugString(woss.str().c_str());
	switch (input)
	{
	case INPUT_RIGHT:
		{
			if (!m_bShowMenu)
			{
				m_nHighlightedSlot++;
				if (m_nHighlightedSlot > 3)
					m_nHighlightedSlot = 1;
			}
			else
			{
				if (m_bConfirm)
				{
					m_nConfirmChoice++;
					if (m_nConfirmChoice > 1)
						m_nConfirmChoice = 1;
				}
			}

		}
		break;
	case INPUT_LEFT:
		{
			if (!m_bShowMenu)
			{
				m_nHighlightedSlot--;
				if (m_nHighlightedSlot < 1)
					m_nHighlightedSlot = 3;
			}
			else
			{
				if (m_bConfirm)
				{
					m_nConfirmChoice--;
					if (m_nConfirmChoice < 0)
						m_nConfirmChoice = 0;
				}
			}
		}
		break;
	case INPUT_UP:
		{
			if (m_bShowMenu)
			{
				m_nMenuChoice--;
				if (m_nMenuChoice < 0)
					m_nMenuChoice = 2;
			}
		}
		break;
	case INPUT_DOWN:
		{
			if (m_bShowMenu)
			{
				m_nMenuChoice++;
				if (m_nMenuChoice > 2)
					m_nMenuChoice = 0;
			}
		}
		break;
	case INPUT_ACCEPT:
		{
			if (!m_bShowMenu)
			{
				m_bShowMenu = true;
				break;
			}
			else
			{
				if (m_bConfirm)
				{
					if (m_nConfirmChoice == 1)
					{
						// execute whatever we are on in menu choice
						switch (m_nMenuChoice)
						{
						case 0: // Load
							{
								CGameManager::GetInstance()->LoadSave(m_nHighlightedSlot);
								CStateStack::GetInstance()->Pop();
								m_nConfirmChoice = 0;
								return;
							}
							break;
						case 1: // Save!
							{
								CGameManager::GetInstance()->SaveGame(m_nHighlightedSlot);
								m_nConfirmChoice = 0;
								m_bConfirm = false;
								return;
							}
							break;
						case 2: // Delete!
							{
								std::ostringstream oss;
								oss << "Assets\\Scripts\\saveslot" << m_nHighlightedSlot << ".xml";
								std::remove(oss.str().c_str());
								m_bConfirm = false;
								m_nConfirmChoice = 0;

							//	m_bShowMenu = false;
							}
							break;
						}
					}
					else
					{
						m_bConfirm = false;
						break;
					}
				}
				else
					m_bConfirm = true;
			}
		}
		break;
	case INPUT_CANCEL:
		{
			if (m_bShowMenu)
			{
				if (m_bConfirm)
				{
					m_bConfirm = false;
					break;
				}
				m_bShowMenu = false;
				break;
			}

			CStateStack::GetInstance()->Pop();
		}
		break;

	}
}
void CSaveSlotState::Update(float fElapsedTime)
{
}
void CSaveSlotState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0, 0, 0);

	CBitmapFont m_pBitmapFont;

	ReadSlot(1);
	ReadSlot(2);
	ReadSlot(3);
	if (m_bShowMenu)
	{
		std::ostringstream woss;
		woss << "Load from Slot";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 370, 480, 255, 255, 255);
		m_pBitmapFont.Print(woss.str().c_str(), 370, 480, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Save to Slot";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 370, 500, 255, 255, 255);
		m_pBitmapFont.Print(woss.str().c_str(), 370, 500, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Delete Slot";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 370, 520, 255, 255, 255);
		m_pBitmapFont.Print(woss.str().c_str(), 370, 520, 0.3f, D3DCOLOR_XRGB(255, 255, 255));


		if (m_bConfirm)
		{
			woss.str((""));
			woss << "Are you sure?       No        Yes";
			//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 330, 550, 255, 255, 255);
			m_pBitmapFont.Print(woss.str().c_str(), 330, 550, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

			CGraphicsManager::GetInstance()->DrawArrow(455 + (m_nConfirmChoice * 55), 560, 255, 255, 255);
		}
		else
		{
			CGraphicsManager::GetInstance()->DrawArrow(350, 490 + (m_nMenuChoice * 20), 255, 255, 255);
		}
	}

}

struct SlotDataStruct
{
	int nMapID, nCurrPlayer, nPhaseCount, nCurrPhase;

	struct PlayerData
	{
		int nAIControlled;
		int nPlayerID;
		int nAP, nWood, nMetal;
		int nXP;
		int nNumUnits;


		struct ChampData
		{
			int nHealth;
		};

		ChampData tChampion;
	};

	PlayerData p1, p2;
};
void CSaveSlotState::ReadSlot(int nSlot)
{

	CBitmapFont m_pBitmapFont;
	std::ostringstream oss;
	oss << "Assets\\Scripts\\saveslot" << nSlot << ".xml";
	TiXmlDocument doc;

	SlotDataStruct s;

	int xOffset = (nSlot - 1) * 240;
	xOffset -= 40;
	if (doc.LoadFile(oss.str().c_str()))
	{
		TiXmlElement* pRoot = doc.RootElement();

		if (pRoot == nullptr)
			return;


		pRoot->QueryIntAttribute("mapID", &s.nMapID);
		pRoot->QueryIntAttribute("currPlayer", &s.nCurrPlayer);
		pRoot->QueryIntAttribute("phaseNumber", &s.nPhaseCount);
		pRoot->QueryIntAttribute("phase", &s.nCurrPhase);

		TiXmlElement* pPlayers = pRoot->FirstChildElement("Players");
		TiXmlElement* pPlayer = pPlayers->FirstChildElement("Player");

		for (int np = 0; np < 2; ++np)
		{
			SlotDataStruct::PlayerData pl;

			pPlayer->QueryIntAttribute("id", &pl.nPlayerID);
			pPlayer->QueryIntAttribute("ai", &pl.nAIControlled);
			pPlayer->QueryIntAttribute("wood", &pl.nWood);
			pPlayer->QueryIntAttribute("AP", &pl.nAP);
			pPlayer->QueryIntAttribute("metal", &pl.nMetal);

			TiXmlElement* pChampion = pPlayer->FirstChildElement("Champion");

			// TODO: load in spells here from ability manager
			pChampion->QueryIntAttribute("health", &pl.tChampion.nHealth);
			pChampion->QueryIntAttribute("xp", &pl.nXP);

			TiXmlElement* pUnits = pPlayer->FirstChildElement("Units");
			pUnits->QueryIntAttribute("numUnits", &pl.nNumUnits);
			pPlayer = pPlayer->NextSiblingElement("Player");

			if (np == 0)
				s.p1 = pl;
			else
				s.p2 = pl;
		}



		std::ostringstream woss;
		woss << "Slot " << nSlot;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 150 + xOffset , 80);
		m_pBitmapFont.Print(woss.str().c_str(), 150 + xOffset, 80, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Map ID: "<< s.nMapID;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 100);
		m_pBitmapFont.Print(woss.str().c_str(), 100 + xOffset, 100, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Current Player: " << s.nCurrPlayer + 1;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 120);
		m_pBitmapFont.Print(woss.str().c_str(), 100 + xOffset, 120, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Current Turn: " << (s.nPhaseCount / 4) + 1;
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 140);
		m_pBitmapFont.Print(woss.str().c_str(), 100 + xOffset, 140, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "Current Phase: ";
		if (s.nCurrPhase == 0)
			woss << "Movement";
		else
			woss << "Attack";
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 160);
		m_pBitmapFont.Print(woss.str().c_str(), 100 + xOffset, 160, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));

		woss << "Player 1 ";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 190);
		m_pBitmapFont.Print(woss.str().c_str(), 100 + xOffset, 190, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Wood " << s.p1.nWood;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 210);
		m_pBitmapFont.Print(woss.str().c_str(), 120 + xOffset, 210, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Metal " << s.p1.nMetal;
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 230);
		m_pBitmapFont.Print(woss.str().c_str(), 120 + xOffset, 230, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  AP " << s.p1.nAP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 250); // last one
		m_pBitmapFont.Print(woss.str().c_str(), 120 + xOffset, 250, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Units " << s.p1.nNumUnits;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 270);
		m_pBitmapFont.Print(woss.str().c_str(), 120 + xOffset, 270, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  XP " << s.p1.nXP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 290);
		m_pBitmapFont.Print(woss.str().c_str(), 120 + xOffset, 270, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));



		woss << "Player 2 ";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 210 + xOffset, 330); // + 40 from last
		m_pBitmapFont.Print(woss.str().c_str(), 210 + xOffset, 330, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Wood " << s.p2.nWood;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 350);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 350, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Metal " << s.p2.nMetal;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 370);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 360, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  AP " << s.p2.nAP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 390);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 390, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  Units " << s.p2.nNumUnits;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 410);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 410, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));
		woss << "  XP " << s.p2.nXP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 430);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 430, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str((""));


	}
	else
	{
		std::ostringstream woss;
		woss << "NO SAVE";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 330);
		m_pBitmapFont.Print(woss.str().c_str(), 170 + xOffset, 330, 0.3f, D3DCOLOR_XRGB(255, 255, 255));

	}

		int r,g,b;
		r=g=b=255;
	if (m_nHighlightedSlot == nSlot)
	{
		r = g = 255;
		b = 0;
		if (m_bShowMenu)
		{
			r = g = 0;
			b = 255;
		}
	}
	RECT outlineRect = { 90  + xOffset, 70, 230, 390 };
	CGraphicsManager::GetInstance()->DrawWireframeRect(outlineRect, r, g, b, false);

}