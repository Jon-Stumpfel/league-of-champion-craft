#include "StdAfx.h"
#include "GameManager.h"
#include "GameplayState.h"
#include "ObjectManager.h"
#include "AIManager.h"
#include "SpawnUnitMessage.h"
#include "TileManager.h"
#include "ScriptManager.h"
#include "AbilityManager.h"
#include "MessageSystem.h"
#include "DeSpawnUnitMessage.h"
#include "FloatingText.h"
#include "AddResourceMessage.h"
#include "Tile.h"
#include "Unit.h"
#include "Hero.h"
#include "Player.h"
#include "StateStack.h"
#include "AttackPhaseTransState.h"
#include "MovetPhaseTransState.h"

CGameManager* CGameManager::s_Instance = nullptr;
int CGameManager::m_nUniqueUnitID = 0;
bool IntToBool(int n)
{
	return (n != 0);
}
CGameManager::CGameManager(void)
{
	m_nNewPlayerID = 0;
	m_nPhaseCount = 0;
	m_pCurrentPlayer = nullptr;
	m_pNextPlayer = nullptr;
}


CGameManager::~CGameManager(void)
{

}

void CGameManager::NextPhase(void)
{
	int numcols= CTileManager::GetInstance()->GetNumColumns();
	int numrows= CTileManager::GetInstance()->GetNumRows();

	m_nPhaseCount++;
	if (m_nCurrentPhase == GP_MOVE)
	{
		CAIManager::GetInstance()->BeginAttack();
		m_nCurrentPhase = GP_ATTACK;
		//Attack!!!(Attack Phase Transition)-DG
		CStateStack::GetInstance()->Push(CAttackPhaseTransState::GetInstance());
		//Chilling the cooldown: this function does the cooldowndown each turn  -DG
		CHero* Hero =  dynamic_cast <CHero*>(GetChampion(m_pCurrentPlayer->GetPlayerID()));
		Hero->ChillCooldown();
	}
	else if (m_nCurrentPhase == GP_ATTACK)
	{
		CPlayer* pTemp = m_pCurrentPlayer;
		m_nCurrentPhase = GP_MOVE;
		m_pCurrentPlayer = m_pNextPlayer;
		m_pNextPlayer = pTemp;

		//Look At That, TileManager Takeing car of business! this added resoruces based on the tiles -DG
		CTileManager::GetInstance()->EvaluateResources(m_pCurrentPlayer->GetPlayerID());
		
		CGameplayState::GetInstance()->ClearSelections();
		if (GetChampion(m_pCurrentPlayer->GetPlayerID()) != nullptr)
		{
			CGameplayState::GetInstance()->SnapToPosition(GetChampion(m_pCurrentPlayer->GetPlayerID())->GetPos());
		}
		m_pCurrentPlayer->SetAP(nStartingAP);
		CAIManager::GetInstance()->BeginMovement();

		for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
		{
			if (m_vUnits[i]->GetPlayerID() == m_pCurrentPlayer->GetPlayerID())
			{
				m_vUnits[i]->SetTilesMoved(0);
				m_vUnits[i]->SetHasAttacked(false);
				m_vUnits[i]->UpdateEffects();
			}
		}
		//RAISE THE CASTLE WALLS!!!(Do the movement transition)-DG
		CStateStack::GetInstance()->Push(CMovetPhaseTransState::GetInstance());	
	}
}

// Get the player's champion unit. Searches through the unit list to find a unit that matches
// the criteria: Owned by nPlayerID and is a UT_HERO. We can assume there will only ever be 1 hero.
CUnit* CGameManager::GetChampion(int nPlayerID)
{
	for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
	{
		if (m_vUnits[i]->GetPlayerID() != nPlayerID)
			continue;
		if (m_vUnits[i]->GetType() == UT_HERO)
			return m_vUnits[i];
	}
	return nullptr;
}
CGameManager* CGameManager::GetInstance(void)
{
	if (s_Instance == nullptr)
		s_Instance = new CGameManager();
	return s_Instance;
}


