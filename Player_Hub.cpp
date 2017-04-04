#include "stdafx.h"
#include "../../GA_Library/GA_Library/GA_Library.h"
#include "SA_UC.h"

/// Player Database Long-Term Storage I/O:
// Reads a player file and pushes it into program memory
void parsePlayerFile(std::string requestedPlayer, bool user)
{
	FileOps::Data focus;
	if (user)
		FileOps::TargetManage::setDir(focus, "User");
	else if (!user)
		FileOps::TargetManage::setDir(focus, "Players");
	FileOps::TargetManage::setFileName(focus, requestedPlayer);
	FileOps::TargetManage::setExtension(focus, "plr");
	FileOps::DBManage::smartBuffer(focus);

	// filters for data types
	Player xContainer;
	xContainer.writeMe = false;
	xContainer.deleteMe = false;
	for (unsigned int x = 0; x < focus.infoDatabase.size(); x++)
	{
		if (focus.infoDatabase[x].dataType == "Clan")
			xContainer.clan = focus.infoDatabase[x].data[0];
		else if (focus.infoDatabase[x].dataType == "Name")
			xContainer.name = focus.infoDatabase[x].data[0];
		else if (focus.infoDatabase[x].dataType == "Main Team")
			xContainer.mainTeam = GA_Misc::parseInts(focus.infoDatabase[x].data[0]);
		else if (focus.infoDatabase[x].dataType == "Alternate Team")
			xContainer.altTeam = GA_Misc::parseInts(focus.infoDatabase[x].data[0]);
		else if (focus.infoDatabase[x].dataType == "Wins")
			xContainer.stats[0] = std::stoi(focus.infoDatabase[x].data[0], nullptr, 10);
		else if (focus.infoDatabase[x].dataType == "Losses")
			xContainer.stats[1] = std::stoi(focus.infoDatabase[x].data[0], nullptr, 10);
		else if (focus.infoDatabase[x].dataType == "Draws")
			xContainer.stats[2] = std::stoi(focus.infoDatabase[x].data[0], nullptr, 10);
		else if (focus.infoDatabase[x].dataType == "Interrupts")
			xContainer.stats[3] = std::stoi(focus.infoDatabase[x].data[0], nullptr, 10);
		else if (focus.infoDatabase[x].dataType == "Style")
			for (unsigned int y = 0; y < focus.infoDatabase[x].data.size(); y++)
				xContainer.styleNotes.push_back(focus.infoDatabase[x].data[y]);
	}
	bool playerKnown = false;
	unsigned int playerPosition;
	if (ProgramOnly::playerDatabase.size() > 0)
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
			if (xContainer.name == ProgramOnly::playerDatabase[x].name)
			{
				playerKnown = true;
				playerPosition = x;
			}
	// adds the user to the program memory
	if (user)
		ProgramOnly::user = xContainer;
	// adds the opponent to the program memory
	else if (!user && !playerKnown)
		ProgramOnly::playerDatabase.push_back(xContainer);
	else if (!user && playerKnown)
		ProgramOnly::playerDatabase[playerPosition] = xContainer;
}
// Function to read all player files
void populatePlayerDB(FileOps::Data &playerDirectory)
{
	UI::clearIt();
	std::cout << "Populating opponent database... ";
	FileOps::TargetManage::setDir(playerDirectory, "Players");
	FileOps::TargetManage::setExtension(playerDirectory, "plr");
	FileOps::FileManage::setFileList(playerDirectory);
	for (unsigned int a = 0; a < playerDirectory.fileList.size(); a++)
		parsePlayerFile(playerDirectory.fileList[a], false);
	std::cout << playerDirectory.fileList.size() << " ...opponents found!";
	UI::pressEnterToContinue();
}
// User is prompted to save user, save unmarked opponents, and delete marked opponents 
void quickSync()
{
	UI::clearIt();
	std::cout << "QuickSync Menu" << "\n\n";
	// generate player sync list
	std::vector<std::string> syncThesePlayers = {};
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		if (ProgramOnly::playerDatabase[x].writeMe && !ProgramOnly::playerDatabase[x].deleteMe)
			syncThesePlayers.push_back(ProgramOnly::playerDatabase[x].name);
	if (syncThesePlayers.size() == 0)
		syncThesePlayers.push_back("None.");
	// generate player cleanup list
	std::vector<std::string> deleteThesePlayers = {};
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		if (ProgramOnly::playerDatabase[x].deleteMe && !ProgramOnly::playerDatabase[x].writeMe)
			deleteThesePlayers.push_back(ProgramOnly::playerDatabase[x].name);
	if (deleteThesePlayers.size() == 0)
		deleteThesePlayers.push_back("None.");
	// perform sync operation
	std::cout << "Sync all players and perform cleanup ";
	bool quickSyncIt = UI::yesNo();
	if (quickSyncIt)
	{
		// User sync
		if (ProgramOnly::user.writeMe)
		{
			writePlayerFile(0, true);
			std::cout << "\nWrote user.\n";
		}
		else if (!ProgramOnly::user.writeMe)
			std::cout << "\nNo changes detected in user profile.\n";
		// Opponent sync
		for (unsigned int z = 0; z < ProgramOnly::playerDatabase.size(); z++)
			if (!ProgramOnly::playerDatabase[z].deleteMe && ProgramOnly::playerDatabase[z].writeMe)
				writePlayerFile(z, false);
		std::cout << "\nWrote these players:\n";
		for (unsigned int y = 0; y < syncThesePlayers.size(); y++)
			std::cout << y + 1 << ". " << syncThesePlayers[y] << "\n";
		// Opponent cleanup
		cleanUpPlayers(); // <-- did it here
		std::cout << "\nDeleted these players:\n";
		for (unsigned int y = 0; y < deleteThesePlayers.size(); y++)
			std::cout << y + 1 << ". " << deleteThesePlayers[y] << "\n";
		// End
		std::cout << "\nThese changes can not be undone.";
		UI::pressEnterToContinue();
	}
	if (!quickSyncIt)
	{
		UI::clearIt();
		std::cout << "Aborting sync.";
		UI::pressEnterToContinue();
	}
}
// Reads user or opponent data from program memory and pushes it into long-term storage
void writePlayerFile(unsigned int playerIndex, bool user)
{
	if (user)
	{
		std::ofstream writingUser("User/User.plr");
		writingUser << "Name:  " << ProgramOnly::user.name << "\n";
		writingUser << "Clan:  " << ProgramOnly::user.clan << "\n";
		std::string mainTeam;
		for (unsigned int x = 0; x < ProgramOnly::user.mainTeam.size(); x++)
		{
			mainTeam += std::to_string(ProgramOnly::user.mainTeam[x]);
			mainTeam += ", ";
		}
		writingUser << "Main Team:  " << mainTeam << "\n";
		std::string alternateTeam;
		for (unsigned int x = 0; x < ProgramOnly::user.altTeam.size(); x++)
		{
			alternateTeam += std::to_string(ProgramOnly::user.altTeam[x]);
			alternateTeam += ", ";
		}
		writingUser << "Alternate Team:  " << alternateTeam << "\n";
		writingUser << "Wins:  " << ProgramOnly::user.stats[0] << "\n";
		writingUser << "Losses:  " << ProgramOnly::user.stats[1] << "\n";
		writingUser << "Draws:  " << ProgramOnly::user.stats[2] << "\n";
		writingUser << "Interrupts:  " << ProgramOnly::user.stats[3] << "\n";
		for (unsigned int stylesCounter = 0; stylesCounter < ProgramOnly::user.styleNotes.size(); stylesCounter++)
			writingUser << "Style:  " << ProgramOnly::user.styleNotes[stylesCounter] << "\n";
		writingUser.close();
		ProgramOnly::user.writeMe = false;
	}
	else if (!user)
	{
		std::ofstream writingPlayer("Players/" + ProgramOnly::playerDatabase[playerIndex].name + ".plr");
		writingPlayer << "Name:  " << ProgramOnly::playerDatabase[playerIndex].name << "\n";
		writingPlayer << "Clan:  " << ProgramOnly::playerDatabase[playerIndex].clan << "\n";
		std::string mainTeam;
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase[playerIndex].mainTeam.size(); x++)
		{
			mainTeam += std::to_string(ProgramOnly::playerDatabase[playerIndex].mainTeam[x]);
			mainTeam += ", ";
		}
		writingPlayer << "Main Team:  " << mainTeam << "\n";
		std::string alternateTeam;
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase[playerIndex].altTeam.size(); x++)
		{
			alternateTeam += std::to_string(ProgramOnly::playerDatabase[playerIndex].altTeam[x]);
			alternateTeam += ", ";
		}
		writingPlayer << "Alternate Team:  " << alternateTeam << "\n";
		writingPlayer << "Wins:  " << ProgramOnly::playerDatabase[playerIndex].stats[0] << "\n";
		writingPlayer << "Losses:  " << ProgramOnly::playerDatabase[playerIndex].stats[1] << "\n";
		writingPlayer << "Draws:  " << ProgramOnly::playerDatabase[playerIndex].stats[2] << "\n";
		writingPlayer << "Interrupts:  " << ProgramOnly::playerDatabase[playerIndex].stats[3] << "\n";
		for (unsigned int stylesCounter = 0; stylesCounter < ProgramOnly::playerDatabase[playerIndex].styleNotes.size(); stylesCounter++)
			writingPlayer << "Style:  " << ProgramOnly::playerDatabase[playerIndex].styleNotes[stylesCounter] << "\n";
		writingPlayer.close();
		parsePlayerFile(ProgramOnly::playerDatabase[playerIndex].name, false);
		ProgramOnly::playerDatabase[playerIndex].writeMe = false;
	}
}
// removes playerDatabase modEntries & files marked for deletion
void cleanUpPlayers()
{
	FileOps::Data fileDelete;
	FileOps::TargetManage::setDir(fileDelete, "Players");
	FileOps::TargetManage::setExtension(fileDelete, "plr");
	int adjustmentMarker = 0;
	unsigned int totalCleanedUp = 0;
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		if (ProgramOnly::playerDatabase[x].deleteMe && !ProgramOnly::playerDatabase[x].writeMe)
		{
			FileOps::TargetManage::setFileName(fileDelete, ProgramOnly::playerDatabase[x].name);
			ProgramOnly::playerDatabase.erase(ProgramOnly::playerDatabase.begin() + x + adjustmentMarker);
			adjustmentMarker--;
			FileOps::FileManage::deleteFile(fileDelete, false);
			totalCleanedUp++;
		}
	if (totalCleanedUp > 0)
		std::cout << "\nCleaned up " << totalCleanedUp << " opponents OK!...\n";
}
// writes all user & opponent data to long-term storage
void syncOnExit()
{
	if (ProgramOnly::user.writeMe)
	{
		writePlayerFile(0, true);
		std::cout << "Sync user data OK!...\n";
	}
	std::vector<unsigned int> writeQueue = {};
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		if (ProgramOnly::playerDatabase[x].writeMe && !ProgramOnly::playerDatabase[x].deleteMe)
			writeQueue.push_back(x);
	if (writeQueue.size() > 0)
	{
		for (unsigned int a = 0; a < writeQueue.size(); a++)
			writePlayerFile(writeQueue[a], false);
		cleanUpPlayers();
		std::cout << "Sync opponent files OK!...\n";
	}
	std::vector<std::string> limboList = {};
	for (unsigned int y = 0; y < ProgramOnly::playerDatabase.size(); y++)
		if (ProgramOnly::playerDatabase[y].writeMe && ProgramOnly::playerDatabase[y].deleteMe)
			limboList.push_back(ProgramOnly::playerDatabase[y].name);
	if (limboList.size() > 0)
	{
		std::cout << "Caught these players in limbo (delete + write flags both TRUE):\n";
		for (unsigned int z = 0; z < limboList.size(); z++)
			std::cout << z + 1 << ". " << limboList[z] << "\n";
	}
}

