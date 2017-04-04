#include "stdafx.h"
#include "../../GA_Library/GA_Library/GA_Library.h"
#include "SA_UC.h"

// Set the main Menu
void skullAssistantMainMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("The SkullAssistant Player Hub");
	passThrough.setMenu("Training");
	passThrough.setMenu("The SkullAssistant Experience");
	passThrough.setMenu("Testing Area");
	passThrough.setMenu("Abandon Your Quest For The Skullheart (and any changes)");
}
// Default menu function for selecting an ASG
void aSGMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("Beowulf");
	passThrough.setMenu("Big Band");
	passThrough.setMenu("Cerebella");
	passThrough.setMenu("Double");
	passThrough.setMenu("Eliza");
	passThrough.setMenu("Filia");
	passThrough.setMenu("Fukua");
	passThrough.setMenu("Ms. Fortune");
	passThrough.setMenu("Painwheel");
	passThrough.setMenu("Parasoul");
	passThrough.setMenu("Peacock");
	passThrough.setMenu("Robo Fortune");
	passThrough.setMenu("Squigly");
	passThrough.setMenu("Valentine");
}
// Populates the specified menu object with the move list of the specified ASG
void setMoveMenu(Menu &passThrough, characterInfo &selectedASG)
{
	passThrough.clearMenu();
	for (unsigned int x = 0; x < selectedASG.moveTotal; x++)
		passThrough.setMenu(selectedASG.moveList[x]);
}
// Displays the information change menu
void infoChangeMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("Name");
	passThrough.setMenu("Clan");
	passThrough.setMenu("Main team");
	passThrough.setMenu("Alternate team");
	passThrough.setMenu("Manage style notes");
}
// Set the playerHub menu
void statisticsMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("User & opponent info management");
	passThrough.setMenu("Modify statistics");
}
// Set the User & Opponent management menu
void userOpponentMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("View user info");
	passThrough.setMenu("View opponent info");
	passThrough.setMenu("Change user info");
	passThrough.setMenu("Change opponent info"); 
	passThrough.setMenu("Add an opponent");
	passThrough.setMenu("Toggle an opponent profile for deletion");
	passThrough.setMenu("Quick-Sync all information");
}
// Set the statistics modification menu
void modifyStatsMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("Game Results Entry");
	passThrough.setMenu("Reset user stats");
	passThrough.setMenu("Reset opponent stats");
	passThrough.setMenu("Manual modification");
}
// Set the opponent selection menu
void opponentSelectMenu(Menu &passThrough, bool showClan)
{
	passThrough.clearMenu();
	if (showClan)
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
		{
			if (ProgramOnly::playerDatabase[x].clan != "")
				passThrough.setMenu(ProgramOnly::playerDatabase[x].clan + " - " + ProgramOnly::playerDatabase[x].name);
			else if (ProgramOnly::playerDatabase[x].clan == "")
				passThrough.setMenu(ProgramOnly::playerDatabase[x].name);
		}
	else if (!showClan)
		for (unsigned int x = 0; x < ProgramOnly::playerDatabase.size(); x++)
			passThrough.setMenu(ProgramOnly::playerDatabase[x].name);
}
// Set the Win, Loss, Draw, Interrupt menu
void setWLDIMenu(Menu &passThrough)
{
	passThrough.clearMenu();
	passThrough.setMenu("Wins");
	passThrough.setMenu("Losses");
	passThrough.setMenu("Draws");
	passThrough.setMenu("Interrupts");
}