CPlayer* CGameManager::GetCurrentPlayer(void)
{
	return m_pCurrentPlayer;
}
void CGameManager::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		s_Instance->ShutDown();
		delete s_Instance;
	}
	s_Instance = nullptr;
}
void CGameManager::ShutDown(void)
{
	while (m_vPlayers.size() != 0)
	{
		delete m_vPlayers.back();
		m_vPlayers.pop_back();
	}

	while (m_vUnits.size() != 0)
	{
		m_vUnits.back()->Release();
		m_vUnits.pop_back();
	}
}
CPlayer* CGameManager::CreatePlayer(bool bAIControlled)
{
	CPlayer* pPlayer = new CPlayer(m_nNewPlayerID++);
	// TODO if bAIControlled add cplayer to list of AI controlled stuff
	if (bAIControlled)
	{
		pPlayer->SetAI(true);
		 CAIManager::GetInstance()->PushPlayerID(pPlayer->GetPlayerID());
	}
	else
		pPlayer->SetAI(false);

	if (m_vPlayers.size() == 0)
	{
		m_pCurrentPlayer = pPlayer;
	}
	else
		m_pNextPlayer = pPlayer;
	m_vPlayers.push_back(pPlayer);
	return pPlayer;
}

CPlayer* CGameManager::GetPlayer(int nPlayerID)
{
	for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
	{
		if (m_vPlayers[i]->GetPlayerID() == nPlayerID)
		{
			return m_vPlayers[i];
			break;
		}

	}
	return nullptr;
}

int CGameManager::GetLevel(void)
{
	return -1;
}

void CGameManager::LoadLevel(std::string sFileName)
{
	std::ostringstream oss;
	oss << "Assets\\Scripts\\" << sFileName << ".xml";
	m_vScriptSpawns.clear();
	CScriptManager::GetInstance()->LoadScript(oss.str(), ST_LEVEL);
}

void CGameManager::LoadUnitsFromScript(void)
{
	for (decltype(m_vScriptSpawns.size()) i = 0; i < m_vScriptSpawns.size(); ++i)
	{
		ScriptedSpawn s = m_vScriptSpawns[i];
		if (GetCurrentTurn() == s.first)
		{
			CSpawnUnitMessage* pMSG = new CSpawnUnitMessage(Vec2D(s.second.sPos), s.second.nPlayerID, s.second.eType, s.second.nFacing);
			CMessageSystem::GetInstance()->SendMessageW(pMSG);
			m_vScriptSpawns.erase(m_vScriptSpawns.begin() + i);
			--i;
		}
	}

	CMessageSystem::GetInstance()->ProcessMessages();

}

void CGameManager::LoadMap(int nLevelNum)
{
	CTileManager* pTM=CTileManager::GetInstance();
	std::ostringstream oss;
	oss << "Assets\\Tiles\\TestMap" << nLevelNum << ".xml";
	string filename= "Assets\\Tiles\\TestMap2.xml";
	pTM->LoadSave(oss.str());
	m_nCurrentLevel = nLevelNum;
	// Attempting to load fake level 1 script
}

