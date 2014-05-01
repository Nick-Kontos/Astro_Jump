#include "AstroJump\stdafx.h"
#include "AstroJump.h"
#include "AstroJumpButtonEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"

void AstroJumpButtonEventHandler::handleButtonEvents(Game *game,
	wstring command)
{
	// THE USER PRESSED THE Exit BUTTON ON THE MAIN MENU,
	// SO LET'S SHUTDOWN THE ENTIRE APPLICATION
	if (command.compare(W_EXIT_COMMAND) == 0)
	{
		game->shutdown();
	}
	// THE USER PRESSED THE MOUSE BUTTON ON THE SPLASH
	// SCREEN, SO LET'S GO TO THE MAIN MENU
	else if (command.compare(W_GO_TO_MM_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToMainMenu();
	}
	else if (command.compare(W_HELP_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToHelp();
	}
	else if (command.compare(W_ABOUT_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToAbout();
	}
	// THE USER PRESSED THE Start BUTTON ON THE MAIN MENU,
	// SO LET'S START THE GAME FROM THE FIRST LEVEL
	else if (command.compare(W_LEVEL1_COMMAND) == 0)
	{
		game->setCurrentLevelFileName("level1.lua");
		game->startGame();
	}
	else if (command.compare(W_LEVEL2_COMMAND) == 0)
	{
		game->setCurrentLevelFileName("level2.lua");
		game->startGame();
	}
	else if (command.compare(W_LEVEL3_COMMAND) == 0)
	{
		game->setCurrentLevelFileName("level3.lua");
		game->startGame();
	}
	else if (command.compare(W_SELECT_LEVEL_COMMAND) == 0)
	{
		GameStateManager *gsm = game->getGSM();
		gsm->goToLevelSelect();
	}
	// THE USER PRESSED THE Quit BUTTON ON THE IN-GAME MENU,
	// SO LET'S UNLOAD THE LEVEL AND RETURN TO THE MAIN MENU
	else if (command.compare(W_QUIT_COMMAND) == 0)
	{
		game->quitGame();
	}
}