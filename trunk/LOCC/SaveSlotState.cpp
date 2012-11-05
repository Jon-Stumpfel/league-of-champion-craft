#include "StdAfx.h"
#include "SaveSlotState.h"
#include "StateStack.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "Hero.h"
#include "Player.h"
#include "GameplayState.h"
#include "SaveSlotState.h"
#include "StringTable.h"
#include "SoundManager.h"
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

	m_bGoodSlot[0] = false;
	m_bGoodSlot[1] = false;
	m_bGoodSlot[2] = false;
	m_bGoodSlot[3] = false;

	if (CStateStack::GetInstance()->FindState(CMainMenuState::GetInstance()))
	{
		m_bFromMainMenu = true;
	}
	else
		m_bFromMainMenu = false;

	if (m_bFromMainMenu)
		m_nMenuChoice = 1;
	else
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
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
				m_nHighlightedSlot++;
				if (m_nHighlightedSlot > 3)
					m_nHighlightedSlot = 1;
			}
			else
			{
				if (m_bConfirm)
				{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

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
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				m_nHighlightedSlot--;
				if (m_nHighlightedSlot < 1)
					m_nHighlightedSlot = 3;
			}
			else
			{
				if (m_bConfirm)
				{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

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
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				m_nMenuChoice--;
				if (m_bFromMainMenu)
				{
					if (m_nMenuChoice < 1)
						m_nMenuChoice = 2;
				}
				else
				{
					if (m_nMenuChoice < 0)
						m_nMenuChoice = 2;
				}
			}
		}
		break;
	case INPUT_DOWN:
		{
			if (m_bShowMenu)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				m_nMenuChoice++;
				if (m_bFromMainMenu)
				{
					if (m_nMenuChoice > 2)
						m_nMenuChoice = 1;
				}
				else
				{
					if (m_nMenuChoice > 2)
						m_nMenuChoice = 0;
				}
			}
		}
		break;
	case INPUT_ACCEPT:
		{
			if (!m_bShowMenu)
			{
				CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
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
						case 1: // Load
							{
								if (m_bGoodSlot[m_nHighlightedSlot])
								{
									CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
									CGameManager::GetInstance()->LoadSave(m_nHighlightedSlot);
									CStateStack::GetInstance()->Switch(CGameplayState::GetInstance());
									m_nConfirmChoice = 0;
									return;
								}
							}
							break;
						case 0: // Save!
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("savegame")), false, false);
								CGameManager::GetInstance()->SaveGame(m_nHighlightedSlot);
								m_nConfirmChoice = 0;
								m_bConfirm = false;
								return;
							}
							break;
						case 2: // Delete!
							{
								CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("deletesave")), false, false);
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
						CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

						m_bConfirm = false;
						break;
					}
				}
				else
				{
					m_bConfirm = true;
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				}
			}
		}
		break;
	case INPUT_CANCEL:
		{
			if (m_bShowMenu)
			{
				if (m_bConfirm)
				{
					CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);
					m_bConfirm = false;
					break;
				}
				m_bShowMenu = false;
						CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

				break;
			}
							CSoundManager::GetInstance()->Play(CSoundManager::GetInstance()->GetID(_T("click")), false, false);

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
	CSGD_Direct3D::GetInstance()->Clear(50, 50, 50);

	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("warriorblue")),0,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("warriorred")),290,90,0.5f,0.5f,0,0,0,0,D3DXCOLOR(255,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("mainmenubg")),15,-5,0.7f,0.7f,0,0,0,0,D3DXCOLOR(255,255,255,255));



	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR shaded = D3DCOLOR_XRGB(120, 120, 120);
	if (m_nHighlightedSlot == 1)
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 0, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, white);

	else
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 0, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, shaded);

	if (m_nHighlightedSlot == 2)
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 260, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, white);

	else
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 260, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, shaded);
	if (m_nHighlightedSlot == 3)
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 520, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, white);

	else
	CSGD_TextureManager::GetInstance()->Draw(CGraphicsManager::GetInstance()->GetID(_T("scrollvert")), 520, 0, 0.55f, 1.0f,
		(RECT*)0, 0.0f, 0.0f, 0.0f, shaded);

	CBitmapFont m_pBitmapFont;

	ReadSlot(1);
	ReadSlot(2);
	ReadSlot(3);
	if (m_bShowMenu)
	{
		m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Load from slot").c_str(), 330, 520, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255);
		if (m_bFromMainMenu)
		{
			color = D3DCOLOR_XRGB(120, 120, 120);
		}
		m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Save to slot").c_str(), 330, 500, 0.4f, color);
		m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Delete slot").c_str(), 330, 540, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
		if (m_bConfirm)
		{
			m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Are you sure?").c_str(), 250, 570, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
			m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("No").c_str(), 475, 570, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
			m_pBitmapFont.Print(StringTable::GetInstance()->GetString
			("Yes").c_str(), 550, 570, 0.4f, D3DCOLOR_XRGB(255, 255, 255));
			CGraphicsManager::GetInstance()->DrawArrow(455 + (m_nConfirmChoice * 75), 580, 255, 255, 255);
		}
		else
		{
			CGraphicsManager::GetInstance()->DrawArrow(310, 510 + (m_nMenuChoice * 20), 255, 255, 255);
		}
	}
	
	m_pBitmapFont.Print("Press cancel to return...", 20, 510, 0.28f, D3DCOLOR_XRGB(255, 255, 255), 250);
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

	D3DCOLOR drawColor = D3DCOLOR_XRGB(255, 255, 255);
	if (m_nHighlightedSlot != nSlot)
	{
		drawColor = D3DCOLOR_XRGB(120, 120, 120);

	}


	int xOffset = (nSlot - 1) * 260;
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
		woss << StringTable::GetInstance()->GetString("Slot ") << nSlot;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 150 + xOffset , 80);
		m_pBitmapFont.Print(woss.str().c_str(), 140 + xOffset, 80, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("Map ID: ")<< s.nMapID;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 100);
		m_pBitmapFont.Print(woss.str().c_str(), 70 + xOffset, 100, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("Current Player: ") << s.nCurrPlayer + 1;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 120);
		m_pBitmapFont.Print(woss.str().c_str(), 70 + xOffset, 120, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("Current Turn: ") << (s.nPhaseCount / 4) + 1;
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 140);
		m_pBitmapFont.Print(woss.str().c_str(), 70 + xOffset, 140, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("Current Phase: ");
		if (s.nCurrPhase == 0)
			woss << StringTable::GetInstance()->GetString("Movement");
		else
			woss << StringTable::GetInstance()->GetString("Attack");
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 160);
		m_pBitmapFont.Print(woss.str().c_str(), 70 + xOffset, 160, 0.3f, drawColor,150);

		woss.str((""));

		woss << StringTable::GetInstance()->GetString("Player ") << "1 ";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 100 + xOffset, 190);
		m_pBitmapFont.Print(woss.str().c_str(), 70 + xOffset, 210, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Wood ") << s.p1.nWood;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 210);
		m_pBitmapFont.Print(woss.str().c_str(), 90 + xOffset, 230, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Metal ") << s.p1.nMetal;
	//	CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 230);
		m_pBitmapFont.Print(woss.str().c_str(), 90 + xOffset, 250, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  AP ") << s.p1.nAP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 250); // last one
		m_pBitmapFont.Print(woss.str().c_str(), 90 + xOffset, 270, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Units ") << s.p1.nNumUnits;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 270);
		m_pBitmapFont.Print(woss.str().c_str(), 90 + xOffset, 290, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  XP ") << s.p1.nXP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 120 + xOffset, 290);
		m_pBitmapFont.Print(woss.str().c_str(), 90 + xOffset, 310, 0.3f, drawColor);

		woss.str((""));



		woss << StringTable::GetInstance()->GetString("Player ") <<"2 ";
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 210 + xOffset, 330); // + 40 from last
		m_pBitmapFont.Print(woss.str().c_str(), 200 + xOffset, 350, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Wood ") << s.p2.nWood;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 350);
		m_pBitmapFont.Print(woss.str().c_str(), 160 + xOffset, 370, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Metal ") << s.p2.nMetal;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 370);
		m_pBitmapFont.Print(woss.str().c_str(), 160 + xOffset, 390, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  AP ") << s.p2.nAP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 390);
		m_pBitmapFont.Print(woss.str().c_str(), 160 + xOffset, 410, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  Units ") << s.p2.nNumUnits;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 410);
		m_pBitmapFont.Print(woss.str().c_str(), 160 + xOffset, 430, 0.3f, drawColor);

		woss.str((""));
		woss << StringTable::GetInstance()->GetString("  XP ") << s.p2.nXP;
		//CSGD_Direct3D::GetInstance()->DrawTextW((TCHAR*)woss.str().c_str(), 170 + xOffset, 430);
		m_pBitmapFont.Print(woss.str().c_str(), 160 + xOffset, 450, 0.3f, drawColor);

		woss.str((""));

		m_bGoodSlot[nSlot] = true;

	}
	else
	{
		std::ostringstream woss;
		woss << StringTable::GetInstance()->GetString("NO SAVE");
		m_pBitmapFont.Print(woss.str().c_str(), 140 + xOffset, 330, 0.3f, drawColor);
		m_bGoodSlot[nSlot] = false;

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
	//RECT outlineRect = { 90  + xOffset, 70, 230, 390 };
//	CGraphicsManager::GetInstance()->DrawWireframeRect(outlineRect, r, g, b, false);

}