/// Player Info Modification:
// Modify player information including name, clan, teams, & style notes
void modifyPlayerInfoMenu(Menu &passThrough, Player &xContainer)
{
	unsigned int thisMenuSelection;
	do {
		if (ProgramOnly::user.name == xContainer.name)
			displayPlayerData(0, true, true);
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
			if (ProgramOnly::playerDatabase[x].name == xContainer.name
				&& ProgramOnly::playerDatabase[x].clan == xContainer.clan)
				displayPlayerData(x, false, false);
		std::cout << "\nPlease select a field to modify:\n"; 
		infoChangeMenu(passThrough);
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			return;
		case 1:
			UI::clearIt();
			changeNameClan(xContainer, true);
			break;
		case 2:
			UI::clearIt();
			changeNameClan(xContainer, false);
			break;
		case 3:
			UI::clearIt();
			changeTeam(xContainer, true);
			break;
		case 4:
			UI::clearIt();
			changeTeam(xContainer, false);
			break;
		case 5:
			UI::clearIt();
			changeStyleNotes(xContainer);
			UI::pressEnterToContinue();
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// Changes the name or clan of a provided player
void changeNameClan(Player &passThrough, bool name)
{
	Player newData;
	if (name)
	{
		std::cout << "Change Name" << "\n\n";
		std::cout << "Old name:  " << passThrough.name << "\n"
			<< "New name (enter 0 to go back):  "; newData.name = UI::getField(true);
		if (newData.name == "0")
		{
			UI::clearIt();
			std::cout << "No changes made.";
			UI::pressEnterToContinue();
			return;
		}
		if (newData.name != passThrough.name && UI::commitChanges())
			passThrough.name = newData.name;
	}
	else if (!name)
	{
		std::cout << "Change Clan" << "\n\n";
		std::cout << "Old clan:  " << passThrough.clan << "\n"
			<< "New clan (enter 0 to go back):  "; newData.clan = UI::getField(true);
		if (newData.clan == "0")
		{
			UI::clearIt();
			std::cout << "No changes made.";
			UI::pressEnterToContinue();
			return;
		}
		if (newData.clan != passThrough.clan && UI::commitChanges())
			passThrough.clan = newData.clan;
	}
	passThrough.writeMe = true;
}
// changes the team for a provided player
void changeTeam(Player &passThrough, bool mainTeam)
{
	Player newData;
	Menu thisMenu;
	unsigned int teamSizer;
	unsigned int tempASGSelect;
	unsigned int tempAssistSelect;
	bool commit;

	if (mainTeam)
	{
		UI::clearIt();
		std::cout << "Change Main Team" << "\n\n";
		std::cout << "Current main team for " + passThrough.name + ":\n";
		displayTeam(passThrough, true);
		std::cout << "\nSelect a new main team size.\n";
		teamSizer = UI::selector(3);
		newData.mainTeam = { 0, 0, 0, 0, 0, 0 };
		switch (teamSizer)
		{
		case 0:
		{
			// Get outa heeah
			return;
		}
		case 1:
		{
			// Display the team comparison
			displayTeamChanges(passThrough, newData, true);
			// Acquire an ASG from the user
			std::cout << "\nSelect an ASG:\n";
			thisMenu.clearMenu();
			aSGMenu(thisMenu);
			thisMenu.displayMenu();
			tempASGSelect = UI::selector(14);
			// exit if 0
			if (tempASGSelect == 0)
				break;
			// buffer any selected ASG
			newData.mainTeam[0] = tempASGSelect;
			break;
		}
		case 2:
		{
			// 
			for (unsigned int aSGPosition = 0; aSGPosition < 4; aSGPosition = aSGPosition + 2)
			{
				// Display the team comparison
				displayTeamChanges(passThrough, newData, true);
				// Acquire an ASG from the user
				std::cout << "\nSelect an ASG:\n";
				thisMenu.clearMenu();
				aSGMenu(thisMenu);
				thisMenu.displayMenu();
				tempASGSelect = UI::selector(14);
				// exit if 0
				if (tempASGSelect == 0)
					break;
				// buffer any selected ASG
				newData.mainTeam[aSGPosition] = tempASGSelect;
				// Display the team comparison
				displayTeamChanges(passThrough, newData, true);
				// Acquire an assist from the user
				std::cout << "Select an assist for " + ASGS::aSGIndex[tempASGSelect].name + ":\n";
				thisMenu.clearMenu();
				setMoveMenu(thisMenu, ASGS::aSGIndex[tempASGSelect]);
				thisMenu.displayMenu();
				tempAssistSelect = UI::selector(thisMenu.choices.size());
				// exit if 0
				if (tempAssistSelect == 0)
					break;
				// buffer any selected assist
				newData.mainTeam[aSGPosition + 1] = tempAssistSelect;
			}
			break;
		}
		case 3:
		{
			// 
			for (unsigned int aSGPosition = 0; aSGPosition < 6; aSGPosition = aSGPosition + 2)
			{
				// Display the team comparison
				displayTeamChanges(passThrough, newData, true);
				// Acquire an ASG from the user
				std::cout << "\nSelect an ASG:\n";
				thisMenu.clearMenu();
				aSGMenu(thisMenu);
				thisMenu.displayMenu();
				tempASGSelect = UI::selector(14);
				// exit if 0
				if (tempASGSelect == 0)
					break;
				// buffer any selected ASG
				newData.mainTeam[aSGPosition] = tempASGSelect;
				// Display the team comparison
				displayTeamChanges(passThrough, newData, true);
				// Acquire an assist from the user
				std::cout << "Select an assist for " + ASGS::aSGIndex[tempASGSelect].name + ":\n";
				thisMenu.clearMenu();
				setMoveMenu(thisMenu, ASGS::aSGIndex[tempASGSelect]);
				thisMenu.displayMenu();
				tempAssistSelect = UI::selector(thisMenu.choices.size());
				// exit if 0
				if (tempAssistSelect == 0)
					break;
				// buffer any selected assist
				newData.mainTeam[aSGPosition + 1] = tempAssistSelect;
			}
			break;
		}
		default:
		{
			// Shouldn't be here
			break;
		}
		}
		// Display the team comparison
		displayTeamChanges(passThrough, newData, true);
		// exit if no changes were made
		if (passThrough.mainTeam == newData.mainTeam)
		{
			std::cout << "No changes detected.\n";
			UI::pressEnterToContinue();
			return;
		}
		// confirm any present changes
		commit = UI::commitChanges();
		// exit if user denies commit
		if (!commit)
		{
			std::cout << "\n\nChanges ignored.\n";
			UI::pressEnterToContinue();
			return;
		}
		// write if user commits
		else if (commit)
		{
			passThrough.mainTeam = newData.mainTeam;
			std::cout << "\n\nChanges applied.\n";
			UI::pressEnterToContinue();
			return;
		}
	}
	if (!mainTeam)
	{
		UI::clearIt();
		std::cout << "Change Alternate Team" << "\n\n";
		std::cout << "Current alternate team for " + passThrough.name + ":\n";
		displayTeam(passThrough, false);
		std::cout << "\nSelect a new main team size.\n";
		teamSizer = UI::selector(3);
		newData.altTeam = { 0, 0, 0, 0, 0, 0 };
		switch (teamSizer)
		{
		case 0:
		{
			// Get outa heeah
			return;
		}
		case 1:
		{
			// Display the team comparison
			displayTeamChanges(passThrough, newData, false);
			// Acquire an ASG from the user
			std::cout << "\nSelect an ASG:\n";
			thisMenu.clearMenu();
			aSGMenu(thisMenu);
			thisMenu.displayMenu();
			tempASGSelect = UI::selector(14);
			// exit if 0
			if (tempASGSelect == 0)
				break;
			// buffer any selected ASG
			newData.altTeam[0] = tempASGSelect;
			break;
		}
		case 2:
		{
			// 
			for (unsigned int aSGPosition = 0; aSGPosition < 4; aSGPosition = aSGPosition + 2)
			{
				// Display the team comparison
				displayTeamChanges(passThrough, newData, false);
				// Acquire an ASG from the user
				std::cout << "\nSelect an ASG:\n";
				thisMenu.clearMenu();
				aSGMenu(thisMenu);
				thisMenu.displayMenu();
				tempASGSelect = UI::selector(14);
				// exit if 0
				if (tempASGSelect == 0)
					break;
				// buffer any selected ASG
				newData.altTeam[aSGPosition] = tempASGSelect;
				// Display the team comparison
				displayTeamChanges(passThrough, newData, false);
				// Acquire an assist from the user
				std::cout << "Select an assist for " + ASGS::aSGIndex[tempASGSelect].name + ":\n";
				thisMenu.clearMenu();
				setMoveMenu(thisMenu, ASGS::aSGIndex[tempASGSelect]);
				thisMenu.displayMenu();
				tempAssistSelect = UI::selector(thisMenu.choices.size());
				// exit if 0
				if (tempAssistSelect == 0)
					break;
				// buffer any selected assist
				newData.altTeam[aSGPosition + 1] = tempAssistSelect;
			}
			break;
		}
		case 3:
		{
			// 
			for (unsigned int aSGPosition = 0; aSGPosition < 6; aSGPosition = aSGPosition + 2)
			{
				// Display the team comparison
				displayTeamChanges(passThrough, newData, false);
				// Acquire an ASG from the user
				std::cout << "\nSelect an ASG:\n";
				thisMenu.clearMenu();
				aSGMenu(thisMenu);
				thisMenu.displayMenu();
				tempASGSelect = UI::selector(14);
				// exit if 0
				if (tempASGSelect == 0)
					break;
				// buffer any selected ASG
				newData.altTeam[aSGPosition] = tempASGSelect;
				// Display the team comparison
				displayTeamChanges(passThrough, newData, false);
				// Acquire an assist from the user
				std::cout << "Select an assist for " + ASGS::aSGIndex[tempASGSelect].name + ":\n";
				thisMenu.clearMenu();
				setMoveMenu(thisMenu, ASGS::aSGIndex[tempASGSelect]);
				thisMenu.displayMenu();
				tempAssistSelect = UI::selector(thisMenu.choices.size());
				// exit if 0
				if (tempAssistSelect == 0)
					break;
				// buffer any selected assist
				newData.altTeam[aSGPosition + 1] = tempAssistSelect;
			}
			break;
		}
		default:
		{
			// Shouldn't be here
			break;
		}
		}
		// Display the team comparison
		displayTeamChanges(passThrough, newData, false);
		// exit if no changes were made
		if (passThrough.altTeam == newData.altTeam)
		{
			std::cout << "No changes detected.\n";
			UI::pressEnterToContinue();
			return;
		}
		// confirm any present changes
		commit = UI::commitChanges();
		// exit if user denies commit
		if (!commit)
		{
			std::cout << "\n\nChanges ignored.\n";
			UI::pressEnterToContinue();
			return;
		}
		// write if user commits
		else if (commit)
		{
			passThrough.altTeam = newData.altTeam;
			std::cout << "\n\nChanges applied.\n";
			UI::pressEnterToContinue();
			return;
		}
	}
}
// Displays teamChanges (for changeTeam)
void displayTeamChanges(Player &passThrough, Player &newData, bool mainTeam)
{
	// Change the output based on mainTeam
	std::string mainOrAlt;
	if (mainTeam)
		mainOrAlt = "main";
	if (!mainTeam)
		mainOrAlt = "alternate";
	// Display the team comparison
	UI::clearIt();
	std::cout << "Review Team Change" << "\n\n";
	std::cout << "Current " + mainOrAlt + " team for " + passThrough.name + ":\n\n";
	displayTeam(passThrough, mainTeam);
	std::cout << "Proposed " + mainOrAlt + " team for " + passThrough.name + ":\n\n";
	displayTeam(newData, mainTeam);
}
// manages the style notes for a provided player
void changeStyleNotes(Player &passThrough)
{
	Menu thisMenu;
	std::string modStyleNote;
	unsigned int selectedStyleNote;
	unsigned int styleNoteAction;

	do {
		UI::clearIt();
		std::cout << "Manage style notes for " << passThrough.name << "\n\n";
		displayStyleNotes(passThrough, false);
		thisMenu.clearMenu();
		thisMenu.setMenu("Add a style note");
		thisMenu.setMenu("Modify a style note");
		thisMenu.setMenu("Delete a style note");
		thisMenu.displayMenu();
		styleNoteAction = UI::selector(thisMenu.choices.size());
		switch (styleNoteAction)
		{
		case 0:
			return;
		case 1:
			UI::clearIt();
			std::cout << "Add A Style Note" << "\n\n";
			displayStyleNotes(passThrough, false);
			std::cout << "Please enter a new style note for " << passThrough.name << "(enter 0 to go back): ";
			modStyleNote = UI::getField(false);
			if (modStyleNote == "0")
			{
				UI::clearIt();
				std::cout << "No changes made.";
				UI::pressEnterToContinue();
				break;
			}
			if (UI::commitChanges())
			{
				passThrough.styleNotes.push_back(modStyleNote);
				passThrough.writeMe = true;
			}
			break;
		case 2:
			UI::clearIt();
			std::cout << "Modify A Style Note" << "\n\n";
			displayStyleNotes(passThrough, true);
			if (passThrough.styleNotes.size() == 0)
			{
				std::cout << "No style notes to modify.";
				UI::pressEnterToContinue();
				break;
			}
			std::cout << "Select the style note you wish to modify.\n";
			selectedStyleNote = UI::selector(passThrough.styleNotes.size());
			if (selectedStyleNote == 0)
				break;
			std::cout << "Current style note: " << passThrough.styleNotes[selectedStyleNote - 1] << "\n\n";
			std::cout << "Enter a replacement style note (press enter or input 0 to go back): ";
			modStyleNote = UI::getField(false);
			if (modStyleNote == "0" || modStyleNote == "")
			{
				UI::clearIt();
				std::cout << "No changes made";
				UI::pressEnterToContinue();
				break;
			}
			if (UI::commitChanges())
			{
				passThrough.styleNotes[selectedStyleNote - 1] = modStyleNote;
				passThrough.writeMe = true;
			}
			break;
		case 3:
			UI::clearIt();
			std::cout << "Delete A Style Note" << "\n\n";
			displayStyleNotes(passThrough, true);
			if (passThrough.styleNotes.size() == 0)
			{
				std::cout << "No style notes to delete.";
				UI::pressEnterToContinue();
				break;
			}
			std::cout << "Select the style note you wish to delete.\n";
			selectedStyleNote = UI::selector(passThrough.styleNotes.size());
			if (selectedStyleNote == 0)
				break;
			if (UI::commitChanges())
				passThrough.styleNotes.erase(passThrough.styleNotes.begin() + selectedStyleNote - 1);
			break;
		default:
		{
			// shouldn't be here
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
		}
	} while (styleNoteAction != 0);
}
// Displays all the style notes on the screen, bool determines whether list is numbered
void displayStyleNotes(Player &passThrough, bool numbered)
{
	std::cout << "Current Style notes for " << passThrough.name << ":\n";
	if (numbered)
		if (passThrough.styleNotes.size() > 0)
			for (unsigned int x = 0; x < passThrough.styleNotes.size(); x++)
				std::cout << x + 1 << ". " << passThrough.styleNotes[x] << "\n";
	if (!numbered)
		if (passThrough.styleNotes.size() > 0)
			for (unsigned int x = 0; x < passThrough.styleNotes.size(); x++)
				std::cout << "\t" << passThrough.styleNotes[x] << "\n";
	std::cout << "\n";
}
// Prompts the user to mark an opponent file for deletion
void togglePlayerDeletion(Menu &passThrough)
{
	UI::clearIt();
	std::cout << "Player Deletion Menu" << "\n\n";
	std::cout << "Select player:\n";
	std::cout << "(changes applied at QuickSync and at successful program exit.)\n\n";
	unsigned int chosenPlayer = choosePlayer(passThrough, false);
	if (chosenPlayer == 0)
		return;

	UI::clearIt();
	std::cout << "Confirm Toggle Deletion" << "\n\n";
	std::cout << "You wish to toggle deletion for: " << ProgramOnly::playerDatabase[chosenPlayer - 1].name << "\n";
	if (ProgramOnly::playerDatabase[chosenPlayer - 1].deleteMe)
	{
		std::cout << "Current deletion status:\n";
		std::cout << "[x] Yes\n";
		std::cout << "[ ] No\n";
	}
	else if (!ProgramOnly::playerDatabase[chosenPlayer - 1].deleteMe)
	{
		std::cout << "Current deletion status:\n";
		std::cout << "[ ] Yes\n";
		std::cout << "[x] No\n";
	}
	bool commit = UI::commitChanges();
	if (commit)
		ProgramOnly::playerDatabase[chosenPlayer - 1].deleteMe = !ProgramOnly::playerDatabase[chosenPlayer - 1].deleteMe;
}

/// Other Player Management Functions:
// Player management portal
void userOpponent(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		std::cout << "Player Management Menu" << "\n\n";
		userOpponentMenu(passThrough);
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		unsigned int chosenPlayer;
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			// view user info
			UI::clearIt();
			displayPlayerData(0, true, false);
			UI::pressEnterToContinue();
			break;
		case 2:
			// view opponent info
			UI::clearIt();
			std::cout << "View Opponent Info Menu" << "\n\n";
			std::cout << "Choose the opponent information you would like to view:\n";
			chosenPlayer = choosePlayer(passThrough, true);
			if (chosenPlayer == 0)
				break;
			if (chosenPlayer == passThrough.choices.size())
			{
				UI::clearIt();
				std::cout << "View All Opponents" << "\n\n";
				displayAllOpponents();
				break;
			}
			UI::clearIt();
			displayPlayerData(chosenPlayer - 1, false, false);
			UI::pressEnterToContinue();
			break;
		case 3:
			// change user info
			UI::clearIt();
			modifyPlayerInfoMenu(passThrough, ProgramOnly::user);
			break;
		case 4:
			// change opponent info
			do {
				UI::clearIt();
				std::cout << "Change Opponent Info" << "\n\n";
				std::cout << "Choose the opponent whose info you would like to modify:\n";
				chosenPlayer = choosePlayer(passThrough, false);
				if (chosenPlayer == 0)
					break;
				UI::clearIt();
				modifyPlayerInfoMenu(passThrough, ProgramOnly::playerDatabase[chosenPlayer - 1]);
			} while (chosenPlayer > 0);
			break;
		case 5:
			// add opponent
			createOpponent();
			break;
		case 6:
			// toggle opponent for deletion
			togglePlayerDeletion(passThrough);
			break;
		case 7:
			// quick-sync all player elements
			quickSync();
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// Displays data for a the user or opponent (using program memory)
void displayPlayerData(unsigned int playerIndex, bool user, bool specialTrigger)
{
	// Console output
	if (user)
	{		
		if (!specialTrigger)
			std::cout << "View User Info" << "\n\n";
		else if (specialTrigger)
			std::cout << "Change User Info" << "\n\n";
		std::cout << "Name:        " << ProgramOnly::user.name << "\n";
		std::cout << "Clan:        " << ProgramOnly::user.clan << "\n";
		std::cout << "Main Team:\n";
		displayTeam(ProgramOnly::user, true);
		std::cout << "Alternate Team:\n";
		displayTeam(ProgramOnly::user, false);
		displayStyleNotes(ProgramOnly::user, false);
		float totalGames = (float)(ProgramOnly::user.stats[0] + ProgramOnly::user.stats[1] + ProgramOnly::user.stats[2] + ProgramOnly::user.stats[3]);
		float winPercentage = 0;
		float lossPercentage = 0;
		float drawPercentage = 0;
		float interruptPercentage = 0;
		if (totalGames > 0)
		{
			winPercentage = 100 * (ProgramOnly::user.stats[0] / totalGames);
			lossPercentage = 100 * (ProgramOnly::user.stats[1] / totalGames);
			drawPercentage = 100 * (ProgramOnly::user.stats[2] / totalGames);
			interruptPercentage = 100 * (ProgramOnly::user.stats[3] / totalGames);
		}
		std::cout << std::setprecision(4)
			<< "Wins:        " << ProgramOnly::user.stats[0] << "\t\t(" << winPercentage << "%)" << "\n"
			<< "Losses:      " << ProgramOnly::user.stats[1] << "\t\t(" << lossPercentage << "%)" << "\n"
			<< "Draws:       " << ProgramOnly::user.stats[2] << "\t\t(" << drawPercentage << "%)" << "\n"
			<< "Interrupts:  " << ProgramOnly::user.stats[3] << "\t\t(" << interruptPercentage << "%)" << "\n";
		std::cout << "\n";
		std::cout << "Changes have been made since last save:  ";
		if (ProgramOnly::user.writeMe)
			std::cout << "Yes\n";
		if (!ProgramOnly::user.writeMe)
			std::cout << "No\n";
	}
	else if (!user)
	{
		if (!specialTrigger)
			std::cout << "View Opponent Info" << "\n\n";
		std::cout << "Name:        " << ProgramOnly::playerDatabase[playerIndex].name << "\n";
		std::cout << "Clan:        " << ProgramOnly::playerDatabase[playerIndex].clan << "\n";
		std::cout << "Main Team:\n";
		displayTeam(ProgramOnly::playerDatabase[playerIndex], true);
		std::cout << "Alternate Team:\n";
		displayTeam(ProgramOnly::playerDatabase[playerIndex], false);
		displayStyleNotes(ProgramOnly::playerDatabase[playerIndex], false);
		float totalGames = (float)(ProgramOnly::playerDatabase[playerIndex].stats[0] + ProgramOnly::playerDatabase[playerIndex].stats[1] +
			ProgramOnly::playerDatabase[playerIndex].stats[2] + ProgramOnly::playerDatabase[playerIndex].stats[3]);
		float totalUserGames = (float)(ProgramOnly::user.stats[0] + ProgramOnly::user.stats[1] +
			ProgramOnly::user.stats[2] + ProgramOnly::user.stats[3]);
		float participationRatio = 100 * (totalGames / totalUserGames);
		float winPercentage = 0;
		float lossPercentage = 0;
		float drawPercentage = 0;
		float interruptPercentage = 0;
		if (totalGames > 0)
		{
			winPercentage = 100 * (ProgramOnly::playerDatabase[playerIndex].stats[0] / totalGames);
			lossPercentage = 100 * (ProgramOnly::playerDatabase[playerIndex].stats[1] / totalGames);
			drawPercentage = 100 * (ProgramOnly::playerDatabase[playerIndex].stats[2] / totalGames);
			interruptPercentage = 100 * (ProgramOnly::playerDatabase[playerIndex].stats[3] / totalGames);
		}
		std::cout << std::setprecision(4)
			<< "Wins:        " << ProgramOnly::playerDatabase[playerIndex].stats[0] << "\t\t(" << winPercentage << "%)" << "\n"
			<< "Losses:      " << ProgramOnly::playerDatabase[playerIndex].stats[1] << "\t\t(" << lossPercentage << "%)" << "\n"
			<< "Draws:       " << ProgramOnly::playerDatabase[playerIndex].stats[2] << "\t\t(" << drawPercentage << "%)" << "\n"
			<< "Interrupts:  " << ProgramOnly::playerDatabase[playerIndex].stats[3] << "\t\t(" << interruptPercentage << "%)" << "\n";
		if (totalGames == 0)
			participationRatio = 0;
		std::cout << std::setprecision(4)
			<< "User accounts for ~" << participationRatio << "% of games played...\n";
		std::cout << "\n";
		std::cout << "Marked for deletion upon program exit:  ";
		if (ProgramOnly::playerDatabase[playerIndex].deleteMe)
			std::cout << "Yes\n";
		if (!ProgramOnly::playerDatabase[playerIndex].deleteMe)
			std::cout << "No\n";
		std::cout << "Changes have been made since last save:  ";
		if (ProgramOnly::playerDatabase[playerIndex].writeMe)
			std::cout << "Yes\n";
		if (!ProgramOnly::playerDatabase[playerIndex].writeMe)
			std::cout << "No\n";
	}
}
// Displays data for all the opponents in program memory
void displayAllOpponents()
{
	unsigned int counter = 0;
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
	{
		displayPlayerData(x, false, true);
		if (counter == 9)
		{
			counter = 0;
			UI::pressEnterToContinue();
		}
		std::cout << "\n";
		counter++;
	}
	UI::pressEnterToContinue();
}
// Basic function to create a new user and stores the new player in the program memory
void createOpponent()
{
	// Gather new player information from the user
	UI::clearIt();
	std::cout << "Opponent Creation" << "\n\n";
	Player yContainer;
	std::cout << "Please enter a name (enter 0 to go back): ";
	yContainer.name = UI::getField(true);
	// Failsafe exit
	if (yContainer.name == "0" || yContainer.name.size() == 0)
	{
		UI::clearIt();
		std::cout << "No changes made.";
		UI::pressEnterToContinue();
		return;
	}
	std::cout << "Please enter a clan (press enter for none or 0 to go back): ";
	yContainer.clan = UI::getField(true);
	// Failsafe exit
	if (yContainer.clan == "0")
	{
		UI::clearIt();
		std::cout << "No changes made.";
		UI::pressEnterToContinue();
		return;
	}
	// Check to overwrite user
	std::cout << "Searching for user entry...\n";
	if (yContainer.name == ProgramOnly::user.name)
	{
		std::cout << "User found!  This will overwrite the existing player profile.\n";
		bool overwrite = UI::commitChanges();
		if (overwrite)
		{
			resetStats(0, true);
			ProgramOnly::user = yContainer;
			return;
		}
	}
	std::cout << "Name does not match user...\n";

	// Check to overwrite opponent
	std::cout << "Searching for Opponent entry...\n";
	for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
	{
		if (yContainer.name == ProgramOnly::playerDatabase[x].name)
		{
			std::cout << "Opponent found!  This will overwrite the existing player profile.\n";
			bool overwrite = UI::commitChanges();
			if (overwrite)
			{
				resetStats(x, false);
				ProgramOnly::playerDatabase[x] = yContainer;
				return;
			}
		}
	}
	std::cout << "Name does not match any opponents...\n";

	// Populate the struct
	for (unsigned int x = 0; x < 6; x++)
	{
		yContainer.mainTeam.push_back(0);
		yContainer.altTeam.push_back(0);
	}
	for (unsigned int y = 0; y < 4; y++)
		yContainer.stats[y] = 0;
	yContainer.writeMe = true;
	yContainer.deleteMe = false;

	// Confirm new player entry
	UI::clearIt();
	std::cout << "Name:         " << yContainer.name << "\n";
	std::cout << "Clan:         " << yContainer.clan << "\n";
	std::cout << "Main Team:\n";
	std::cout << "\tUndefined.\n";
	std::cout << "Alternate Team:\n";
	std::cout << "\tUndefined.\n";
	std::cout << "Wins:         " << yContainer.stats[0] << "\n";
	std::cout << "Losses:       " << yContainer.stats[1] << "\n";
	std::cout << "Draws:        " << yContainer.stats[2] << "\n";
	std::cout << "Interrupts:   " << yContainer.stats[3] << "\n";
	std::cout << "Style Note:   " << "\n\n";
	std::cout << "(Styles & teams may be defined in player management.)\n\n";
	bool commit = UI::commitChanges();
	if (commit)
		ProgramOnly::playerDatabase.push_back(yContainer);
}

/// Statistics Management Functions:
// Statistics management portal
void playerHub(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	do {
		UI::clearIt();
		std::cout << "Player Hub" << "\n\n";
		statisticsMenu(passThrough);
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			userOpponent(passThrough);
			break;
		case 2:
			modifyStats(passThrough);
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// General stat modification portal
void modifyStats(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	bool proceed = false;
	unsigned int chosenPlayer;
	do {
		UI::clearIt();
		std::cout << "Modify Statistics Menu" << "\n\n";
		modifyStatsMenu(passThrough);
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			break;
		case 1:
			gameDataEntry();
			break;
		case 2:
			// clear screen
			UI::clearIt();
			// display user info
			displayPlayerData(0, true, true);
			// describe the reset
			std::cout << "\nResetting user stats will also reset all opponent stats.  Continue ";
			// prompt for reset (yesNo)
			proceed = UI::yesNo();
			// reset or break
			if (proceed)
				resetStats(0, true);
			break;
		case 3:
			// clear screen
			UI::clearIt();
			std::cout << "User Stat Modification" << "\n\n";
			// prompt the user to select an opponent
			std::cout << "Please select the user whose stats you would like to reset:\n";
			chosenPlayer = choosePlayer(passThrough, true);
			if (chosenPlayer == 0)
				break;
			if (chosenPlayer == passThrough.choices.size())
			{
				UI::clearIt();
				std::cout << "Resetting ALL opponents' stats will reset ALL users stats...\n"
					<< "Continue ";
				if (UI::yesNo())
				{
					if ((std::cout << "\n\nAre you sure ", UI::yesNo()))
					{
						resetStats(0, true); // just reset the user, it's easier
						std::cout << "\n\n" << "OK, reset all stats, but did not sync/save!";
						UI::pressEnterToContinue();
						break;
					}
					break;
				}
				break;
			}
			// display user info
			displayPlayerData(chosenPlayer - 1, false, false);
			// describe the reset
			std::cout << "\nResetting opponent stats will affect user stats appropriately.  Continue ";
			// prompt for reset (yesNo)
			proceed = UI::yesNo();
			// reset or break
			if (proceed)
				resetStats(chosenPlayer - 1, false);
			break;
		case 4:
			// manual modification
			manualModifyStats(passThrough);
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// User updates their personal win/loss database on a game-by-game basis
void gameDataEntry()
{
	Menu gameEntryTime;
	unsigned int player = 0;
	// Choose opponent
	do
	{
		UI::clearIt();
		std::cout << "Game Data Entry Menu" << "\n\n";
		std::cout << "Choose your opponent:\n\n";
		opponentSelectMenu(gameEntryTime, true);
		gameEntryTime.setMenu("Add a new opponent");
		gameEntryTime.displayMenu();
		skullBit();
		player = UI::selector(gameEntryTime.choices.size());
		if (player == 0)
			return;
		if (player == gameEntryTime.choices.size())
		{
			createOpponent();
			UI::pressEnterToContinue();
		}
	} while (player == gameEntryTime.choices.size());
	unsigned int xResult = 0;
	do {
		gameEntryTime.clearMenu();
		setWLDIMenu(gameEntryTime);
		gameEntryTime.displayMenu();
		xResult = UI::selector(4);
	} while (xResult > 0);
	// set WLDI from the user's point of view
	setWLDI(player - 1, xResult - 1);
}
// Log a score
void setWLDI(unsigned int playerIndex, unsigned int wLDI)
{
	switch (wLDI)
	{
	case 0:
		// attribute win
		ProgramOnly::user.stats[0]++;
		ProgramOnly::user.writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].stats[1]++;
		ProgramOnly::playerDatabase[playerIndex].writeMe = true;
		std::cout << "\nWin recorded...\n";
		if (ProgramOnly::playerDatabase[playerIndex].deleteMe)
		{
			ProgramOnly::playerDatabase[playerIndex].deleteMe = false;
			std::cout << ProgramOnly::playerDatabase[playerIndex].name << " unmarked for deletion.\n";
		}
		UI::pressEnterToContinue();
		break;
	case 1:
		// attribute loss
		ProgramOnly::user.stats[1]++;
		ProgramOnly::user.writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].stats[0]++;
		ProgramOnly::playerDatabase[playerIndex].writeMe = true;
		std::cout << "\nLoss recorded...\n";
		if (ProgramOnly::playerDatabase[playerIndex].deleteMe)
		{
			ProgramOnly::playerDatabase[playerIndex].deleteMe = false;
			std::cout << ProgramOnly::playerDatabase[playerIndex].name << " unmarked for deletion.\n";
		}
		UI::pressEnterToContinue();
		break;
	case 2:
		// attribute draw
		ProgramOnly::user.stats[2]++;
		ProgramOnly::user.writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].stats[2]++;
		ProgramOnly::playerDatabase[playerIndex].writeMe = true;
		std::cout << "\nDraw recorded...\n";
		if (ProgramOnly::playerDatabase[playerIndex].deleteMe)
		{
			ProgramOnly::playerDatabase[playerIndex].deleteMe = false;
			std::cout << ProgramOnly::playerDatabase[playerIndex].name << " unmarked for deletion.\n";
		}
		UI::pressEnterToContinue();
		break;
	case 3:
		// attribute interrupt
		ProgramOnly::user.stats[3]++;
		ProgramOnly::user.writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].stats[3]++;
		ProgramOnly::playerDatabase[playerIndex].writeMe = true;
		std::cout << "\nInterrupt recorded...\n";
		if (ProgramOnly::playerDatabase[playerIndex].deleteMe)
		{
			ProgramOnly::playerDatabase[playerIndex].deleteMe = false;
			std::cout << ProgramOnly::playerDatabase[playerIndex].name << " unmarked for deletion.\n";
		}
		UI::pressEnterToContinue();
		break;
	default:
		// exit
		break;
	}
}
// Sets all wins, losses, draws, & interrupts to 0 for a given player (or all, if user)
void resetStats(unsigned int playerIndex, bool user)
{
	if (user)
	{
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		{
			for (unsigned int y = 0; y < 4; y++)
				ProgramOnly::playerDatabase[x].stats[y] = 0;
			ProgramOnly::playerDatabase[x].writeMe = true;
		}
		for (unsigned int z = 0; z < 4; z++)
			ProgramOnly::user.stats[z] = 0;
		ProgramOnly::user.writeMe = true;
		UI::clearIt();
		std::cout << "All stats cleared.";
		UI::pressEnterToContinue();
	}
	if (!user)
	{
		ProgramOnly::user.stats[0] = ProgramOnly::user.stats[0] - ProgramOnly::playerDatabase[playerIndex].stats[1];
		ProgramOnly::user.stats[1] = ProgramOnly::user.stats[1] - ProgramOnly::playerDatabase[playerIndex].stats[0];
		ProgramOnly::user.stats[2] = ProgramOnly::user.stats[2] - ProgramOnly::playerDatabase[playerIndex].stats[2];
		ProgramOnly::user.stats[3] = ProgramOnly::user.stats[3] - ProgramOnly::playerDatabase[playerIndex].stats[3];
		ProgramOnly::user.writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].stats[0] = 0;
		ProgramOnly::playerDatabase[playerIndex].stats[1] = 0;
		ProgramOnly::playerDatabase[playerIndex].stats[2] = 0;
		ProgramOnly::playerDatabase[playerIndex].stats[3] = 0;
		ProgramOnly::playerDatabase[playerIndex].writeMe = true;
		ProgramOnly::playerDatabase[playerIndex].deleteMe = false;
		UI::clearIt();
		std::cout << "Player stats cleared.  User stats adjusted.";
		UI::pressEnterToContinue();
	}
}
// Manual stat modification portal
void manualModifyStats(Menu &passThrough)
{
	unsigned int thisMenuSelection;
	unsigned int selectedPlayer;
	unsigned int modChoice;
	std::string amountString;
	std::vector<int> amountInt;
	bool mathError = true;
	bool commit = false;
	do {
		UI::clearIt();
		std::cout << "Modify Player Stats Menu" << "\n\n";
		passThrough.clearMenu();
		passThrough.setMenu("User");
		passThrough.setMenu("Opponents");
		passThrough.displayMenu();
		thisMenuSelection = UI::selector(passThrough.choices.size());
		switch (thisMenuSelection)
		{
		case 0:
			return;
		case 1:
			// user
			do {
				UI::clearIt();
				displayPlayerData(0, true, false);
				std::cout << "\nSelect the statistic you wish to modify:\n\n";
				passThrough.clearMenu();
				setWLDIMenu(passThrough);
				passThrough.displayMenu();
				modChoice = UI::selector(4);
				if (modChoice == 0)
					break;
				userModifyWLDI(modChoice - 1);
			} while (modChoice > 0);
			break;
		case 2:
			// opponent
			do {
				UI::clearIt();
				std::cout << "Opponent Stat modification" << "\n\n";
				std::cout << "Choose the player whose stats you wish to modify:\n\n";
				selectedPlayer = choosePlayer(passThrough, false);
				/*passThrough.clearMenu();
				for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
					passThrough.setMenu(ProgramOnly::playerDatabase[x].name);
				passThrough.displayMenu();
				selectedPlayer = UI::selector(ProgramOnly::playerDatabase.size());*/
				if (selectedPlayer == 0)
					return;
				UI::clearIt();
				displayPlayerData(selectedPlayer - 1, false, false);
				std::cout << "\nSelect the statistic you wish to modify:\n\n";
				setWLDIMenu(passThrough);
				passThrough.displayMenu();
				modChoice = UI::selector(4);
				if (modChoice == 0)
					return;
				opponentModifyWLDI(selectedPlayer - 1, modChoice - 1);
			} while (modChoice > 0);
			break;
		default:
			DebugTools::consoleDebugMarker("Warning: menu default case reached");
			break;
		}
	} while (thisMenuSelection > 0);
}
// Modify user stats with a custom value
void userModifyWLDI(int wLDI)
{
	// how much?
	std::cout << "How much (negative numbers OK)?:  ";
	std::string amountString = UI::getField(false);
	std::vector<int> amountInt = GA_Misc::parseInts(amountString);
	if (amountInt.size() == 0)
	{
		UI::clearIt();
		std::cout << "No integers found.  Aborting modifications.";
		UI::pressEnterToContinue();
		return;
	}
	else if (amountInt[0] == 0)
		return;
	else if (amountInt[0] + ProgramOnly::user.stats[wLDI] < 0)
	{
		badCalculationHaiku(std::abs(amountInt[0]), ProgramOnly::user.stats[wLDI]);
		return;
	}

	// failsafe exit
	if (amountInt[0] == 0)
		return;

	// yes, these are all necessary
	unsigned int amountCounter = std::abs(amountInt[0]);
	std::vector<int> modThesePlayers = {};
	std::vector <int> modEntries[2] = {};
	bool quarantineLoop = false;
	int modMe = 0;
	int modMeSize = 0;
	std::vector<int> quarantinedPlayer = {};
	std::vector<int> cleanPlayer = {};
	int tempPlayerScan = 0;
	bool playerIsOK = true;
	bool quarantineEntryFound = true;
	bool caughtThat = false;
	bool entryFound = false;
	bool confirmModification = false;
	Menu thisMenu;
	// target designators
	unsigned int alpha;
	unsigned int bravo;
	// target protocol
	if (wLDI == 0)
	{
		alpha = 0;
		bravo = 1;
	}
	if (wLDI == 1)
	{
		alpha = 1;
		bravo = 0;
	}
	if (wLDI == 2)
	{
		alpha = 2;
		bravo = 2;
	}
	if (wLDI == 3)
	{
		alpha = 3;
		bravo = 3;
	}

	// process positive numbers
	if (amountInt[0] > 0)
	{
		// how to appoint the losses...?
		std::cout << "Distribute secondary changes...\n";
		thisMenu.clearMenu();
		thisMenu.setMenu("Randomly");
		thisMenu.setMenu("Manually");
		thisMenu.displayMenu();
		unsigned int methodChoice = UI::selector(2);
		if (methodChoice == 0)
			return;
		switch (methodChoice)
		{
		case 1:
		{
			// for (the amount of adjustment cycles)
			for (int x = 0; x < std::abs(amountInt[0]); x++)
			{
				caughtThat = false;
				// choose a random target
				modMe = RandomOps::upperLimit(ProgramOnly::playerDatabase.size()) - 1;
				// check to see if it is in modEntries
				if (modEntries[0].size() > 0)
					for (unsigned int h = 0; h < modEntries[0].size(); h++)
					{
						// if found...
						if (modMe == modEntries[0][h])
						{
							// add a value to the modEntries index
							modEntries[1][h]++;
							// let the loop know that a value has been found in modEntries
							caughtThat = true;
						}
					}
				// if not found in modEntries...
				if (!caughtThat)
				{
					// add appropriate values to the modEntries index
					modEntries[0].push_back(modMe);
					modEntries[1].push_back(1);
				}
			}
			// list the players and values
			for (unsigned int z = 0; z < modEntries[0].size(); z++)
				std::cout << ProgramOnly::playerDatabase[modEntries[0][z]].name << ":  " << modEntries[1][z] << "\n";
			/// modifications needed to adapt to other stat modification types
			std::cout << "Distribute effects to these opponents ";
			// confirm modifications
			confirmModification = UI::yesNo();
			if (confirmModification)
			{
				// perform the modifications
				ProgramOnly::user.stats[alpha] = ProgramOnly::user.stats[alpha] + amountInt[0];
				for (unsigned int a = 0; a < modEntries[0].size(); a++)
					ProgramOnly::playerDatabase[modEntries[0][a]].stats[bravo] = ProgramOnly::playerDatabase[modEntries[0][a]].stats[bravo] + modEntries[1][a];
				return;
			}
			break;
		}
		case 2:
		{
			// begin YELLOW MARKER (do)
			do {
				// if playerDatabase entry is not a quarantine, set to menu
				thisMenu.clearMenu();
				for (unsigned int r = 0; r < ProgramOnly::playerDatabase.size(); r++)
					thisMenu.setMenu(ProgramOnly::playerDatabase[r].name);
				thisMenu.displayMenu();
				// display any current changes
				for (unsigned int t = 0; t < modEntries[0].size(); t++)
					std::cout << ProgramOnly::playerDatabase[modEntries[0][t]].name << ": " << modEntries[1][t] << "\n";
				// upon the event of only 1 opponent option, alert the user that remaining losses will be processed for the only choice
				modMe = UI::selector(thisMenu.choices.size());
				// if 0, break function;
				if (modMe == 0)
					return;
				// modEntries[1][wherever it needs to be]++
				for (unsigned int playerDBScan = 0; playerDBScan < ProgramOnly::playerDatabase.size(); playerDBScan++)
				{
					caughtThat = false;
					if (ProgramOnly::playerDatabase[playerDBScan].name == thisMenu.choices[modMe - 1])
					{
						for (unsigned int modEntriesScan = 0; modEntriesScan < modEntries[0].size(); modEntriesScan++)
							if (modEntries[0][modEntriesScan] == playerDBScan)
							{
								modEntries[1][modEntriesScan]++;
								caughtThat = true;
							}
						if (!caughtThat)
						{
							modEntries[0].push_back(playerDBScan);
							modEntries[1].push_back(1);
						}
					}
				}
				modMeSize++;
				// end YELLOW MARKER
			} while (modMeSize < std::abs(amountInt[0]));
			// display changes
			for (unsigned int x = 0; x < modEntries[0].size(); x++)
				std::cout << ProgramOnly::playerDatabase[modEntries[0][x]].name << ":  " << modEntries[1][x] << "\n";
			// confirm changes
			std::cout << "Distribute effects to these opponents ";
			confirmModification = UI::yesNo();
			// process changes via modEntries
			if (confirmModification)
			{
				for (unsigned int w = 0; w < modEntries[0].size(); w++)
					ProgramOnly::playerDatabase[modEntries[0][w]].stats[bravo] = ProgramOnly::playerDatabase[modEntries[0][w]].stats[bravo] + modEntries[1][w];
				ProgramOnly::user.stats[alpha] = ProgramOnly::user.stats[alpha] + amountInt[0];
			}
			break;
		}
		default:
			// shouldn't be here
			break;
		}
	}
	// process negative numbers
	else if (amountInt[0] < 0)
	{
		if (ProgramOnly::user.stats[alpha] + amountInt[0] == 0)
		{
			// confirm modifications
			std::cout << "All properties of this type for all opponents will be reset.  Continue ";
			confirmModification = UI::yesNo();
			if (!confirmModification)
			{
				UI::clearIt();
				std::cout << "Aborting changes.";
				UI::pressEnterToContinue();
				return;
			}
			/// modifications needed to adapt to other stat modification types
			// perform the modifications
			ProgramOnly::user.stats[alpha] = ProgramOnly::user.stats[alpha] + amountInt[0];
			/// modifications needed to adapt to other stat modification types
			for (unsigned int a = 0; a < ProgramOnly::playerDatabase.size(); a++)
				ProgramOnly::playerDatabase[a].stats[bravo] = 0;
			return;
		}
		// how to appoint the losses...?
		std::cout << "Distribute the effects...\n";
		thisMenu.clearMenu();
		thisMenu.setMenu("Randomly");
		thisMenu.setMenu("Manually");
		thisMenu.displayMenu();
		unsigned int methodChoice = UI::selector(2);
		if (methodChoice == 0)
			return;
		switch (methodChoice)
		{
		case 1:
		{
			// for (the amount of adjustment cycles)
			for (int x = 0; x < std::abs(amountInt[0]); x++)
				// Quarantine loop
				do {
					// reset the conditions
					quarantineLoop = false;
					caughtThat = false;
					// choose a random target
					modMe = RandomOps::upperLimit(ProgramOnly::playerDatabase.size()) - 1;
					// check to see if target is quarantined
					if (quarantinedPlayer.size() > 0)
						for (unsigned int g = 0; g < quarantinedPlayer.size(); g++)
							if (modMe == quarantinedPlayer[g])
								// restart loop without processing
								quarantineLoop = true;
					// If type not found in quarantine...
					if (!quarantineLoop)
						// check to see if it is in modEntries
						if (modEntries[0].size() > 0)
							for (unsigned int h = 0; h < modEntries[0].size(); h++)
								// if found...
								if (modMe == modEntries[0][h])
								{
									/// modifications needed to adapt to other stat modification types
									// check running elegibility for -1 change (the following is "true")
									if (ProgramOnly::playerDatabase[modEntries[0][h]].stats[bravo] - modEntries[1][h] - 1 >= 0)
									{
										// add a value to the modEntries index
										modEntries[1][h]++;
										// signal the loop to exit
										quarantineLoop = false;
										// let the loop know that a value has been found in modEntries
										caughtThat = true;
									}
									/// modifications needed to adapt to other stat modification types
									// check running elegibility for -1 change (the following is "false")
									else if (ProgramOnly::playerDatabase[modEntries[0][h]].stats[bravo] - modEntries[1][h] - 1 < 0)
									{
										// set the quarantine
										quarantinedPlayer.push_back(modMe);
										// signal the loop to skip checking and continue
										quarantineLoop = true;
									}
								}
					// if not found in quarantine or modEntries...
					if (!quarantineLoop && !caughtThat)
					{
						/// modifications needed to adapt to other stat modification types
						// check elegibility for -1 change (the following is "yes")
						if (ProgramOnly::playerDatabase[modMe].stats[1] >= 1)
						{
							// add appropriate values to the modEntries index
							modEntries[0].push_back(modMe);
							modEntries[1].push_back(1);
							// signal the loop to exit
							quarantineLoop = false;
						}
						/// modifications needed to adapt to other stat modification types
						// check elegibility for -1 change (the following is "no")
						else if (ProgramOnly::playerDatabase[modMe].stats[bravo] <= 0)
						{
							// quarantine player
							quarantinedPlayer.push_back(modMe);
							// signal the loop to continue
							quarantineLoop = true;
						}
					}
				} while (quarantineLoop);
				// list the players and values
				for (unsigned int z = 0; z < modEntries[0].size(); z++)
					std::cout << z + 1 << ". " << ProgramOnly::playerDatabase[modEntries[0][z]].name << ":  " << modEntries[1][z] << "\n";
				/// modifications needed to adapt to other stat modification types
				std::cout << "Distribute effects to these opponents ";
				// confirm modifications
				confirmModification = UI::yesNo();
				if (!confirmModification)
				{
					UI::clearIt();
					std::cout << "Aborting changes.";
					UI::pressEnterToContinue();
					return;
				}
				/// modifications needed to adapt to other stat modification types
				// perform the modifications
				ProgramOnly::user.stats[alpha] = ProgramOnly::user.stats[alpha] + amountInt[0];
				/// modifications needed to adapt to other stat modification types
				for (unsigned int a = 0; a < modEntries[0].size(); a++)
					ProgramOnly::playerDatabase[modEntries[0][a]].stats[bravo] = ProgramOnly::playerDatabase[modEntries[0][a]].stats[bravo] - modEntries[1][a];
				break;
		}
		case 2:
		{
			// create an initial database of quarantined players
			for (unsigned int q = 0; q < ProgramOnly::playerDatabase.size(); q++)
				if (ProgramOnly::playerDatabase[q].stats[bravo] - 1 < 0)
					quarantinedPlayer.push_back(q);
			// begin YELLOW MARKER (do)
			do {
				// if playerDatabase entry is not a quarantine, set to menu
				thisMenu.clearMenu();
				for (unsigned int r = 0; r < ProgramOnly::playerDatabase.size(); r++)
				{
					playerIsOK = false;
					for (unsigned int s = 0; s < quarantinedPlayer.size(); s++)
					{
						if (r != quarantinedPlayer[s]) { playerIsOK = true; }
						if (r == quarantinedPlayer[s]) { playerIsOK = false; break; }
					}
					if (playerIsOK)
						thisMenu.setMenu(ProgramOnly::playerDatabase[r].name);
				}
				// display any current changes
				for (unsigned int t = 0; t < modEntries[0].size(); t++)
					std::cout << ProgramOnly::playerDatabase[modEntries[0][t]].name << ": " << modEntries[1][t] << "\n";
				// upon the event of only 1 opponent option, alert the user that remaining losses will be processed for the only choice
				if (thisMenu.choices.size() == 1)
				{
					UI::clearIt();
					std::cout << "Only 1 player found.  Processing for: " << thisMenu.choices[0] << ".\n";
					modMe = 1;
				}
				// otherwise, get a player selection from the user
				else if (thisMenu.choices.size() > 1)
				{
					thisMenu.displayMenu();
					modMe = UI::selector(thisMenu.choices.size());
				}
				// if 0, break function;
				if (modMe == 0)
					return;
				// modEntries[1][wherever it needs to be]++
				for (unsigned int playerDBScan = 0; playerDBScan < ProgramOnly::playerDatabase.size(); playerDBScan++)
				{
					caughtThat = false;
					if (ProgramOnly::playerDatabase[playerDBScan].name == thisMenu.choices[modMe - 1])
					{
						for (unsigned int modEntriesScan = 0; modEntriesScan < modEntries[0].size(); modEntriesScan++)
							if (modEntries[0][modEntriesScan] == playerDBScan)
							{
								modEntries[1][modEntriesScan]++;
								// add any new quarantine entry (as a result of the new total)
								if (ProgramOnly::playerDatabase[playerDBScan].stats[bravo] - modEntries[1][modEntriesScan] - 1 < 0)
									quarantinedPlayer.push_back(playerDBScan);
								caughtThat = true;
							}
						if (!caughtThat)
						{
							modEntries[0].push_back(playerDBScan);
							modEntries[1].push_back(1);
							// add any new quarantine entry (as a result of the new total)
							if (ProgramOnly::playerDatabase[playerDBScan].stats[bravo] - modEntries[1][modEntries[1].size() - 1] - 1 < 0)
								quarantinedPlayer.push_back(playerDBScan);
						}
					}
				}
				modMeSize++;
				// end YELLOW MARKER
			} while (modMeSize < std::abs(amountInt[0]));
			// display changes
			for (unsigned int x = 0; x < modEntries[0].size(); x++)
				std::cout << ProgramOnly::playerDatabase[modEntries[0][x]].name << ":  " << modEntries[1][x] << "\n";
			// confirm changes
			std::cout << "Distribute effects to these opponents ";
			confirmModification = UI::yesNo();
			// process changes via modEntries
			if (confirmModification)
			{
				ProgramOnly::user.stats[alpha] = ProgramOnly::user.stats[alpha] + amountInt[0];
				for (unsigned int w = 0; w < modEntries[0].size(); w++)
					ProgramOnly::playerDatabase[modEntries[0][w]].stats[bravo] = ProgramOnly::playerDatabase[modEntries[0][w]].stats[bravo] - modEntries[1][w];
			}
			break;
		}
		default:
			// shouldn't be here
			break;
		}
	}
	// flag for writing
	ProgramOnly::user.writeMe = true;
}
// Modify opponent stats with a custom value
void opponentModifyWLDI(unsigned int playerIndex, int wLDI)
{
	// how much?
	std::cout << "How much (negative numbers OK)?:  ";
	std::string amountString = UI::getField(false);
	std::vector<int> amountInt = GA_Misc::parseInts(amountString);
	if (amountInt.size() == 0)
		return;
	else if (amountInt[0] == 0)
		return;
	else if (amountInt[0] + ProgramOnly::user.stats[wLDI] < 0)
	{
		badCalculationHaiku(std::abs(amountInt[0]), ProgramOnly::user.stats[wLDI]);
		return;
	}

	// failsafe exit
	if (amountInt[0] == 0)
		return;

	// target designators
	unsigned int alpha;
	unsigned int bravo;
	// target protocol
	if (wLDI == 0)
	{
		alpha = 0;
		bravo = 1;
	}
	if (wLDI == 1)
	{
		alpha = 1;
		bravo = 0;
	}
	if (wLDI == 2)
	{
		alpha = 2;
		bravo = 2;
	}
	if (wLDI == 3)
	{
		alpha = 3;
		bravo = 3;
	}

	// subtracting too much
	if (ProgramOnly::playerDatabase[playerIndex].stats[alpha] + amountInt[0] < 0)
	{
		badCalculationHaiku(amountInt[0], ProgramOnly::playerDatabase[playerIndex].stats[alpha]);
		return;
	}
	// processing is OK
	else if (ProgramOnly::playerDatabase[playerIndex].stats[alpha] + amountInt[0] >= 0)
	{
		std::cout << "\nUser stats will be affected appropriately.  ";
		if (UI::commitChanges())
		{
			ProgramOnly::playerDatabase[playerIndex].stats[alpha] = ProgramOnly::playerDatabase[playerIndex].stats[alpha] + amountInt[0];
			ProgramOnly::user.stats[bravo] = ProgramOnly::user.stats[bravo] - amountInt[0];
			std::cout << "\nChanges applied.";
			UI::pressEnterToContinue();
		}
	}
	// flag for writing
	ProgramOnly::playerDatabase[playerIndex].writeMe = true;
}

/// General Tools:
// Returns an unsigned int (0 OK)
unsigned int choosePlayer(Menu &passThrough, bool allowChooseAll)
{
	bool clanOn = RandomOps::flipCoin();
	opponentSelectMenu(passThrough, clanOn);
	if (passThrough.choices.size() == 0)
	{
		UI::clearIt();
		std::cout << "No players to choose from.";
		UI::pressEnterToContinue();
		return 0;
	}
	if (allowChooseAll)
		passThrough.setMenu(">> All");
	passThrough.displayMenu();
	if (clanOn)
		std::cout << "Clan view (decided by coin flip) is \"on\"\n\n";
	if (!clanOn)
		std::cout << "Clan view (decided by coin flip) is \"off\"\n\n";
	return UI::selector(passThrough.choices.size());;
}
// Handy little tool to make the team display dynamic
void displayTeam(Player &passThrough, bool mainTeam)
{
	switch (mainTeam)
	{
	case true:
	{
		if (passThrough.mainTeam.size() == 0)
			return;
		for (unsigned int x = 0; x < passThrough.mainTeam.size(); x = x + 2)
		{
			if (passThrough.mainTeam[x] > 0)
			{
				std::cout << "\t" << ASGS::aSGIndex[passThrough.mainTeam[x]].name;
				if (passThrough.mainTeam[x + 1] != 0)
					std::cout << ", " << ASGS::aSGIndex[passThrough.mainTeam[x]].moveList[passThrough.mainTeam[x + 1] - 1] << "\n";
				else if (passThrough.mainTeam[x + 1] == 0)
					std::cout << "\n";
			}
			else if (passThrough.mainTeam[x] < 0)
			{
				std::cout << "\t" << ASGS::aSGIndex[std::abs(passThrough.mainTeam[x])].altName;
				if (passThrough.mainTeam[x + 1] != 0)
					std::cout << ", " << ASGS::aSGIndex[std::abs(passThrough.mainTeam[x])].moveList[passThrough.mainTeam[x + 1] - 1] << "\n";
				else if (passThrough.mainTeam[x + 1] == 0)
					std::cout << "\n";
			}
		}
	}
	break;
	case false:
	{
		if (passThrough.altTeam.size() == 0)
			return;
		for (unsigned int x = 0; x < passThrough.altTeam.size(); x = x + 2)
		{
			if (passThrough.altTeam[x] > 0)
			{
				std::cout << "\t" << ASGS::aSGIndex[passThrough.altTeam[x]].name;
				if (passThrough.altTeam[x + 1] != 0)
					std::cout << ", " << ASGS::aSGIndex[passThrough.altTeam[x]].moveList[passThrough.altTeam[x + 1] - 1] << "\n";
				else if (passThrough.altTeam[x + 1] == 0)
					std::cout << "\n";
			}
			else if (passThrough.altTeam[x] < 0)
			{
				std::cout << "\t" << ASGS::aSGIndex[std::abs(passThrough.altTeam[x])].altName;
				if (passThrough.altTeam[x + 1] != 0)
					std::cout << ", " << ASGS::aSGIndex[std::abs(passThrough.altTeam[x])].moveList[passThrough.altTeam[x + 1] - 1] << "\n";
				else if (passThrough.altTeam[x + 1] == 0)
					std::cout << "\n";
			}
		}
	}
	break;
	}
}
// If a bad subtraction is found, subtlely infuse the user with a sense of wrongdoing
void badCalculationHaiku(int first, int second)
{
	std::cout << "To subtract " << std::abs(first) << " from " << second << "...\n";
	std::cout << "You can't just DO that.  Things BREAK.\n";
	std::cout << "Immature and reckless decisions... >:< \n";
	UI::pressEnterToContinue();
}

/// Review/Test:

/// In progress:

/// Graveyard: