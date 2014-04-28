/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutGame.cpp

	This is a test game application, a game that demonstrates use of the 
	SideScrollerFramework to make a little scrolling, interactive demo. It
	demonstrates the rendering of images and text as well as responding to
	key presses and button cicks. Students should make their own named game
	applictions using a similar pattern, gradually adding other components,
	like additional gui controls, tiles, sprites, ai, and physics.
 */

#include "AstroJump\stdafx.h"

// BugginOut GAME INCLUDES
#include "AstroJumpButtonEventHandler.h"
#include "AstroJumpDataLoader.h"
#include "AstroJump.h"
#include "AstroJumpKeyEventHandler.h"
#include "AstroJumpTextGenerator.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

#include "XAudio2BasicSound.h"

/*
	WinMain - This is the application's starting point. In this method we will construct a Game object, 
	then initialize all the platform-dependent technologies, then construct all the custom data for our 
	game, and then initialize the Game with	our custom data. We'll then start the game loop.
*/

struct Nums
{
	int num1;
	int num2;
};
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	// CREATE THE GAME
	Game *astroJumpGame = new Game();

	// FIRST WE'LL SETUP THE DATA LOADER, SINCE IT MAY NEED TO READ
	// IN DATA TO SETUP OTHER STUFF
	AstroJumpDataLoader *astroJumpDataLoader = new AstroJumpDataLoader();
	astroJumpDataLoader->initWinHandle(hInstance, nCmdShow);
	astroJumpGame->setDataLoader(astroJumpDataLoader);
	astroJumpDataLoader->loadGame(astroJumpGame, W_INIT_FILE); // INIT FILE NEEDS TO BE UPDATED
	
	// WHAT WE SHOULD BE DOING HERE IS LOADING THE GAME DATA FROM FILES. THIS
	// MEANS THE GUIS THEMSELVES AS WELL AS THE LEVELS. THAT WILL BE LEFT
	// FOR BECHMARK HWS. FOR NOW WE WILL JUST HARD CODE THE LOADING OF THE GUI

	// LOAD THE GUI STUFF, AGAIN, NOTE THAT THIS SHOULD REALLY
	// BE DONE FROM A FILE, NOT HARD CODED
	astroJumpDataLoader->loadGUI(astroJumpGame, W_GUI_INIT_FILE); //GUI INIT FILE NEEDS TO BE UPDATED

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	AstroJumpButtonEventHandler *astroJumpButtonHandler = new AstroJumpButtonEventHandler();
	GameGUI *gui = astroJumpGame->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)astroJumpButtonHandler);

	// SPECIFY WHO WILL HANDLE KEY EVENTS
	AstroJumpKeyEventHandler *astroJumpKeyHandler = new AstroJumpKeyEventHandler();
	astroJumpGame->getInput()->registerKeyHandler((KeyEventHandler*)astroJumpKeyHandler);

	XAudio2BasicSound *aud = new XAudio2BasicSound();
	aud->start();

	// START THE GAME LOOP
	astroJumpGame->runGameLoop();

	// GAME'S OVER SHUTDOWN ALL THE STUFF WE CONSTRUCTED HERE
	delete (WindowsOS*)astroJumpGame->getOS();
	delete (WindowsInput*)astroJumpGame->getInput();
	delete (WindowsTimer*)astroJumpGame->getTimer();
	delete (DirectXGraphics*)astroJumpGame->getGraphics();
	delete (AstroJumpTextGenerator*)astroJumpGame->getText()->getTextGenerator();
	delete astroJumpButtonHandler;
	delete astroJumpKeyHandler;
	delete astroJumpGame;

	// AND RETURN
	return 0;
}