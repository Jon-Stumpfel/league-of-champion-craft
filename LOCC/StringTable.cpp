#include "StdAfx.h"
#include "StringTable.h"
StringTable* StringTable::s_Instance = nullptr;
StringTable::StringTable(void)
{
	IsItModern = true;
	modernenglish.push_back("Start");
	yeoldeanglish.push_back("Steort");
	modernenglish.push_back("Load");
	yeoldeanglish.push_back("Byrden");
	modernenglish.push_back("Options");
	yeoldeanglish.push_back("Costs");
	modernenglish.push_back("Credits");
	yeoldeanglish.push_back("Apwyrdes");
	modernenglish.push_back("Help");
	yeoldeanglish.push_back("Ar");
	modernenglish.push_back("Exit");
	yeoldeanglish.push_back("Utfaer");
	modernenglish.push_back("Credits:");
	yeoldeanglish.push_back("Apwyrdes:");
	modernenglish.push_back("Art: Maher Sagrillo");
	yeoldeanglish.push_back("Creaft: Maher Sagrillo");
	modernenglish.push_back("Lead Producer: Jon");
	yeoldeanglish.push_back("Aetlaede Icend: Jon");
	modernenglish.push_back("Sounds: Jordan Wells");
	yeoldeanglish.push_back("Cnylls: Jordan Wells");
	modernenglish.push_back("Tile Engine: Dalton Gbur");
	yeoldeanglish.push_back("Hroftigel Searu: Dalton Gbur");
	modernenglish.push_back("Core Gameplay: Kyle Veilleux");
	yeoldeanglish.push_back("Midde Gamengliw: Kyle Veilleux");
	modernenglish.push_back("Particle Engine: Ryan Cartier");
	yeoldeanglish.push_back("Soru Searu: Ryan Cartier");
	modernenglish.push_back("Animation Engine: Jon Stumpfel");
	yeoldeanglish.push_back("Onbryrdnes Searu: Jon Stumpfel");
	modernenglish.push_back("Assistant Producer: Robert Martinez");
	yeoldeanglish.push_back("Geongra Icend: Robert Martinez");
	modernenglish.push_back("Minor units also provided by Blizzard Entertainment");
	yeoldeanglish.push_back("Clidwyrt hererinc eac foresceawianed purh Blizzard Entertainment");
	ReadSlot(1);
	ReadSlot(2);
	ReadSlot(3);
	modernenglish.push_back("Load from slot");
	yeoldeanglish.push_back("Hlaest fram hwil");
	modernenglish.push_back("Save to slot");
	yeoldeanglish.push_back("Nerian od hwil");
	modernenglish.push_back("Delete slot");
	yeoldeanglish.push_back("Fordon hwil");
	modernenglish.push_back("Are you sure?");
	yeoldeanglish.push_back("Sien ge gewisslic?");
	modernenglish.push_back("No");
	yeoldeanglish.push_back("Ne");
	modernenglish.push_back("Yes");
	yeoldeanglish.push_back("Waer");
	modernenglish.push_back("Sound Volume");
	yeoldeanglish.push_back("Agalan Rim");
	modernenglish.push_back("Music Volume");
	yeoldeanglish.push_back("Dreamas Rim");
	modernenglish.push_back("Fullscreen");
	yeoldeanglish.push_back("Fulldaeg");
	modernenglish.push_back("Modern English?");
	yeoldeanglish.push_back("Niwe Englisc?");
	modernenglish.push_back("Back");
	yeoldeanglish.push_back("Baec");
	modernenglish.push_back("Player ");
	yeoldeanglish.push_back("Gliwiend ");
	modernenglish.push_back("Attack Phase");
	yeoldeanglish.push_back("Forsecan Tacnunga");

}
StringTable::~StringTable(void)
{

}
StringTable* StringTable::GetInstance()
{
	if (s_Instance == nullptr)
		s_Instance = new StringTable();
	return s_Instance;
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
void StringTable::ReadSlot(int nSlot)
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
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Hwil " << nSlot;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Map ID: "<< s.nMapID;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Mappe ID " << s.nMapID;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Current Player: " << s.nCurrPlayer + 1;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Gifsceatt Gliwiend: " << s.nCurrPlayer + 1;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Current Turn: " << (s.nPhaseCount / 4) + 1;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Gifsceatt Cierr: " << (s.nPhaseCount / 4) + 1;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Current Phase: ";
		if (s.nCurrPhase == 0)
			woss << "Movement";
		else
			woss << "Attack";
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Gifsceatt Tacnung: ";
		if (s.nCurrPhase == 0)
			woss << "Faer";
		else
			woss << "Aflygennes";
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Player 1 ";
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Gliwiend 1 ";
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Wood " << s.p1.nWood;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Acholt " << s.p1.nWood;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Metal " << s.p1.nMetal;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Wecg " << s.p1.nMetal;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  AP " << s.p1.nAP;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  AP " << s.p1.nAP;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Units " << s.p1.nNumUnits;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Hererincs " << s.p1.nNumUnits;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  XP " << s.p1.nXP;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  XP " << s.p1.nXP;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "Player 2 ";
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "Gliwiend 2 ";
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Wood " << s.p2.nWood;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Acholt " << s.p2.nWood;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Metal " << s.p2.nMetal;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Wecg " << s.p2.nMetal;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  AP " << s.p2.nAP;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  AP " << s.p2.nAP;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  Units " << s.p2.nNumUnits;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  Hererincs " << s.p2.nNumUnits;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
		woss << "  XP " << s.p2.nXP;
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "  XP " << s.p2.nXP;
		yeoldeanglish.push_back(woss.str());
		woss.str((""));
	}
	else
	{
		std::ostringstream woss;
		woss << "NO SAVE";
		modernenglish.push_back(woss.str());
		woss.str((""));
		woss << "NE NERIAN";
		yeoldeanglish.push_back(woss.str());
	}
}
void StringTable::SetLanguage(bool IsItModernEnglish)
{
	if(IsItModernEnglish)
	{
		IsItModern = true;
	}
	else
	{
		IsItModern = false;
	}
}
std::string StringTable::GetString(std::string tempstring)
{
	for(std::vector<int>::size_type i = 0; i != modernenglish.size(); i++)
	{
		if(modernenglish[i] == tempstring)
		{
			if(IsItModern)
				return modernenglish[i];
			else
				return yeoldeanglish[i];
		}
	}
	return NULL;
}