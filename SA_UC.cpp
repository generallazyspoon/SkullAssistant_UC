/// Program Information:
// Title:
// -SkullAssistant - Updated Code
//
// Note:
// -The GA_Library is being integrated.  It will help modernize the code.
//
// Purpose:
// -The SkullAssistant program is designed to act as a helper tool for Skullgirls players.  It is designed to track
//	player stats in competitive play and aid in training the player by various methods.
//

/// Main Development Info:
// -Character Database:							Currently working as intended
// -User & Opponent Info Modification:			Working as intended.  UI optimizations pending.
// -Competitive Stat Tracking:					Working as intended.  UI optimizations pending.
// -SkullTips:									Using FileOps::FileContent::ListManage.  
// -SkullAppreciation:							Using FileOps::FileContent::ListManage.  ListManage could use updating.
// -Training:									In progress.  Some functions completed.  UI optimizations pending.

/// Feature Requests:
// --Multiple users (each with different opponent sets)
//   Include a local-user recognition protocol (Bill & Jane are siblings.  They both use the same PC for games.
//	(The program recognizes when Bill & Jane are both playing together and modifies stats accordingly)
//	[This is possible if you use a Player ID system and parse a line "Stat:  [ID], [Wins], [Losses], [Draws], [Interrupts]
//	 and pass it into a struct in the Player object (just like style notes)]
// -Character Database Update:					Use FileOps::DBManagement with character files, parsing data into 
//		sub-structs (incluing frame data, etc)
// -Colors for chosen teams... console reflects color choices? would be neat...
// -Toggle all players for deletion
// -Toggle all players for undeletion
// -Toggle all players current deletion status

/// Main Development Tasks:
// -UI unification ([titles], \n, selector, getField, pressEnterToContinue, clearIt)
// -Training mode

#include "stdafx.h"
#include "../../GA_Library/GA_Library/GA_Library.h"
#include "SA_UC.h"

// Program Memory
namespace ProgramOnly
{
	// The user
	extern Player user = { false, false, 0 , 0 , 0 , 0 , "" , "" ,{ 0, 0 } ,{ 0, 0 } ,{ "" } };
	// Opponents to the user
	extern std::vector<Player> playerDatabase = {};
	// Opponent cleanup on exit
	extern std::vector<std::string> chosenForDeletion = {};
}

// main
int main()
{
	// Populate the ASG index (necessary to parse user files)
	populateCharDB();

	// Populates the user & player structs:
	parsePlayerFile("User", true);
	FileOps::Data playerDirectory;
	populatePlayerDB(playerDirectory); 

	// Main Menu
	Menu thisMenu;
	unsigned int menu1;
	do {
		UI::clearIt();
		std::cout << "Main Menu" << "\n\n";
		skullAssistantMainMenu(thisMenu);
		thisMenu.displayMenu();
		menu1 = UI::selector(thisMenu.choices.size());
		switch (menu1)
		{
		case 0:
			UI::clearIt(); 
			std::cout << "As you wish...\n";
			syncOnExit();
			break;
		case 1:
			playerHub(thisMenu);
			break;
		case 2:
			DebugTools::consoleDebugMarker("This area under construction.");
			break;
		case 3:
			skullExperience(thisMenu);
			break;
		case 4:
			testing();
			break;
		case 5:
			UI::clearIt();
			std::cout << "As you wish...\n";
			break;
		}
	} while (menu1 != 0 && menu1 < thisMenu.choices.size());
	return 0;
}