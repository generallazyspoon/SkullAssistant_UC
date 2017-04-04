#ifndef SA_UC
#define SA_UC

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#pragma region GA_Library Forward Declarations
class Menu;
namespace FileOps
{
	struct Data;
}
#pragma endregion

#pragma region Program-specific objects
/// ASG struct declaration
struct characterInfo
{
	unsigned int index;
	std::string name;
	std::string altName;
	unsigned int moveTotal;
	std::vector<std::string> normals;
	std::vector<std::string> specials;
	std::vector<std::string> misc;
	std::vector<std::string> assistOnly;
	std::vector<std::string> moveList;
};
/// Player (both user & opponent) object.  Usage: stat management
struct Player
{
	bool writeMe;
	bool deleteMe;
	int stats[4];
	std::string clan;
	std::string name;
	std::vector<int> mainTeam;
	std::vector<int> altTeam;
	std::vector<std::string> styleNotes;	
};
#pragma endregion

#pragma region Program-specific memory elements
// ASG selection namespace
namespace ASGS
{
	extern characterInfo aSGIndex[15];
	extern characterInfo beowulf, bigBand, cerebella, doubleASG, eliza, filia, fukua, msFortune, painwheel, parasoul, peacock, roboFortune, squigly, valentine;
}
// Other program memory
namespace ProgramOnly
{
	extern Player user;
	extern std::vector<Player> playerDatabase;
	extern std::vector<std::string> chosenForDeletion;

}
#pragma endregion

/// Menu methods:
void skullAssistantMainMenu(Menu &passThrough);
void aSGMenu(Menu &passThrough);
void setMoveMenu(Menu &passThrough, characterInfo &selectedASG);
void infoChangeMenu(Menu &passThrough);
void statisticsMenu(Menu &passThrough);
void userOpponentMenu(Menu &passThrough);
void modifyStatsMenu(Menu &passThrough);
void opponentSelectMenu(Menu &passThrough, bool showClan);
void setWLDIMenu(Menu &passThrough);

/// The SkullAssistant Experience:
void skullExperience(Menu &passThrough);
void skullTips();
void skullAppreciation();
void skullBit();

/// Skullgirls Internal Database:
void populateCharDB();
void moveListPopulate(characterInfo &selectedASG);

/// Player Database Long-Term Storage I/O:
void parsePlayerFile(std::string requestedPlayer, bool user);
void populatePlayerDB(FileOps::Data &playerDirectory);
void quickSync();
void writePlayerFile(unsigned int playerIndex, bool user);
void cleanUpPlayers();
void syncOnExit();

/// Player Info Modification:
void modifyPlayerInfoMenu(Menu &passThrough, Player &xContainer);
void changeNameClan(Player &passThrough, bool name);
void changeTeam(Player &passThrough, bool mainTeam);
void displayTeamChanges(Player &passThrough, Player &newData, bool mainTeam);
void changeStyleNotes(Player &passThrough);
void displayStyleNotes(Player &passThrough, bool numbered);
void togglePlayerDeletion(Menu &passThrough);

/// Other Player Management Functions:
void userOpponent(Menu &passThrough);
void displayPlayerData(unsigned int playerIndex, bool user, bool specialTrigger);
void displayAllOpponents();
void createOpponent();

/// Statistics Management Functions:
void playerHub(Menu &passThrough);
void modifyStats(Menu &passThrough); 
void gameDataEntry();
void setWLDI(unsigned int playerIndex, unsigned int wLDI);
void resetStats(unsigned int playerIndex, bool user); 
void manualModifyStats(Menu & passThrough);
void userModifyWLDI(int wLDI);
void opponentModifyWLDI(unsigned int playerIndex, int wLDI);

/// General Tools:
unsigned int choosePlayer(Menu &passThrough, bool chooseAllOption);
void displayTeam(Player &passThrough, bool mainTeam);
void badCalculationHaiku(int first, int second);

/// DMZ:
void testing();

/// Review/Test:

/// In progress:
// Training:
void trainingMenu(Menu &passThrough);

void displayGymStats();

void manageCombos(Menu &passThrough);
void manageTasks(Menu &passThrough);
void manageRoutines(Menu &passThrough);

void doCombos(Menu &passThrough);
void doTasks(Menu &passThrough);
void doRoutines(Menu &passThrough);

void randomTrainingProgram();
void randomTrainingExercise(unsigned int intensity);
bool trainingLevelContent(unsigned int levelSelect);

struct Combo
{
	// info (as displayed in "view", not "create")
	std::string name;
	std::vector<int> userTeam;
	std::vector<int> opponentTeam;
	std::string comboType;
	std::string startingPosition;
	std::string startingUserState;
	std::string startingOpponentState;
	std::vector<unsigned int> moveSequence;
	std::string endingPosition;
	std::string endingOpponentstate;
	unsigned int meterRequired;
	std::vector<std::string> otherNotes;

	// metrics
	unsigned int comboStage;
	bool technical;
};
// speculative:
struct fightMove
{
	std::vector<bool> startup;
	std::vector<bool> active;
	std::vector<bool> recovery;
	std::vector<bool> totallyInvulnerable;
	std::vector<bool> grabInvunerable;
	std::vector<bool> armor;
	std::vector<bool> tripVulnerable;
	std::vector<bool> reStand;
	bool wallBounce;
	bool slide;
	bool knockdown;
	bool hardKnockdown;
	bool techableThrow;
	bool commandThrow;
	bool grabOnHit;
	bool goesAirborne;
	bool selfKnockdown;
	unsigned int normalStrength;
	bool special;
	bool super;
	bool snapback;
};

/// Placeholder(s):

/// Graveyard:

#endif