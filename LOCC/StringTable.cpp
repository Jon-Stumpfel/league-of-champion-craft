#include "StdAfx.h"
#include "StringTable.h"
StringTable* StringTable::s_Instance = nullptr;
StringTable::StringTable(void)
{
	IsItModern = true;
	//start menu
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
	//crdits screen
	modernenglish.push_back("Credits:");
	yeoldeanglish.push_back("Apwyrdes:");
	modernenglish.push_back("Art: Maher Sagrillo");
	yeoldeanglish.push_back("Creaft: Maher Sagrillo");
	modernenglish.push_back("Lead Producer: John O'Leske");
	yeoldeanglish.push_back("Aetlaede Icend: John O'Leske");
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
	yeoldeanglish.push_back("Clidwyrt hererincs eac foresceawianed purh Blizzard Entertainment");
	modernenglish.push_back("Slot ");
	yeoldeanglish.push_back("Hwil ");
	modernenglish.push_back("Map ID: ");
	yeoldeanglish.push_back("Mappe ID ");
	modernenglish.push_back("Current Player: ");
	yeoldeanglish.push_back("Gifsceatt Gliwiend: ");
	modernenglish.push_back("Current Turn: ");
	yeoldeanglish.push_back("Gifsceatt Cierr: ");
	modernenglish.push_back("Current Phase: ");
	yeoldeanglish.push_back("Gifsceatt Tacnung: ");
	modernenglish.push_back("Movement");
	yeoldeanglish.push_back("Faer");
	modernenglish.push_back("Attack");
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
	modernenglish.push_back("Trample Hill");
	yeoldeanglish.push_back("Fortritte Beorg");
	modernenglish.push_back("Forest Siege");
	yeoldeanglish.push_back("Weald Beadwa");
	modernenglish.push_back("Close Quarters");
	yeoldeanglish.push_back("Lucan Daels");
	modernenglish.push_back("A Bridge runs Through It");
	yeoldeanglish.push_back("Ever Brycg iernans Pugh Hit");
	modernenglish.push_back("Frozen Throne");
	yeoldeanglish.push_back("Forstlic Gifstol");
	modernenglish.push_back("Grave Circumstance");
	yeoldeanglish.push_back("Byrgen Circumsteance");
	modernenglish.push_back("Twin Wiver");
	yeoldeanglish.push_back("Getwisa Ea");
	modernenglish.push_back("Press cancel to return...");
	yeoldeanglish.push_back("Preat unde to wendan...");
	modernenglish.push_back("Siege on the Mountain");
	yeoldeanglish.push_back("Beadwa on dy Beorga");
	modernenglish.push_back("The Champion hurls a ball of fire at a target.");
	yeoldeanglish.push_back("Dy Cempan scepas ever trindan of fyr aet ever targete.");
	modernenglish.push_back("The Champion closes the wounds of a selected unit.");
	yeoldeanglish.push_back("Dy Cempan lucan dy benns of ever aceosan cempestran.");
	modernenglish.push_back("The Champion shields his target, preventing damage for a turn.");
	yeoldeanglish.push_back("Dy Cempan scylds his targete, forsceotaning aewerdla for ever cierr.");
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

	modernenglish.push_back("The Champion uses the dead to bolster his army, only works on tombstone tiles.");
	yeoldeanglish.push_back("Dy Cempan neotans se blod be bolster cerdic here ealdor geneat on tombstone scirdenWeak.");

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
	modernenglish.push_back("A spinning attack so fast that the Champion's sheer velocity damages all foes around them");
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
	modernenglish.push_back("The Champion shields his allies, decreasing their damage taken by 70% for 2 turns.");
	yeoldeanglish.push_back("Dy Cempan scylds his gefylceaps, wanunging hira aewerdla niman purh 70% for 2 cierrs.");

	modernenglish.push_back("Applies a debuff, Champion's take 10 damage while all other units die.");
	yeoldeanglish.push_back("Druncen sum debuff bealdor gemot 10 angilde hwi a obres rim feorh.");

	modernenglish.push_back("The Champion steals the mind of one of his enemies. Doesn't work on Champion units.");
	yeoldeanglish.push_back("Dy Cempan stelans dy hyge aetforan mon aetforan his feonds. Donsn't weorc on Cempan herenics.");
	modernenglish.push_back("The Champion moves a unit from one place to another.");
	yeoldeanglish.push_back("Dy Cempan lacans ever herenic fram mon stede to gewrixlung.");
	modernenglish.push_back("The Champion sacrifices a unit to gain an extra turn.");
	yeoldeanglish.push_back("Dy Cempan blotans ever herenic to earnian evern extrea cierr.");
	modernenglish.push_back("The Champion raises all dead around him.");
	yeoldeanglish.push_back("Dy Cempan hebbans eall cwild tyrning him.");

	modernenglish.push_back("");
	yeoldeanglish.push_back("");
	
	modernenglish.push_back("All ally units get half their damage back in health.");
	yeoldeanglish.push_back("Eall gefylceap rim socn ceren hiera angilde hrycg beinnan eftbot.");

	modernenglish.push_back("The Champion sends a wall of ice down from the sky, damaging enemies they hit.");
	yeoldeanglish.push_back("Dy Cempan sendans ever waeg aetforan is forscutan fram dy lyft, aewerdlaing feonds agon abeat.");
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
	
	//How to text
	modernenglish.push_back("Tile Information");
	yeoldeanglish.push_back("Sceard Ascung");
	modernenglish.push_back("Tile Type");
	yeoldeanglish.push_back("Sceard Getacnung");
	modernenglish.push_back("-Plains-");
	yeoldeanglish.push_back("-Felds-");
	modernenglish.push_back("A Basic Tile");
	yeoldeanglish.push_back("Ever Felcsop Sceard");
	modernenglish.push_back("costing 1 AP ");
	yeoldeanglish.push_back("deoring 1 AP ");
	modernenglish.push_back("to move across");
	yeoldeanglish.push_back("to onstyrian oferfaereld");
	modernenglish.push_back("-Forest-");
	yeoldeanglish.push_back("-Weald-");
	modernenglish.push_back("A Tile giving");
	yeoldeanglish.push_back("Ever Sceard giefaning");
	modernenglish.push_back("a dodge chance");
	yeoldeanglish.push_back("ever ascunian belimp");
	modernenglish.push_back("costing 2 AP ");
	yeoldeanglish.push_back("deoring 2 AP ");
	modernenglish.push_back("-Mountains-");
	yeoldeanglish.push_back("-Beorgas-");
	modernenglish.push_back("Archer a range");
	yeoldeanglish.push_back("Scytta ever Underwierpest");
	modernenglish.push_back("Adavantage ");
	yeoldeanglish.push_back("Bot ");
	modernenglish.push_back("costing 3 AP ");
	yeoldeanglish.push_back("deoring 3 AP ");
	modernenglish.push_back("-Water-");
	yeoldeanglish.push_back("-Waeter-");
	modernenglish.push_back("An Impassable Tile");
	yeoldeanglish.push_back("Evern Ungefaren Sceard");
	modernenglish.push_back("that can't be");
	yeoldeanglish.push_back("se con't beon");
	modernenglish.push_back("moved across");
	yeoldeanglish.push_back("onstyrianed oferfaereld");
	modernenglish.push_back("Resource Tile");
	yeoldeanglish.push_back("Resource Sceard");
	modernenglish.push_back("-Mill-");
	yeoldeanglish.push_back("-Mylen-");
	modernenglish.push_back("A Forest Tile");
	yeoldeanglish.push_back("Ever Weald Sceard");
	modernenglish.push_back("that adds 10 ");
	yeoldeanglish.push_back("se fenmetes 10 ");
	modernenglish.push_back("wood to its ");
	yeoldeanglish.push_back("acholt to hits ");
	modernenglish.push_back("owner's resource");
	yeoldeanglish.push_back("aga's resource");
	modernenglish.push_back("-Mine-");
	yeoldeanglish.push_back("-Gyldenwecg-");
	modernenglish.push_back("A Mountian Tile");
	yeoldeanglish.push_back("Ever Beorga Sceard");
	modernenglish.push_back("Metal to its ");
	yeoldeanglish.push_back("Clympre to hits ");
	modernenglish.push_back("-Farm-");
	yeoldeanglish.push_back("-Berewic-");
	modernenglish.push_back("A Plains Tile");
	yeoldeanglish.push_back("Ever Feld Sceard");
	modernenglish.push_back("that adds 6 ");
	yeoldeanglish.push_back("se fenmetes 6 ");
	modernenglish.push_back("to its owner's");
	yeoldeanglish.push_back("to hits aga's");
	modernenglish.push_back("Population Cap");
	yeoldeanglish.push_back("Landwaru Caeppe");
	modernenglish.push_back("Tile Status");
	yeoldeanglish.push_back("Sceard Endebyrdnes");
	modernenglish.push_back("-Frozen-");
	yeoldeanglish.push_back("-Forstlic-");
	modernenglish.push_back("Frozen Tile");
	yeoldeanglish.push_back("Forstlic Sceard");
	modernenglish.push_back("Increases AP cost");
	yeoldeanglish.push_back("Eacnians AP deore");
	modernenglish.push_back("to move by 1");
	yeoldeanglish.push_back("to onstyrian purh 1");
	modernenglish.push_back("-Captured-");
	yeoldeanglish.push_back("-Forfanged-");
	modernenglish.push_back("When Tile is Captured it adds the benefit to it's owner");
	yeoldeanglish.push_back("Ponne Sceard is Forfanged hit fenmetes an ar od hit's aga");
	modernenglish.push_back("-Capturing-");
	yeoldeanglish.push_back("-Forfanging-");
	modernenglish.push_back("When Unit moves onto a resource tile, they will Capture it if they are not killed or move off it");
	yeoldeanglish.push_back("Ponne Hererinc onstyrians onto ever resource sceard, agon willa Forfang hit gif agon aien ne deapcwielmended sam onstyrian uferian hit");
	modernenglish.push_back("-Dead-");
	yeoldeanglish.push_back("-Cwild-");
	modernenglish.push_back("Shows a fallen ");
	yeoldeanglish.push_back("Wisians ever droren");
	modernenglish.push_back("unit that can");
	yeoldeanglish.push_back("hererinc se con");
	modernenglish.push_back("be Reanimated");
	yeoldeanglish.push_back("beon Acucianed");
	modernenglish.push_back("Unit Information");
	yeoldeanglish.push_back("Herenic Ascung");
	modernenglish.push_back("-Basic Units-");
	yeoldeanglish.push_back("-Felcsop Herenics-");
	modernenglish.push_back("-Champion-");
	yeoldeanglish.push_back("-Cempan-");
	modernenglish.push_back("Commanding Unit. If he dies, ");
	yeoldeanglish.push_back("Beodending Herenic. Gif he sweltans, ");
	modernenglish.push_back("the game is over");
	yeoldeanglish.push_back("an game is bufan");
	modernenglish.push_back("Special ability: Spell Tree");
	yeoldeanglish.push_back("Swaes craeft: Galdru Aesc");
	modernenglish.push_back("Unit has access to ");
	yeoldeanglish.push_back("Herenic ah togang od ");
	modernenglish.push_back("customizible Spell trees");
	yeoldeanglish.push_back("siduizeable Galdru aescs");
	modernenglish.push_back("-Calvary-");
	yeoldeanglish.push_back("-Eored-");
	modernenglish.push_back("Advanced melee Unit");
	yeoldeanglish.push_back("Fordweard melee Herenic");
	modernenglish.push_back("Special ability: Charge");
	yeoldeanglish.push_back("Swaes craeft: Hilderae");
	modernenglish.push_back("Charges forward, damging  ");
	yeoldeanglish.push_back("Hilderaes on aewerdling  ");
	modernenglish.push_back("units in one cardinal Direction ");
	yeoldeanglish.push_back("herenics in mon heorr Gestihtung ");
	modernenglish.push_back("-TILE CHARGED TO MUST BE OPEN");
	yeoldeanglish.push_back("-SCEARD HILDERAED TO MOTAN BEON OPEN");
	modernenglish.push_back("-Archer-");
	yeoldeanglish.push_back("-Scytta-");
	modernenglish.push_back("Ranged Unit");
	yeoldeanglish.push_back("Underwierpested Herenic");
	modernenglish.push_back("Special ability: Volley");
	yeoldeanglish.push_back("Swaes craeft: Vollae");
	modernenglish.push_back("Fires mulitple Arrows at ");
	yeoldeanglish.push_back("Fyrs fela Arwans aet ");
	modernenglish.push_back("a target unit in range");
	yeoldeanglish.push_back("ever targete herenic in underwierpest");
	modernenglish.push_back("-CANNOT MOVE BEFORE ATTACK");
	yeoldeanglish.push_back("-CONNE ONSTYRIAN BEFORAN AFKYGENNES");
	modernenglish.push_back("-Swordsman-");
	yeoldeanglish.push_back("-Sweordsesne-");
	modernenglish.push_back("Melee Unit");
	yeoldeanglish.push_back("Melee Herenic");
	modernenglish.push_back("Special ability: Stand Ground");
	yeoldeanglish.push_back("Swaes craeft: Standan Flett");
	modernenglish.push_back("Braces for impact");
	yeoldeanglish.push_back("Braces for gegrind");
	modernenglish.push_back("reducing dmg taken next turn");
	yeoldeanglish.push_back("apynning dmg niman niehsta cierr");
	modernenglish.push_back("-Castle Base-");
	yeoldeanglish.push_back("-Castel Syll-");
	modernenglish.push_back("Support Unit");
	yeoldeanglish.push_back("Geoc Herenic");
	modernenglish.push_back("Special ability: Spawn Unit");
	yeoldeanglish.push_back("Swaes craeft: Acennan Herenic");
	modernenglish.push_back("The Base can Spawn ");
	yeoldeanglish.push_back("An Syll con Acennan");
	modernenglish.push_back("other Units");
	yeoldeanglish.push_back("oder Herenics");
	modernenglish.push_back("-Ice Block-");
	yeoldeanglish.push_back("-Gicel Mearr-");
	modernenglish.push_back("Neutral Unit");
	yeoldeanglish.push_back("Neutrael Herenic");
	modernenglish.push_back("It's name says it ");
	yeoldeanglish.push_back("Hit's nama cwepap hit");
	modernenglish.push_back("all a Block that");
	yeoldeanglish.push_back("eall ever Mearr se");
	modernenglish.push_back("blocks most movement");
	yeoldeanglish.push_back("mearrs swipost faer");
	modernenglish.push_back("-Skeleton-");
	yeoldeanglish.push_back("-Grima-");
	modernenglish.push_back("Dead Melee Unit");
	yeoldeanglish.push_back("Cwild Melee Herenic");
	modernenglish.push_back("Poor reainmated  ");
	yeoldeanglish.push_back("Earm acucianed  ");
	modernenglish.push_back("soul that fights");
	yeoldeanglish.push_back("sawol se winnans");
	modernenglish.push_back("for his summoner");
	yeoldeanglish.push_back("for his bannaner");
	modernenglish.push_back("Gameplay Information");
	yeoldeanglish.push_back("Gamengliw Ascung");
	modernenglish.push_back("-Phases-");
	yeoldeanglish.push_back("-Tacnungs-");
	modernenglish.push_back("-Movement-");
	yeoldeanglish.push_back("-Faer-");
	modernenglish.push_back("During movement, players move");
	yeoldeanglish.push_back("Langsumllce faer, gliwiends onstyrian");
	modernenglish.push_back("their champions and other units, ");
	yeoldeanglish.push_back("hira cempans and oder herenics, ");
	modernenglish.push_back("as well as cast any champion ");
	yeoldeanglish.push_back("swa wel swa beweorpan aenig cempan ");
	modernenglish.push_back("spells that can be cast during ");
	yeoldeanglish.push_back("galdrus se con beon beweorpan langsumllce");
	modernenglish.push_back("the movement phase ");
	yeoldeanglish.push_back("se faer tacnung");
	modernenglish.push_back("-Attack-");
	yeoldeanglish.push_back("-Aflygen-");
	modernenglish.push_back("During the attack phase, ");
	yeoldeanglish.push_back("Langsumllce se aflygen tacnung, ");
	modernenglish.push_back("Champions and other units ");
	yeoldeanglish.push_back("Cempans and oder herenics ");
	modernenglish.push_back("can do basic attacks");
	yeoldeanglish.push_back("con don felcsop aflygens");
	modernenglish.push_back("within range, or perform ");
	yeoldeanglish.push_back("innan underwierpest, sam aefnan");
	modernenglish.push_back("their special Abilities ");
	yeoldeanglish.push_back("hira swaes Craeft ");
	modernenglish.push_back("-Action Points-");
	yeoldeanglish.push_back("-Daed Bronds-");
	modernenglish.push_back("Action Point, or AP,");
	yeoldeanglish.push_back("Daed Brond, sam AP,");
	modernenglish.push_back("is your central focus");
	yeoldeanglish.push_back("is ger middel fustrendel");
	modernenglish.push_back("for how to move and ");
	yeoldeanglish.push_back("for hu od onstyrian and");
	modernenglish.push_back("what to attack. ");
	yeoldeanglish.push_back("hwaet od aflygen. ");
	modernenglish.push_back("Every action costs AP");
	yeoldeanglish.push_back("Aelc daed deores AP");
	modernenglish.push_back("-Losing/Winning the Game-");
	yeoldeanglish.push_back("-Leosaning/Wyrcaning se Gamen-");
	modernenglish.push_back("Player can Win or");
	yeoldeanglish.push_back("Gliwiend con Wyrcan sam");
	modernenglish.push_back("lose the game by");
	yeoldeanglish.push_back("leosan se gamen purh");
	modernenglish.push_back("Defeating the ");
	yeoldeanglish.push_back("sigeleasing se");
	modernenglish.push_back("enemy Champion or ");
	yeoldeanglish.push_back("feond Cempan sam");
	modernenglish.push_back("Destroying the");
	yeoldeanglish.push_back("Getaning se");
	modernenglish.push_back("enemy base ");
	yeoldeanglish.push_back("feond syll");
	//how-to controls
	modernenglish.push_back("Xbox Controls");
	yeoldeanglish.push_back("Xboxe Gewealds");
	modernenglish.push_back("Arcade Controls");
	yeoldeanglish.push_back("Arceade Gewealds");
	modernenglish.push_back("Accept");
	yeoldeanglish.push_back("Clyppan");
	modernenglish.push_back("Cancel/Deselect");
	yeoldeanglish.push_back("Unde/Deaceosan");
	modernenglish.push_back("End Phase/Turn");
	yeoldeanglish.push_back("Ende Tacnung/Cierr");
	modernenglish.push_back("Pause Menu");
	yeoldeanglish.push_back("Stand Menue");
	modernenglish.push_back("Champions Only:");
	yeoldeanglish.push_back("Cempans Anga:");
	modernenglish.push_back("Get/Change spell");
	yeoldeanglish.push_back("Onfon/Wrixlan galdru");
	modernenglish.push_back("Champions Only: Get/Change spell");
	yeoldeanglish.push_back("Cempans Anga: Onfon/Wrixlan galdru");
	modernenglish.push_back("Move Cursor");
	yeoldeanglish.push_back("Faer Cursore");
	modernenglish.push_back("Move camera ");
	yeoldeanglish.push_back("Faer camerae");
	modernenglish.push_back("Cycle through Units ");
	yeoldeanglish.push_back("Hring pugh Herenics ");
	modernenglish.push_back("Keyboard Controls");
	yeoldeanglish.push_back("Keyboarde Gewealds");
	//level descriptions
	modernenglish.push_back("20x20: Take your calvary and crush your enemies");
	yeoldeanglish.push_back("20x20: Niman eower Eored and brytan feond");
	modernenglish.push_back("20x20: Infiltrate the enemy's castle and destory it");
	yeoldeanglish.push_back("20x20: Snican an feond's castel and abreodan hit");
	modernenglish.push_back("30x30: Defend  aganist an onslaught of enemies");
	yeoldeanglish.push_back("30x30: Amundian fram ever gudraes sylfum feond");
	modernenglish.push_back("10x10: Fight for Ownership of tiny island");
	yeoldeanglish.push_back("10x10: aetfeohtan for agnung sylfum smael aeg");
	modernenglish.push_back("Looks kinda cold here.");
	yeoldeanglish.push_back("Beseons cynna cald hider.");
	modernenglish.push_back("Looks like both sides have some losses. Maybe you can turn those into gains.");
	yeoldeanglish.push_back("Beseons gelic begen healfs ag sum lyres. Acumendlic ge con cierr pa in earnians.");
	modernenglish.push_back("Hmm... I wonder if you can get to those islands.");
	yeoldeanglish.push_back("Hmm... Ic wundur gif ge con onfon od pa ealands.");
	modernenglish.push_back("Be careful, there's not a lot of space to fight here.");
	yeoldeanglish.push_back("Beon behogod, paer's ne ever monegum of hwil to winnan hider.");

	modernenglish.push_back("Cost: Metal - 20, Wood - 0, Population - 1");
	yeoldeanglish.push_back("Be�dland: Wecg - 20, Acholt - 0, Eor�waru - 1");
	modernenglish.push_back("Cost: Metal - 20, Wood - 20, Population - 2");
	yeoldeanglish.push_back("Be�dland: Wecg - 20, Acholt - 20, Eorowaru - 2");
	modernenglish.push_back("Cost: Metal - 5, Wood - 15, Population - 1");
	yeoldeanglish.push_back("Beodland: Wecg - 5, Acholt - 15, Eorowaru - 1");

	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-056
	// BUG FIX START
	/////////////////////////////////////////////////////////////////
	modernenglish.push_back("Elemental");
	yeoldeanglish.push_back("Andefn ");

	modernenglish.push_back("Physical");
	yeoldeanglish.push_back("Nearunes ");

	modernenglish.push_back("Support");
	yeoldeanglish.push_back("Andwist");

	modernenglish.push_back("Epic");
	yeoldeanglish.push_back("Epic");
	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-056
	/////////////////////////////////////////////////////////////////

	//game mode
	modernenglish.push_back("Tutorial");
	yeoldeanglish.push_back("Fosteraeder");

	modernenglish.push_back("Multi Player");
	yeoldeanglish.push_back("Monegum  Onspillend");

	modernenglish.push_back("Single Player");
	yeoldeanglish.push_back("Anfeald Onspillend");

	//movement phase
	//
	modernenglish.push_back(" Movement Phase");
	yeoldeanglish.push_back(" Onstyrenes Tacnungs");
	// 
	/////////////////////////////////////////////////////////////////
	// BUG FIX
	// Reference Bug # BB-036
	// BUG FIX START
	/////////////////////////////////////////////////////////////////
	modernenglish.push_back("Defeated"); // added this string...
	yeoldeanglish.push_back("Sigeled"); // ...and this string to the string tables
	/////////////////////////////////////////////////////////////////
	// BUG FIX END  Reference # BB-036
	/////////////////////////////////////////////////////////////////
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
std::string StringTable::GetString(std::string tempstring, bool ability)
{
	if(IsItModern)
	{
		for(std::vector<int>::size_type i = 0; i != yeoldeanglish.size(); i++)
		{
			if(yeoldeanglish[i] == tempstring)
			{
				return modernenglish[i];
			}
			else if( modernenglish[i] == tempstring )
				return modernenglish[i];
		}
	}
	else
	{
		for(std::vector<int>::size_type i = 0; i != modernenglish.size(); i++)
		{
			if(modernenglish[i] == tempstring)
			{
				return yeoldeanglish[i];
			}
			else if( yeoldeanglish[i] == tempstring )
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