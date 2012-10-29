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
	modernenglish.push_back("Slot ");
	yeoldeanglish.push_back("Hwil ");
	modernenglish.push_back("Map ID: ");
	yeoldeanglish.push_back("Mappe ID ");
	modernenglish.push_back("Current Player: ");
	yeoldeanglish.push_back("Gifsceatt Gliwiend: ");
	modernenglish.push_back("Current Turn: ");
	yeoldeanglish.push_back("Gifsceatt Cierr: ");
	modernenglish.push_back("Current Phase: ");
	modernenglish.push_back("Movement");
	modernenglish.push_back("Attack");
	yeoldeanglish.push_back("Gifsceatt Tacnung: ");
	yeoldeanglish.push_back("Faer");
	yeoldeanglish.push_back("Aflygennes");
	modernenglish.push_back("  Wood ");
	yeoldeanglish.push_back("  Acholt ");
	modernenglish.push_back("  Metal ");
	yeoldeanglish.push_back("  Wecg ");
	modernenglish.push_back("  AP ");
	yeoldeanglish.push_back("  AP ");
	modernenglish.push_back("  Units ");
	yeoldeanglish.push_back("  Hererincs ");
	modernenglish.push_back("  XP ");
	yeoldeanglish.push_back("  XP ");
	modernenglish.push_back("NO SAVE");
	yeoldeanglish.push_back("NE NERIAN");
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
	modernenglish.push_back(" wins the coin toss");
	yeoldeanglish.push_back(" wyrcans an mynet cnyssan");
	modernenglish.push_back("AI Wins!");
	yeoldeanglish.push_back("AI Wyrcans!");
	modernenglish.push_back("  Wins!");
	yeoldeanglish.push_back("  Wyrcans!");
	modernenglish.push_back("Bottleneck");
	yeoldeanglish.push_back("Ampellanbogenett");
	modernenglish.push_back("Siege on the mountain");
	yeoldeanglish.push_back("Beadwa on dy beorga");
	modernenglish.push_back("The Champion hurls a ball of fire at a target.");
	yeoldeanglish.push_back("Dy Cempan scepas ever trindan of fyr aet ever targete.");
	modernenglish.push_back("The Champion closes the wounds of a selected unit.");
	yeoldeanglish.push_back("Dy Cempan lucan dy benns of ever aceosan cempestran.");
	modernenglish.push_back("The Champion shields his target preventing damage for a turn.");
	yeoldeanglish.push_back("Dy Cempan scyld his targete forsceotaning aewerdla for ever cierr.");
	modernenglish.push_back("The Champion increases the speed of a selected unit for a turn.");
	yeoldeanglish.push_back("Dy Cempan eacnians dy ofost of ever aceosan cempestran for ever cierr.");
	modernenglish.push_back("Test spell for testing");
	yeoldeanglish.push_back("Fandian galdru for fandianing");
	modernenglish.push_back("The Calvary rushes forward, dealing more damage for every unit hit in a line.");
	yeoldeanglish.push_back("Dy Eored reses on, fordaeing ma aewerdla for aelc cempestran abeat in ever sceaftriht.");
	modernenglish.push_back("Reduces the cost of moving to one for a target unit.");
	yeoldeanglish.push_back("Apynnes dy deore of onstyrianing to mon for ever targete cempestran.");
	modernenglish.push_back("The Champion turns a target forest into a plain.");
	yeoldeanglish.push_back("Dy Cempan cierrs ever targete weald in ever feld.");
	modernenglish.push_back("The Champion heals the wounds of everyone around him.");
	yeoldeanglish.push_back("Dy Champion haelans dy benns of gehwa tyrning him.");
	modernenglish.push_back("Rally the troops, increasing thier damage by 2 for a turn.");
	yeoldeanglish.push_back("Ralley dy dugups, weaxaning hira aewerdla purh 2 for ever cierr.");
	modernenglish.push_back("Nearby units have the cost to move reduced to 1 until the end of the turn.");
	yeoldeanglish.push_back("Nearbye cempestrans ag dy deore to onstyrian apynned to 1 od dy ende of dy cierr.");
	modernenglish.push_back("The Champion creates a mountain tile from any non-resource tile.");
	yeoldeanglish.push_back("Dy Cempan scieppans ever beorga sceard fram aenig non-resource sceard.");
	modernenglish.push_back("The Swordsman gives up movement for a turn to reduce his damage by half.");
	yeoldeanglish.push_back("Dy Sweordsesne agiefans faereld for ever cierr to apynne his aewerdla purh healf.");
	modernenglish.push_back("If the Archer hasn't moved, he can prepare a shot that deals double his damage.");
	yeoldeanglish.push_back("Gif dy Scytta ahne abifed, he con gearcian ever scotung se fordae twihwyrft his aewerdla.");
	modernenglish.push_back("Brings any unit back to life as a skeleton. Can only be cast on a tile with a tombstone.");
	yeoldeanglish.push_back("Gebrengans aenig cempestran baec to ae swa a skeletone. Hit can anga beon beweorpan on ever sceard mid ever byrgelsstan.");
	modernenglish.push_back("It's a missile made of magic.");
	yeoldeanglish.push_back("Hit's ever scotung maede of bealu.");
	modernenglish.push_back("The champion hurls a bolt of ice at a target, reducing their speed by 2 for the next turn.");
	yeoldeanglish.push_back("Dy Cempan scepas ever bolt of gicel aet ever targete, apynning hira ofost purh 2 for se niehsta cierr.");

}
StringTable::~StringTable(void)
{
	modernenglish.clear();
	delete &modernenglish;
	yeoldeanglish.clear();
	delete &yeoldeanglish;
	delete s_Instance;
	s_Instance = nullptr;
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
	return "String not found!";
}