void CGameManager::SaveGame(int nSlot)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "");

	doc.LinkEndChild(pDec);

	TiXmlElement* pRoot = new TiXmlElement("Map");
	doc.LinkEndChild(pRoot);

	pRoot->SetAttribute("mapID", m_nCurrentLevel);
	pRoot->SetAttribute("phaseNumber", m_nPhaseCount);
	pRoot->SetAttribute("phase", m_nCurrentPhase);
	pRoot->SetAttribute("currPlayer", m_pCurrentPlayer->GetPlayerID());

	TiXmlElement* pMapMods = new TiXmlElement("MapModifications");
	pMapMods->SetAttribute("numModifications", m_vMapMods.size());
	pRoot->LinkEndChild(pMapMods);


	for (unsigned int i = 0; i < m_vMapMods.size(); ++i)
	{
		TiXmlElement* pMapMod = new TiXmlElement("MapModification");
		pMapMod->SetAttribute("modType", m_vMapMods[i].modType);
		pMapMod->SetAttribute("modPosX", m_vMapMods[i].posX);
		pMapMod->SetAttribute("modPosY", m_vMapMods[i].posY);
		pMapMods->LinkEndChild(pMapMod);
	}

	TiXmlElement* pPlayers = new TiXmlElement("Players");
	pRoot->LinkEndChild(pPlayers);

	for (int i = 0; i < 2; ++i)
	{
		TiXmlElement* pPlayer = new TiXmlElement("Player");
		pPlayers->LinkEndChild(pPlayer);
		pPlayer->SetAttribute("id", m_vPlayers[i]->GetPlayerID());
		pPlayer->SetAttribute("ai", (int)m_vPlayers[i]->GetAI());
		pPlayer->SetAttribute("AP", m_vPlayers[i]->GetAP());
		pPlayer->SetAttribute("wood", m_vPlayers[i]->GetWood());
		pPlayer->SetAttribute("metal", m_vPlayers[i]->GetMetal());

		// Game Stats!

		TiXmlElement* pStats = new TiXmlElement("Stats");
		pStats->SetAttribute("numStats", 17);

		TiXmlElement* pChampionDmgDone = new TiXmlElement("ChampionDamageDone");
		pChampionDmgDone->SetAttribute("value", m_vPlayers[i]->GetStats()->nChampionDamageDone);
		pStats->LinkEndChild(pChampionDmgDone);

		TiXmlElement* pChampionHealingDone = new TiXmlElement("ChampionHealingDone");
		pChampionHealingDone->SetAttribute("value", m_vPlayers[i]->GetStats()->nChampionHealingDone);
		pStats->LinkEndChild(pChampionHealingDone);

		TiXmlElement* pSwordsmanCreated = new TiXmlElement("SwordsmanCreated");
		pSwordsmanCreated->SetAttribute("value", m_vPlayers[i]->GetStats()->nSwordsmanCreated);
		pStats->LinkEndChild(pSwordsmanCreated);

		TiXmlElement* pArcherCreated = new TiXmlElement("ArcherCreated");
		pArcherCreated->SetAttribute("value", m_vPlayers[i]->GetStats()->nArcherCreated);
		pStats->LinkEndChild(pArcherCreated);

		TiXmlElement* pCalvaryCreated = new TiXmlElement("CalvaryCreated");
		pCalvaryCreated->SetAttribute("value", m_vPlayers[i]->GetStats()->nCalvaryCreated);
		pStats->LinkEndChild(pCalvaryCreated);

		TiXmlElement* pSwordsmanDmgDone = new TiXmlElement("SwordsmanDamageDone");
		pSwordsmanDmgDone->SetAttribute("value", m_vPlayers[i]->GetStats()->nSwordsmanDamageDone);
		pStats->LinkEndChild(pSwordsmanDmgDone);

		TiXmlElement* pArcherDmgDone = new TiXmlElement("ArcherDamageDone");
		pArcherDmgDone->SetAttribute("value", m_vPlayers[i]->GetStats()->nArcherDamageDone);
		pStats->LinkEndChild(pArcherDmgDone);

		TiXmlElement* pCalvaryDmgDone = new TiXmlElement("CalvaryDamageDone");
		pCalvaryDmgDone->SetAttribute("value", m_vPlayers[i]->GetStats()->nCalvaryDamageDone);
		pStats->LinkEndChild(pCalvaryDmgDone);

		TiXmlElement* pSwordsmanKilled = new TiXmlElement("SwordsmanKilled");
		pSwordsmanKilled->SetAttribute("value", m_vPlayers[i]->GetStats()->nSwordsmanKilled);
		pStats->LinkEndChild(pSwordsmanKilled);

		TiXmlElement* pArcherKilled = new TiXmlElement("ArcherKilled");
		pArcherKilled->SetAttribute("value", m_vPlayers[i]->GetStats()->nArcherKilled);
		pStats->LinkEndChild(pArcherKilled);

		TiXmlElement* pCalvaryKilled = new TiXmlElement("CalvaryKilled");
		pCalvaryKilled->SetAttribute("value", m_vPlayers[i]->GetStats()->nCavalryKilled);
		pStats->LinkEndChild(pCalvaryKilled);

		TiXmlElement* pWoodEarned = new TiXmlElement("WoodEarned");
		pWoodEarned->SetAttribute("value", m_vPlayers[i]->GetStats()->nPlayerWoodEarned);
		pStats->LinkEndChild(pWoodEarned);

		TiXmlElement* pMetalEarned = new TiXmlElement("MetalEarned");
		pMetalEarned->SetAttribute("value", m_vPlayers[i]->GetStats()->nPlayerMetalEarned);
		pStats->LinkEndChild(pMetalEarned);

		TiXmlElement* pWoodSpent = new TiXmlElement("WoodSpent");
		pWoodSpent->SetAttribute("value", m_vPlayers[i]->GetStats()->nPlayerWoodSpent);
		pStats->LinkEndChild(pWoodSpent);

		TiXmlElement* pMetalSpent = new TiXmlElement("MetalSpent");
		pMetalSpent->SetAttribute("value", m_vPlayers[i]->GetStats()->nPlayerMetalSpent);
		pStats->LinkEndChild(pMetalSpent);

		TiXmlElement* pAPSpent = new TiXmlElement("APSpent");
		pAPSpent->SetAttribute("value", m_vPlayers[i]->GetStats()->nPlayerAPSpent);
		pStats->LinkEndChild(pAPSpent);

		pPlayer->LinkEndChild(pStats);


		TiXmlElement* pChampion = new TiXmlElement("Champion");
		CHero* pHero = dynamic_cast<CHero*>(GetChampion(m_vPlayers[i]->GetPlayerID()));
		if (pHero == nullptr)
		{
			// Why are you here?
			MessageBoxA(0, "How did you get here? Why are you saving when hero is dead? Go away. Don't save after you won",
				"ERROR:", MB_OK);
			continue;
		}
		if (pHero->GetNumWaypoints() > 0)
		{
			pChampion->SetAttribute("posX", pHero->GetLastWaypoint().nPosX);
			pChampion->SetAttribute("posY", pHero->GetLastWaypoint().nPosY);
		}
		else
		{
			pChampion->SetAttribute("posX", pHero->GetPos().nPosX);
			pChampion->SetAttribute("posY", pHero->GetPos().nPosY);
		}

		pChampion->SetAttribute("health", pHero->GetHP());
		pChampion->SetAttribute("xp", m_vPlayers[i]->GetExp());
		pChampion->SetAttribute("facing", pHero->GetFacing());
		pChampion->SetAttribute("tilesMoved", pHero->GetTilesMoved());
		pChampion->SetAttribute("hasAttacked", (int)pHero->GetHasAttacked());
		// TODO: setup spell saving here

		TiXmlElement* pSpells = new TiXmlElement("Spells");
		pSpells->SetAttribute("numSpells", pHero->GetNumSpells());
		pChampion->LinkEndChild(pSpells);

		for (unsigned int n = 0; n < pHero->GetNumSpells(); ++n)
		{
			TiXmlElement* pSpell = new TiXmlElement("Spell");
			pSpell->SetAttribute("sType", pHero->GetSpell(n)->GetType());
			pSpells->LinkEndChild(pSpell);
		}
		TiXmlElement* pEffects = new TiXmlElement("Effects");
		pChampion->LinkEndChild(pEffects);
		pEffects->SetAttribute("numEffects", pHero->GetNumEffects());
		for (int x = 0; x < pHero->GetNumEffects(); ++x)
		{
			TiXmlElement* pEffect = new TiXmlElement("Effect");
			pEffect->SetAttribute("ability", pHero->GetEffect(i)->GetType());
			pEffects->LinkEndChild(pEffect);
		}

		pPlayer->LinkEndChild(pChampion);

		// Lets save the units!
		TiXmlElement* pUnits = new TiXmlElement("Units");
		pPlayer->LinkEndChild(pUnits);
		int nNumUnits = 0;

		for (decltype(m_vUnits.size()) j = 0; j < m_vUnits.size(); ++j)
		{
			// this is our unit, lets save it!
			if (m_vUnits[j]->GetPlayerID() == m_vPlayers[i]->GetPlayerID() && m_vUnits[j]->GetType() != UT_HERO)
			{
				TiXmlElement* pUnit = new TiXmlElement("Unit");
				CUnit* puni = m_vUnits[j];
				nNumUnits++;
				if (puni->GetNumWaypoints() > 0)
				{
					pUnit->SetAttribute("posX", puni->GetLastWaypoint().nPosX);
					pUnit->SetAttribute("posY", puni->GetLastWaypoint().nPosY);
				}
				else
				{
					pUnit->SetAttribute("posX", puni->GetPos().nPosX);
					pUnit->SetAttribute("posY", puni->GetPos().nPosY);
				}
				pUnit->SetAttribute("unitType", (int)puni->GetType());
				pUnit->SetAttribute("health", puni->GetHP());
				pUnit->SetAttribute("facing", puni->GetFacing());
				pUnit->SetAttribute("tilesMoved", puni->GetTilesMoved());
				pUnit->SetAttribute("hasAttacked", (int)puni->GetHasAttacked());

				// Effects/debuffs on the unit
				TiXmlElement* pEffects = new TiXmlElement("Effects");
				pUnit->LinkEndChild(pEffects);
				pEffects->SetAttribute("numEffects", puni->GetNumEffects());
				for (int i = 0; i < puni->GetNumEffects(); ++i)
				{
					TiXmlElement* pEffect = new TiXmlElement("Effect");
					pEffect->SetAttribute("ability", puni->GetEffect(i)->GetType());
					pEffects->LinkEndChild(pEffect);
				}

				pUnits->LinkEndChild(pUnit);
			}
		}

		pUnits->SetAttribute("numUnits", nNumUnits);
	}

	std::ostringstream oss;
	oss << "Assets\\Scripts\\saveslot" << nSlot << ".xml";

	doc.SaveFile(oss.str().c_str());

}
void CGameManager::LoadSave(int nSlot)
{
	Reset();
	std::ostringstream oss;
	oss << "Assets\\Scripts\\saveslot" << nSlot << ".xml";

	TiXmlDocument doc;
	if (doc.LoadFile(oss.str().c_str()))
	{
		TiXmlElement* pRoot = doc.RootElement();


		if (pRoot == nullptr)
			return;

		int nMapID, nCurrPlayer, nPhaseCount, nCurrPhase;
		pRoot->QueryIntAttribute("mapID", &nMapID);
		pRoot->QueryIntAttribute("currPlayer", &nCurrPlayer);
		pRoot->QueryIntAttribute("phaseNumber", &nPhaseCount);
		pRoot->QueryIntAttribute("phase", &nCurrPhase);


		LoadMap(nMapID);

		// Map modifcations! Weeeeeeeee
		int nNumMapModifications;
		TiXmlElement* pMapMods = pRoot->FirstChildElement("MapModifications");
		pMapMods->QueryIntAttribute("numModifications", &nNumMapModifications);
		TiXmlElement* pMapModification = pMapMods->FirstChildElement("MapModification");
		for (int i = 0; i < nNumMapModifications; ++i)
		{
			MapModification mod;
			int nType;
			pMapModification->QueryIntAttribute("modType", &nType);
			mod.modType = (SPELL_TYPE)nType;
			pMapModification->QueryIntAttribute("modPosX", &mod.posX);
			pMapModification->QueryIntAttribute("modPosY", &mod.posY);

			switch (mod.modType)
			{
			case SP_RAISEMOUNTAIN:
				{
					CTile* selectedTile = CTileManager::GetInstance()->GetTile(mod.posX, mod.posY);
					if( selectedTile != nullptr )
					{	
						if (selectedTile->GetTileType() != TT_FARM && selectedTile->GetTileType() != TT_MILL &&
							selectedTile->GetTileType() != TT_MINE)
						{
							selectedTile->SetTileType(TT_MOUNTAINS);
							selectedTile->SetIfPassable(false);
							CGameManager::GetInstance()->AddModification(mod);
						}
					}
				}
				break;
			case SP_DESTROYFOREST:
				{
					CTile* selectedTile = CTileManager::GetInstance()->GetTile(mod.posX, mod.posY);
					if( selectedTile != nullptr )
					{	
						if (selectedTile->GetTileType() == TT_FOREST)
						{
							selectedTile->SetTileType(TT_PLAINS);
							CGameManager::GetInstance()->AddModification(mod);
						}
					}
				}
				break;
			}

			pMapModification = pMapModification->NextSiblingElement("MapModification");

		}


		TiXmlElement* pPlayers = pRoot->FirstChildElement("Players");
		TiXmlElement* pPlayer = pPlayers->FirstChildElement("Player");

		for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
		{
	
			delete m_vPlayers[i];
		}
		m_vPlayers.clear();
		m_nNewPlayerID = 0;
		for (int np = 0; np < 2; ++np)
		{
			int nAIControlled;
			int nPlayerID;
			int nAP, nWood, nMetal;
			pPlayer->QueryIntAttribute("id", &nPlayerID);
			pPlayer->QueryIntAttribute("ai", &nAIControlled);
			pPlayer->QueryIntAttribute("wood", &nWood);
			pPlayer->QueryIntAttribute("AP", &nAP);
			pPlayer->QueryIntAttribute("metal", &nMetal);
			CPlayer* pplay = CreatePlayer(IntToBool(nAIControlled));

			pplay->SetWood(nWood);
			pplay->SetAP(nAP);
			pplay->SetMetal(nMetal);


			// Load stats!
			TiXmlElement* pStats = pPlayer->FirstChildElement("Stats");

			TiXmlElement* pStat = pStats->FirstChildElement("ChampionDamageDone");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nChampionDamageDone);
			pStat = pStats->FirstChildElement("ChampionHealingDone");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nChampionHealingDone);
			pStat = pStats->FirstChildElement("SwordsmanCreated");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nSwordsmanCreated);
			pStat = pStats->FirstChildElement("ArcherCreated");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nArcherCreated);
			pStat = pStats->FirstChildElement("CalvaryCreated");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nCalvaryCreated);
			pStat = pStats->FirstChildElement("SwordsmanDamageDone");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nSwordsmanDamageDone);
			pStat = pStats->FirstChildElement("ArcherDamageDone");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nArcherDamageDone);
			pStat = pStats->FirstChildElement("CalvaryDamageDone");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nCalvaryDamageDone);
			pStat = pStats->FirstChildElement("SwordsmanKilled");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nSwordsmanKilled);
			pStat = pStats->FirstChildElement("ArcherKilled");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nArcherKilled);
			pStat = pStats->FirstChildElement("CalvaryKilled");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nCavalryKilled);
			pStat = pStats->FirstChildElement("WoodEarned");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nPlayerWoodEarned);
			pStat = pStats->FirstChildElement("WoodSpent");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nPlayerWoodSpent);
			pStat = pStats->FirstChildElement("MetalEarned");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nPlayerMetalEarned);
			pStat = pStats->FirstChildElement("MetalSpent");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nPlayerMetalSpent);
			pStat = pStats->FirstChildElement("APSpent");
			pStat->QueryIntAttribute("value", &pplay->GetStats()->nPlayerAPSpent);



			TiXmlElement* pChampion = pPlayer->FirstChildElement("Champion");

			int nPosX, nPosY, nHealth, nXP, nFacing, nTilesMoved, nHasAttacked;
			// TODO: load in spells here from ability manager
			pChampion->QueryIntAttribute("posX", &nPosX);
			pChampion->QueryIntAttribute("posY", &nPosY);
			pChampion->QueryIntAttribute("health", &nHealth);
			pChampion->QueryIntAttribute("xp", &nXP);
			pChampion->QueryIntAttribute("facing", &nFacing);
			pChampion->QueryIntAttribute("tilesMoved", &nTilesMoved);
			pChampion->QueryIntAttribute("hasAttacked", &nHasAttacked);

			pplay->SetExp(nXP);

			int nNumSpells;
			TiXmlElement* pSpells = pChampion->FirstChildElement("Spells");
			pSpells->QueryIntAttribute("numSpells", &nNumSpells);
			std::vector<SPELL_TYPE> spells;
			TiXmlElement* pSpell = pSpells->FirstChildElement("Spell");

			for (int i = 0; i < nNumSpells; ++i)
			{
				int nType;
				pSpell->QueryIntAttribute("sType", &nType);
				spells.push_back((SPELL_TYPE)nType);
				pSpell = pSpell->NextSiblingElement("Spell");
			}

			int nNumEffects;
			TiXmlElement* pEffects = pChampion->FirstChildElement("Effects");
			pEffects->QueryIntAttribute("numEffects", &nNumEffects);
			std::vector<SPELL_TYPE> effects;
			TiXmlElement* pEffect = pEffects->FirstChildElement("Effect");
			for (int i = 0; i < nNumEffects; ++i)
			{
				int nType;
				pEffect->QueryIntAttribute("ability", &nType);
				effects.push_back((SPELL_TYPE)nType);
				pEffect = pEffect->NextSiblingElement("Effect");
			}

			CSpawnUnitMessage* pMsg = new CSpawnUnitMessage(spells, effects, Vec2D(nPosX, nPosY), nPlayerID, UT_HERO, nFacing, true, 
				nHealth, nTilesMoved, IntToBool(nAIControlled));
			CMessageSystem::GetInstance()->SendMessageW(pMsg);


			int nNumUnits;
			TiXmlElement* pUnits = pPlayer->FirstChildElement("Units");
			pUnits->QueryIntAttribute("numUnits", &nNumUnits);

			TiXmlElement* pUnit = pUnits->FirstChildElement("Unit");
			for (int i = 0; i < nNumUnits; ++i)
			{
				int nUnitPosX, nUnitPosY, nUnitType, nUnitHealth, nUnitFacing, nUnitTilesMoved, nUnitHasAttacked;
				pUnit->QueryIntAttribute("posX", &nUnitPosX);
				pUnit->QueryIntAttribute("posY", &nUnitPosY);
				pUnit->QueryIntAttribute("unitType", &nUnitType);
				pUnit->QueryIntAttribute("health", &nUnitHealth);
				pUnit->QueryIntAttribute("facing", &nUnitFacing);
				pUnit->QueryIntAttribute("tilesMoved", &nUnitTilesMoved);
				pUnit->QueryIntAttribute("hasAttacked", &nUnitHasAttacked);
				std::vector<SPELL_TYPE> spells;
				int nNumEffects;
				TiXmlElement* pEffects = pUnit->FirstChildElement("Effects");
				pEffects->QueryIntAttribute("numEffects", &nNumEffects);
				std::vector<SPELL_TYPE> effects;
				TiXmlElement* pEffect = pEffects->FirstChildElement("Effect");
				for (int i = 0; i < nNumEffects; ++i)
				{
					int nType;
					pEffect->QueryIntAttribute("ability", &nType);
					effects.push_back((SPELL_TYPE)nType);
					pEffect = pEffect->NextSiblingElement("Effect");
				}
				CSpawnUnitMessage* pUnitMsg = 
					new CSpawnUnitMessage(spells, effects, Vec2D(nUnitPosX, nUnitPosY), nPlayerID, (UNIT_TYPE)nUnitType, nUnitFacing, true, nUnitHealth,
						nUnitTilesMoved,IntToBool(nAIControlled) );
				CMessageSystem::GetInstance()->SendMessageW(pUnitMsg);

				pUnit = pUnit->NextSiblingElement("Unit");
			}
			pPlayer = pPlayer->NextSiblingElement("Player");
		}


		SetCurrentPlayer(nCurrPlayer);
		if (nCurrPlayer == 0)
			SetNextPlayer(1);
		else
			SetNextPlayer(0);
		SetPhaseCount(nPhaseCount);
		SetCurrentPhase((GAME_PHASE)nCurrPhase);
		CMessageSystem::GetInstance()->ProcessMessages();
	}
}

