#include "stdafx.h"
#include "../../GA_Library/GA_Library/GA_Library.h"
#include "SA_UC.h"

/// Training Menu
void trainingMenu(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// info
			break;
		case 2:
			// manage
			break;
		case 3:
			// do
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}

/// Training Info
// Displays gym stats
void displayGymStats()
{
	return;
}

/// Manage Training
// -Combos
void manageCombos(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		// -(CVMD)
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			/// create combo
			// choose asg(s)
			// choose assist(s)
			// choose target(s)
			
			// build combo
			// // type: blockstring, normal, counter-hit
			// // starting relative position: close, neutral, full-screen, corner advantage, corner disadvantage
			// // starting player state: standing, jumping, super-jump, PBGC, knockdown/tech, stunt double, in first move (for armor, invuln)
			// // starting opponent state: standing, jumping, super-jump, PBGC, knockdown/tech, hard-knockdown, crumple
			// // move input: normal, special, super, stunt double
			// // // apply move markers: cancel into ->, IPSb, ...?
			// // // normal -> normal (same class/button with special marker, higher class OK), special, super
			// // // special -> super
			// // // super -> DHC -> DHC
			// // end relative position:  close, neutral, full-screen, IPSb, corner advantage, corner disadvantage, ...?
			// // end opponent state:  standing, knockdown, hard-knockdown, crumple, slide (to), (away)

			// // # of supers for description

			// detect combo strength
			// // # of stages
			// // # technical marker
			
			// review combo
			// name & store combo
			break;
		case 2:
			// view combo
			break;
		case 3:
			// modify combo
			break;
		case 4:
			// delete combo
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// -Tasks
void manageTasks(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		// -(CVMD)
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// create task
			break;
		case 2:
			// view task
			break;
		case 3:
			// modify task
			break;
		case 4:
			// delete task
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// -Routines
void manageRoutines(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		// -(CVMD)
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// create routine
			break;
		case 2:
			// view routine
			break;
		case 3:
			// modify routine
			break;
		case 4:
			// delete routine
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}

/// Do Training
// -Combos
void doCombos(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		//	-(Select [1, NRS], Random [1, NRS], Chaos [1, NRS])
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// Hand pick a combo [1 or NRS]
			break;
		case 2:
			// Random pick a combo [1 or NRS]
			break;
		case 3:
			// Chaos mode a combo [1 or NRS]
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// -Tasks
void doTasks(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		//	-(Select [1, NRS], Random [1, NRS], Chaos [1, NRS])
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// Hand pick a task [1 or NRS]
			break;
		case 2:
			// Random pick a task [1 or NRS]
			break;
		case 3:
			// Chaos mode a task [1 or NRS]
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// -Routines
void doRoutines(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		// Populate the menu
		//	-(Select [1, NRS], Random [1, NRS], Randomized [1, NRS], Quick-build [1, NRS], Chaos[x] [1, NRS])
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// Hand pick a routine [1 or NRS]
			break;
		case 2:
			// Random pick a routine [1 or NRS]
			break;
		case 3:
			// Generate a randome routine [1 or NRS]
			break;
		case 4:
			// Quick-build a routine [1 or NRS]
			break;
		case 5:
			// Chaos mode routine [1 or NRS] (Note: chaos mode includes all layers of permutations)
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}


/// Scratch:
/*

Combos & tasks... different or the same?

-----
Info:
-----
# of combos in repository:
Highest damaging combo in repository:
-ASG vs Target
-Title
-Projected damage
# of IPSb Combos in repository:
Highest damaging IPSb combo in repository (incl. 1st IPSb hit):

Training tasks completed:
-Level x (when >0): y times
Training routines completed:
-Level x (when >0): y times

#1 spots on race leaderboards:
-Team
-Time
Farthest level reached in survival:
-Team
-Level
# of times Marie beaten on nightmare:

# of Quickmatch tasks performed:
# of Tutorial tasks performed:
# of Challenge tasks performed:
# of Trial tasks performed:

--------------
Combo-builder:
--------------
(choose) ASG
(choose) target
(CVMD) moveString
(CVMD) IPSb [burst bait] notes

--------------------------
Combo Strength Signifiers:
--------------------------
1 = 1-3 Stages
2 = 4 Stages
3 = 5+ Stages
1 = Technicality (complexity or Burst-Bait or reset)

----------------------
Task Level Signifiers:
----------------------
Combo strength (1-4)
# of times completed (multiplier, 1-3 = 1, 4-7 = 2, 8-10 = 3)

Distribution:
123456789
133321111

Distribution breakdown:
110 = 1
111 = 2
120 = 2
121 = 3
210 = 2
211 = 3
220 = 4
221 = 5
310 = 3
311 = 4
320 = 6
321 = 7
410 = 4
411 = 5
420 = 8
421 = 9

-----------------------------------------
Other Training Tasks & Associated Values:
-----------------------------------------
// Races/Endurance:
3 - Nightmare Story race:  User-chosen ASG [with leaderboard]
4 - Nightmare Story race:  Randomly-chosen ASG [with leaderboard]
3 - race to or through nightmare marie with a user-defined team [with leaderboard]
4 - race to or through nightmare marie with a randomly-generated team [with leaderboard]
3 - Nightmare survival with a user-defined team [with leaderboard]
4 - Nightmare survival with a randomly-generated team [with leaderboard]

1 - nightmare quickplay:  fight a user-defined team with a user-defined team
2 - nightmare quickplay:  fight a randomly-generated team with a user-defined team
3 - nightmare quickplay:  fight a randomly-generated team with a randomly-generated team

3 - Perform a double-snap combo for each of a user-defined team against a user-defined duo/trio
3 - Perform a double-snap combo for each of a user-defined team against a randomly-generated duo/trio
4 - Perform a double-snap combo for each of a randomly-generated team against a randomly-generated duo/trio

1 - Fight (using a user-chosen team) an undying Nightmare CPU (user-chosen) for 5 minutes (cumulative).
2 - Fight (using a random team) an undying Nightmare CPU (user-chosen) for 5 minutes (cumulative).
3 - Fight (using a random team) an undying Nightmare CPU (random) for 5 minutes (cumulative).

// ?
1/40 Tutorials (uneven distribution)
1/26 Challenges (1 array of 26)
1/56 Trials (4 per ASG)

*/

/// End-functions:
// Creates a training program (based on user-defined intensity) and displays the exercise(s)
void randomTrainingProgram()
{
	// Preface
	UI::clearIt();
	std::cout << "Welcome, ASG.\n";
	std::cout << "What intensity level do you wish for your training program?\n\n";
	// User selects the total score for intensity
	unsigned int intensity = UI::selector(9);
	// Exit failsafe
	if (intensity == 0)
		return;
	// Program iterates the random combination of training exercises based on user-selected intensity
	UI::clearIt();
	std::cout << "Your training regimen is to be executed as follows: \n";
	unsigned int randomListNumber = 1;
	do
	{
		// RNG
		int blip;
		do {
			blip = RandomOps::upperLimit(intensity);
		} while (!trainingLevelContent(blip));
		// Output section
		std::cout << randomListNumber << " - ";
		++randomListNumber;
		randomTrainingExercise(blip);
		std::cout << "\n\n";
		// Adjusting for continuous RNG pool selection
		intensity = intensity - blip;
		// function end
	} while (intensity > 0);
	UI::pressEnterToContinue();
}
// Displays a random training exercise h(based on user-defined intensity)
void randomTrainingExercise(unsigned int intensity)
{
	// Failsafe exit
	if (!trainingLevelContent(intensity))
	{
		std::cout << "Sorry, no training files found for intensity level " << intensity << "\n";
		return;
	}
	// All of the following code could use updating to a non-struct implimentation (less bloat)
	FileOps::Data trainingFiles;
	// set directory based on intensity
	std::string intensityString = std::to_string(intensity);
	FileOps::TargetManage::setDir(trainingFiles, "Training/" + intensityString);
	FileOps::TargetManage::setExtension(trainingFiles, "txt");
	FileOps::FileManage::setFileList(trainingFiles);
	// Selects a random file from the directory
	int trainMePlz = RandomOps::upperLimit(intensity);
	FileOps::TargetManage::setFileName(trainingFiles, trainingFiles.fileList[trainMePlz - 1]);
	// dump the contents of the randomly selected file
	FileOps::FileContent::displayFileContents(trainingFiles, false);
}

/// Tools:
// Return true/false if the training level folder contains any items
bool trainingLevelContent(unsigned int levelSelect)
{
	namespace fs = boost::filesystem;
	// Vector to store any filenames, if present
	std::vector<std::string> searchForTrainingContent;
	// Sets the current directory to the chosen level (1-9 currently supported)
	std::string levelPick = std::to_string(levelSelect);
	fs::path directory{ "Training/" + levelPick };
	fs::directory_iterator iterAgain(directory), end;
	// push any content to the vector
	for (; iterAgain != end; ++iterAgain)
	{
		std::string fileFile = iterAgain->path().filename().string();
		searchForTrainingContent.push_back(fileFile);
	}
	// check the vector for content
	if (searchForTrainingContent.size())
		return true;
	else if (!searchForTrainingContent.size())
		return false;
	// default
	return false;
}

/// Testing / in progress:
