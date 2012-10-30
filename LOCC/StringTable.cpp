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
	modernenglish.push_back("The Champion shields his target, preventing damage for a turn.");
	yeoldeanglish.push_back("Dy Cempan scyld his targete, forsceotaning aewerdla for ever cierr.");
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
	modernenglish.push_back("Brings any unit back to life as a skeleton. It can only be cast on a tile with a tombstone.");
	yeoldeanglish.push_back("Gebrengans aenig cempestran baec to ae swa a skeletone. Hit can anga beon beweorpan on ever sceard mid ever byrgelsstan.");
	modernenglish.push_back("It's a missile made of magic.");
	yeoldeanglish.push_back("Hit's ever scotung maede of bealu.");
	modernenglish.push_back("The champion hurls a bolt of ice at a target, reducing their speed by 2 for the next turn.");
	yeoldeanglish.push_back("Dy Cempan scepas ever bolt of gicel aet ever targete, apynning hira ofost purh 2 for se niehsta cierr.");
	modernenglish.push_back("The hero calls a bolt of lightning down on a targeted tile.");
	yeoldeanglish.push_back("Dy bealdor clipians ever bolt of liget forscutan on ever targetede sceard.");
	modernenglish.push_back("The Champion sets a targets weapon ablaze, increasing thier damage by 2.");
	yeoldeanglish.push_back("Dy Cempan gesettans ever targetes waepen on fyre, eacnianing hira aewerdla purh 2.");
	modernenglish.push_back("The Champion uses a powerful lightning strike to stun the enemy for the next turn.");
	yeoldeanglish.push_back("Dy Cempan neotans ever ellenorf liget dynt to stunne dy feond for dy niehsta cierr.");
	modernenglish.push_back("The Champion uses a powerful explosive arrow.");
	yeoldeanglish.push_back("Dy Cempan neotans ever ellenrof beorcive arwan.");
	modernenglish.push_back("The Champion freezes all the tiles in front of him.");
	yeoldeanglish.push_back("Dy Cempan frieses eall dy sceards foran of him.");
	modernenglish.push_back("The Champion strikes a target with a heavy blow.");
	yeoldeanglish.push_back("Dy Cempan dynts ever targete mid ever hefig slege.");
	modernenglish.push_back("The Champion engulfs himself in flames and explodes into an unholy napalm bloom of death.");
	yeoldeanglish.push_back("Dy Cempan geniepeps himselfe in baels and beorces in evern unhalig napalme blowan of cwild.");
	modernenglish.push_back("The Champion uses his bow to attack a target from afar.");
	yeoldeanglish.push_back("Dy Cempan neotans his boga to forsecan ever targete feorran.");
	modernenglish.push_back("The Champion pushes lightning through all conductive targets.");
	yeoldeanglish.push_back("Dy Cempan scufanes liget pugh eall conductaive targetes.");
	modernenglish.push_back("A spinning attack so fast that the Champion's sheer velocity throws back units.");
	yeoldeanglish.push_back("Ever aspinne forsecan swa faestan se dy Cempan's sheere velocity weorpans baec cempestrans.");
	modernenglish.push_back("The Champion uses his bow to hit all targets in a line, doing 2 less damage for each target hit.");
	yeoldeanglish.push_back("Dy Cempan neotans his boga to abeat eall targetes in ever sceaftriht, doning 2 laessa aewerdla for aelc targete abeat.");
	modernenglish.push_back("The Champion swings his sword, hitting all targets in front of him.");
	yeoldeanglish.push_back("Dy Cempan totridas his sweord, abeatting eall targetes aetforan him.");
	modernenglish.push_back("The Champion spins, hitting all targets in front of him.");
	yeoldeanglish.push_back("Dy Cempan aspinnes, abeatting eall, targettes aetforan him.");
	modernenglish.push_back("The Champion stabs all units around him.");
	yeoldeanglish.push_back("Dy Cempan sticeas eall cempestrans tyrning him.");
	modernenglish.push_back("The Champion rushes forward in a direction, dealing 2 extra damage for every unit hit.");
	yeoldeanglish.push_back("Dy Cempan reses on in ever gestihtung, fordaeing 2 extrea aewerdla for aelc cempestran abeat.");
	modernenglish.push_back("The Champion does massive damage to an enemy near him.");
	yeoldeanglish.push_back("Dy Cempan dons great aewerdla to evern feond neah him.");
	modernenglish.push_back("Melee Attack");
	yeoldeanglish.push_back("Melee Forsecan");
	modernenglish.push_back("This unit attacks with a melee weapon.");
	yeoldeanglish.push_back("Pes cempestran forsecan mid ever melee waepen.");
	modernenglish.push_back("Range Attack");
	yeoldeanglish.push_back("Underwierpest Forsecan");
	modernenglish.push_back("This unit attacks with a ranged weapon.");
	yeoldeanglish.push_back("Pes cempestran forsecan mid ever Underwierpested waepen.");
	modernenglish.push_back("Move");
	yeoldeanglish.push_back("Lacan");
	modernenglish.push_back("Allows you to move things to places.");
	yeoldeanglish.push_back("Alyfans pu to lacan dings to stedes.");
	modernenglish.push_back("Spells");
	yeoldeanglish.push_back("Galdru");
	modernenglish.push_back("Spawn Archer");
	yeoldeanglish.push_back("Acennan Scytta");
	modernenglish.push_back("Spawn Swordsman");
	yeoldeanglish.push_back("Acennan Sweordsesne");
	modernenglish.push_back("Spawn Calvary");
	yeoldeanglish.push_back("Acennan Raedehere");
	modernenglish.push_back("Ice Block");
	yeoldeanglish.push_back("Is Mearr");
	modernenglish.push_back("The hero uses his power of freezing stuff to make an ice block");
	yeoldeanglish.push_back("Dy bealdor neotans his miht of freoig idisc to macian evern is mearr");
	modernenglish.push_back("Blank parchment is blank");
	yeoldeanglish.push_back("Blanke bocfell is blanke");
	modernenglish.push_back("Blank Scroll");
	yeoldeanglish.push_back("Blanke Bocfell");
	modernenglish.push_back("GAME PAUSED");
	yeoldeanglish.push_back("GAME STANDED");
	modernenglish.push_back("Resume Game");
	yeoldeanglish.push_back("Fehe Game");
	modernenglish.push_back("Options");
	yeoldeanglish.push_back("Costs");
	modernenglish.push_back("Save/Load");
	yeoldeanglish.push_back("Gelesniss/Llaest");
	modernenglish.push_back("Exit to Menu");
	yeoldeanglish.push_back("Utfaer to Menue");
}
StringTable::~StringTable(void)
{
	modernenglish.clear();
	yeoldeanglish.clear();
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
void StringTable::DeleteInstance(void)
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}