void CGameManager::AddUnit(CUnit* pUnit)
{
	m_vUnits.push_back(pUnit);
	pUnit->AddRef();
}
void CGameManager::RemoveUnit(CUnit* pUnit)
{
	std::vector<CUnit*>::iterator iter = m_vUnits.begin();

	while (iter != m_vUnits.end())
	{
		if ((*iter) == pUnit)
		{
			m_vUnits.erase(iter);
			pUnit->Release();
			break;
		}
		else
			++iter;
	}

}

// Reset the game and load whatever needs to be loaded
void CGameManager::Reset(void)
{
	for (decltype(m_vUnits.size()) i = 0; i < m_vUnits.size(); ++i)
	{
		CDespawnUnitMessage* pMsg = new CDespawnUnitMessage(m_vUnits[i]);
		CMessageSystem::GetInstance()->SendMessageW(pMsg);
	}
	//m_vUnits.clear();
	CMessageSystem::GetInstance()->ProcessMessages();

	for (decltype(m_vPlayers.size()) i = 0; i < m_vPlayers.size(); ++i)
	{

		delete m_vPlayers[i];
	}

	m_vPlayers.clear();
	m_nNewPlayerID = 0;
	m_vScriptSpawns.clear();

	CreatePlayer(false); // player 1
	CreatePlayer(true);

	CTileManager::GetInstance()->ShutDown();

}
void CGameManager::NewGame(string levelstring, int mapint)
{
	LoadLevel(levelstring);

	Reset();

	LoadLevel(levelstring);

	LoadMap(mapint);
	
	m_nPhaseCount = 0;
	// Player 1 and his units
	m_nNewPlayerID = 0;

	LoadUnitsFromScript();

	CAIManager::GetInstance()->BeginMovement();


	m_nCurrentPhase = GP_MOVE;
}

int CGameManager::GetCurrentTurn(void)
{
	int nTurn = m_nPhaseCount / 4;

	return nTurn +1;
}
void CGameManager::Update(float fElapsedTime)
{
	LoadUnitsFromScript();

	int x = m_vUnits.size();

}
void CGameManager::SetNextPlayer(int nPlayerID)
{
	m_pNextPlayer = m_vPlayers[nPlayerID];
}

CUnit* CGameManager::FindUnit(int posX, int posY)
{
	std::vector<CUnit*>::iterator iter = m_vUnits.begin();

	while (iter != m_vUnits.end())
	{
		if ((*iter)->GetPos() == Vec2D(posX, posY))
		{
			return (*iter);
			break;
		}
		++iter;
	}
	return nullptr;
}
CUnit* CGameManager::FindUnit(Vec2D pos)
{
	return FindUnit(pos.nPosX, pos.nPosY);
}

// This is the MessageSystem MessageProc. Message handling is done here
void CGameManager::MessageProc(IMessage* pMsg)
{
	CGameManager* pThis = CGameManager::GetInstance();
	// MESSAGE HANDLING
	switch (pMsg->GetMessageID())
	{
	case MSG_SPAWNUNIT:
		{
			CSpawnUnitMessage* pSMSG = dynamic_cast<CSpawnUnitMessage*>(pMsg);
			CUnit* pUnit = (CUnit*)CObjectManager::GetInstance()->CreateObject(pSMSG->GetUnitType(), pSMSG->GetPlayerID() );
			pUnit->SetPos(pSMSG->GetPos());
			pUnit->SetFacing(pSMSG->GetFacing());
			pUnit->SetPlayerID(pSMSG->GetPlayerID());

			CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer(pSMSG->GetPlayerID());
			switch (pSMSG->GetUnitType())
			{
			case UT_SWORDSMAN:
				pPlayer->GetStats()->nSwordsmanCreated++;
				break;
			case UT_ARCHER:
				pPlayer->GetStats()->nArcherCreated++;
				break;
			case UT_CAVALRY:
				pPlayer->GetStats()->nCalvaryCreated++;
				break;
			}

			if (pSMSG->GetLoaded())
			{
				pUnit->SetHP(pSMSG->GetHealth());
				pUnit->SetTilesMoved(pSMSG->GetTilesMoved());
				pUnit->SetHasAttacked(pSMSG->GetHasAttacked());
				if (pSMSG->GetSpells().size() != 0)
				{
					for (unsigned int i = 0; i < pSMSG->GetSpells().size(); ++i)
					{
						((CHero*)pUnit)->GiveSpell(pSMSG->GetSpells()[i]);
					}
				}
				if (pSMSG->GetEffects().size() != 0)
				{
					for (unsigned int i = 0; i < pSMSG->GetEffects().size(); ++i)
					{
						pUnit->PushEffect(CAbilityManager::GetInstance()->GetAbility(pSMSG->GetEffects()[i]),1);
					}

				}
			}
		}
		break;
	case MSG_DESPAWNUNIT:
		{
			CDespawnUnitMessage* pSMSG = dynamic_cast<CDespawnUnitMessage*>(pMsg);
			if (CGameplayState::GetInstance()->GetSelectedUnit() == pSMSG->GetUnit())
			{
				CGameplayState::GetInstance()->ClearSelections();
			}
			CTile* tile = CTileManager::GetInstance()->GetTile(pSMSG->GetUnit()->GetPos().nPosX, pSMSG->GetUnit()->GetPos().nPosY);
			int x = 9;
			tile->SetIfOccupied(false);
			if (pSMSG->GetUnit()->GetType() != UT_SKELETON)
				tile->SetIfDeadTile(true);
			if (pSMSG->GetUnit() == CGameplayState::GetInstance()->GetHighlighted())
				CGameplayState::GetInstance()->ClearHighlighted();
			CObjectManager::GetInstance()->RemoveObject(pSMSG->GetUnit());
			if(pSMSG->GetUnit()->GetType() == UT_HERO || pSMSG->GetUnit()->GetType() == UT_CASTLE)
			{
				if(pThis->GetCurrentPlayer()->GetAI())
				{
					CGameOverState::GetInstance()->SetAI(true);
				}
				else
				{
					CGameOverState::GetInstance()->SetAI(false);
					if(pSMSG->GetUnit()->GetPlayerID() == 0)
						CGameOverState::GetInstance()->SetPlayer(2);
					else if(pSMSG->GetUnit()->GetPlayerID() == 1)
						CGameOverState::GetInstance()->SetPlayer(1);
				}
				CStateStack::GetInstance()->Push(CGameOverState::GetInstance());
			}

			if (pSMSG->GetUnit()->GetPlayerID() != pThis->GetCurrentPlayer()->GetPlayerID())
			{
				pThis->GetCurrentPlayer()->SetExp(pThis->GetCurrentPlayer()->GetExp() + pSMSG->GetUnit()->GetEXPValue());
				pThis->GetCurrentPlayer()->GetStats()->nPlayerEXPEarned+=pSMSG->GetUnit()->GetEXPValue();
				switch (pSMSG->GetUnit()->GetType())
				{
				case UT_SWORDSMAN:
					pThis->GetCurrentPlayer()->GetStats()->nSwordsmanKilled++;
					break;
				case UT_ARCHER:
					pThis->GetCurrentPlayer()->GetStats()->nArcherKilled++;
					break;
				case UT_CAVALRY:
					pThis->GetCurrentPlayer()->GetStats()->nCavalryKilled++;
					break;
				}
			}

		}
		break;
	case MSG_ADDRESOURCE:
		{
			CAddResourceMessage* pSMSG = dynamic_cast<CAddResourceMessage*>(pMsg);
			CPlayer* pPlayer = pThis->GetPlayer(pSMSG->GetPlayerID());

			switch (pSMSG->GetTileType())
			{
			case TT_FARM:
				{
					pPlayer->SetMaxPopCap(pPlayer->GetMaxPopCap() + POP_PER_FARM);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			case TT_MINE:
				{
					pPlayer->SetMetal(pPlayer->GetMetal() + METAL_PER_MINE);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			case TT_MILL:
				{
					pPlayer->SetWood(pPlayer->GetWood() + WOOD_PER_MILL);
					pPlayer->SetAP(pPlayer->GetAP() + AP_PER_CAPTURE);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}


CUnit* CGameManager::GetUnitByID(int nID)
{
	for (unsigned int i = 0; i < m_vUnits.size(); ++i)
	{
		if (m_vUnits[i]->GetUniqueID() == nID)
			return m_vUnits[i];

	}
	return nullptr;
}

void CGameManager::AddModification(MapModification mod)
{
	m_vMapMods.push_back(mod);

}