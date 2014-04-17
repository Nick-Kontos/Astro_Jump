#include "AstroJump\stdafx.h"

// Bugs GAME INCLUDES
#include "AstroJumpButtonEventHandler.h"
#include "AstroJumpDataLoader.h"
#include "AstroJump.h"
#include "AstroJumpKeyEventHandler.h"
#include "AstroJumpTextGenerator.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\bots\RandomJumpingBot.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\world\TiledLayer.h"
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

// TMX MAP LOADING
#include "tmxmi\TMXMapImporter.h"

// ANIMATED SPRITE TYPE LOADING
#include "psti\PoseurSpriteTypesImporter.h"

/*
loadGame - This method loads the setup game data into the game and
constructs all the needed objects for the game to work.
*/
void AstroJumpDataLoader::loadGame(Game *game, wstring gameInitFile)
{
	// AND LET'S READ IN THE GAME SETUP INFO
	// FIRST LOAD ALL THE PROPERTIES
	map<wstring, wstring> *properties = new map<wstring, wstring>();
	loadGameProperties(game, properties, gameInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring titleProp = (*properties)[W_TITLE];
	wstring useFullscreenProp = (*properties)[W_USE_FULLSCREEN_MODE];
	bool useFullscreen = false;
	if (useFullscreenProp.compare(L"true") == 0)
		useFullscreen = true;

	// GET THE SCREEN WIDTH AND HEIGHT
	int screenWidth, screenHeight;
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;

	// MAKE A CUSTOM GameOS OBJECT (WindowsOS) FOR SOME WINDOWS
	// PLATFORM STUFF, INCLUDING A Window OF COURSE
	WindowsOS *AstroJumpOS = new WindowsOS(hInstance,
		nCmdShow,
		useFullscreen,
		titleProp,
		screenWidth, screenHeight,
		game);

	int textFontSize;
	wstring textFontSizeProp = (*properties)[W_TEXT_FONT_SIZE];
	wstringstream(textFontSizeProp) >> textFontSize;

	// RENDERING WILL BE DONE USING DirectX
	DirectXGraphics *AstroJumpGraphics = new DirectXGraphics(game);
	AstroJumpGraphics->init(screenWidth, screenHeight);
	AstroJumpGraphics->initGraphics(AstroJumpOS, useFullscreen);
	AstroJumpGraphics->initTextFont(textFontSize);

	// AND NOW LOAD THE COLORS THE GRAPHICS WILL USE
	// AS A COLOR KEY AND FOR RENDERING TEXT
	initColors(AstroJumpGraphics, properties);

	// WE'LL USE WINDOWS PLATFORM METHODS FOR GETTING INPUT
	WindowsInput *AstroJumpInput = new WindowsInput();

	// AND WINDOWS FOR THE TIMER AS WELL
	WindowsTimer *AstroJumpTimer = new WindowsTimer();

	// NOW INITIALIZE THE Game WITH ALL THE
	// PLATFORM AND GAME SPECIFIC DATA WE JUST CREATED
	game->initPlatformPlugins((GameGraphics*)AstroJumpGraphics,
		(GameInput*)AstroJumpInput,
		(GameOS*)AstroJumpOS,
		(GameTimer*)AstroJumpTimer);
	

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DRAWS
	// TEXT ON THE SCREEN EACH FRAME
	AstroJumpTextGenerator *AstroTextGenerator = new AstroJumpTextGenerator();
	AstroTextGenerator->initText(game);
	GameText *text = game->getText();
	text->initDebugFile(W_DEBUG_FILE);
	text->setTextGenerator((TextGenerator*)AstroTextGenerator);

	// INIT THE VIEWPORT TOO
	initViewport(game->getGUI(), properties);

	// WE DON'T NEED THE PROPERTIES MAP ANYMORE, THE GAME IS ALL LOADED
	delete properties;
}

/*
initColors - this helper method loads the color key, used for loading
images, and the font color, used for rendering text.
*/
void AstroJumpDataLoader::initColors(GameGraphics *graphics,
	map<wstring, wstring> *properties)
{
	int fontRed, fontGreen, fontBlue;
	wstring fontRedProp = (*properties)[W_FONT_COLOR_RED];
	wstring fontGreenProp = (*properties)[W_FONT_COLOR_GREEN];
	wstring fontBlueProp = (*properties)[W_FONT_COLOR_BLUE];
	wstringstream(fontRedProp) >> fontRed;
	wstringstream(fontGreenProp) >> fontGreen;
	wstringstream(fontBlueProp) >> fontBlue;

	// COLOR USED FOR RENDERING TEXT
	graphics->setFontColor(fontRed, fontGreen, fontBlue);

	int keyRed, keyGreen, keyBlue;
	wstring keyRedProp = (*properties)[W_COLOR_KEY_RED];
	wstring keyGreenProp = (*properties)[W_COLOR_KEY_GREEN];
	wstring keyBlueProp = (*properties)[W_COLOR_KEY_BLUE];
	wstringstream(keyRedProp) >> keyRed;
	wstringstream(keyGreenProp) >> keyGreen;
	wstringstream(keyBlueProp) >> keyBlue;

	// COLOR KEY - COLOR TO BE IGNORED WHEN LOADING AN IMAGE
	// NOTE, IF YOU WISH TO USE PNG IMAGES THAT CONTAIN ALPHA
	// CHANNEL DATA, YOU DON'T NEED A COLOR KEY
	graphics->setColorKey(keyRed, keyGreen, keyBlue);
}

/*
loadGUI - This method loads all the GUI assets described in the guiInitFile
argument. Note that we are loading all GUI art for all GUIs when the application
first starts. We'll learn a better technique later in the semester.
*/
void AstroJumpDataLoader::loadGUI(Game *game, wstring guiInitFile)
{
	// WE'RE JUST GOING TO IGNORE THE GUI FILE FOR NOW.
	// FOR THE MOMENT WE ARE CALLING THIS HARD-CODED GUI LOADER
	hardCodedLoadGUIExample(game);
}

/*
loadLevel - This method should load the data the level described by the
levelInitFile argument in to the Game's game state manager.
*/
void AstroJumpDataLoader::loadWorld(Game *game, wstring levelInitFile)
{
	// LOAD THE LEVEL'S BACKGROUND TILES
	TMXMapImporter tmxMapImporter;
	tmxMapImporter.loadWorld(game, W_LEVEL_1_DIR, W_LEVEL_1_NAME);

	// SPECIFY WHO WILL DO THE PATHFINDING
	GameStateManager *gsm = game->getGSM();
	World *world = gsm->getWorld();
	SpriteManager *spriteManager = gsm->getSpriteManager();

	// LOAD THE LEVEL'S SPRITE IMAGES
	PoseurSpriteTypesImporter psti;
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	// LET'S MAKE A PLAYER SPRITE
	// @TODO - LATER WE'LL LOAD ALL LEVEL DATA FROM A FILE
	Physics *physics = gsm->getPhysics();
	physics->setGravity(W_GRAVITY);
	AnimatedSprite *player = spriteManager->getPlayer(); // CHECK CREATION OF PLAYER
	AnimatedSpriteType *playerSpriteType = spriteManager->getSpriteType(0);
	player->setSpriteType(playerSpriteType);
	player->setAlpha(255);
	player->setCurrentState(IDLE);
	player->setSpawnX(PLAYER_INIT_X);
	player->setSpawnY(PLAYER_INIT_Y);
	player->setSpawnVx(0);
	player->setSpawnVy(0);
	physics->addSprite(player);
	AnimatedSprite *asteroid = new AnimatedSprite();
	asteroid->setSpriteType(spriteManager->getSpriteType(1));
	asteroid->setAlpha(255);
	asteroid->setCurrentState(IDLE);
	asteroid->setSpawnX(100.0f);
	asteroid->setSpawnY(200.0f);
	asteroid->setSpawnVx(0);
	asteroid->setSpawnVy(0);
	physics->addSprite(asteroid);
	spriteManager->addAsteriod(asteroid);
	AnimatedSprite *clear = spriteManager->getClear();
	clear->setSpriteType(spriteManager->getSpriteType(2));
	clear->setAlpha(255);
	clear->setCurrentState(IDLE);
	clear->setSpawnX(0);
	clear->setSpawnY(0);
	clear->setSpawnVx(0);
	clear->setSpawnVy(0);
	physics->addSprite(clear);


	// AND LET'S ADD A BUNCH OF RANDOM JUMPING BOTS, FIRST ALONG
	// A LINE NEAR THE TOP

	// UNCOMMENT THE FOLLOWING CODE BLOCK WHEN YOU ARE READY TO ADD SOME BOTS
	/*	for (int i = 2; i <= 26; i++)
	{
	float botX = 400.0f + (i * 100.0f);
	float botY = 100.0f;
	makeRandomJumpingBot(game, botSpriteType, botX, botY);
	}

	// AND THEN STRATEGICALLY PLACED AROUND THE LEVEL
	makeRandomJumpingBot(game, botSpriteType, 400, 100);
	makeRandomJumpingBot(game, botSpriteType, 200, 400);
	makeRandomJumpingBot(game, botSpriteType, 400, 400);
	makeRandomJumpingBot(game, botSpriteType, 800, 700);
	makeRandomJumpingBot(game, botSpriteType, 900, 700);
	makeRandomJumpingBot(game, botSpriteType, 1000, 700);
	makeRandomJumpingBot(game, botSpriteType, 100, 1000);
	makeRandomJumpingBot(game, botSpriteType, 300, 1000);
	makeRandomJumpingBot(game, botSpriteType, 500, 1000);
	makeRandomJumpingBot(game, botSpriteType, 100, 1400);
	makeRandomJumpingBot(game, botSpriteType, 400, 1400);
	makeRandomJumpingBot(game, botSpriteType, 700, 1400);

	// AND THEN A BUNCH LINED UP NEAR THE LEVEL EXIT
	for (int i = 0; i < 14; i++)
	makeRandomJumpingBot(game, botSpriteType, 1700.0f + (i*100.0f), 1300.0f);
	*/
}

/*
initBugsGUI - This method builds a GUI for the Bugs Game application.
Note that we load all the GUI components from this method, including
the ScreenGUI with Buttons and Overlays and the Cursor.
*/
void AstroJumpDataLoader::hardCodedLoadGUIExample(Game *game)
{
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	DirectXTextureManager *guiTextureManager = (DirectXTextureManager*)graphics->getGUITextureManager();

	// SETUP THE CURSOR VIA OUR HELPER METHOD
	initCursor(gui, guiTextureManager);
	initSplashScreen(game, gui, guiTextureManager);
	initMainMenu(gui, guiTextureManager);
	initInGameGUI(gui, guiTextureManager);
	
	initVictoryScreen(gui, guiTextureManager);
	initDefeatScreen(gui, guiTextureManager);
//	initLevelSelectScreen(gui, guiTextureManager);
	initAboutScreen(gui, guiTextureManager);
	initHelpScreen(gui, guiTextureManager);
}

void AstroJumpDataLoader::initVictoryScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *victoryScreen = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_VICTORY_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 256;
	imageToAdd->y = 100;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->imageID = imageID;
	imageToAdd->roationInRadians = 0.0f;
	victoryScreen->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN NEXT LEVEL BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_NEXT_LEVEL_PATH);
	int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		500,
		0,
		255,
		200,
		100,
		false,
		W_NEXT_LEVEL_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	victoryScreen->addButton(buttonToAdd);

	// AND LET'S ADD A EXIT BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_EXIT_PATH);
	mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		350,
		0,
		255,
		200,
		100,
		false,
		W_GO_TO_MM_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	victoryScreen->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_VICTORY, victoryScreen);
}

void AstroJumpDataLoader::initDefeatScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *deafeatScreen = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_DEFEAT_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 256;
	imageToAdd->y = 100;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->imageID = imageID;
	imageToAdd->roationInRadians = 0.0f;
	deafeatScreen->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN NEXT LEVEL BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_RESTART_PATH);
	int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		500,
		0,
		255,
		200,
		100,
		false,
		W_RESTART_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	deafeatScreen->addButton(buttonToAdd);

	// AND LET'S ADD A EXIT BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_EXIT_PATH);
	mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		350,
		0,
		255,
		200,
		100,
		false,
		W_GO_TO_MM_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	deafeatScreen->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_OVER, deafeatScreen);
}



void AstroJumpDataLoader::initHelpScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *helpScreen = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_HELP_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1367;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	imageToAdd->roationInRadians = 0.0f;
	helpScreen->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN NEXT LEVEL BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_BACK_PATH);
	int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		500,
		0,
		255,
		200,
		100,
		false,
		W_GO_TO_MM_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	helpScreen->addButton(buttonToAdd);

	//// AND LET'S ADD A EXIT BUTTON
	//buttonToAdd = new Button();

	//// - GET THE BUTTON COMMAND AND IMAGE IDs

	//normalTextureID = guiTextureManager->loadTexture(W_EXIT_PATH);
	//mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	//// - INIT THE START BUTTON
	//buttonToAdd->initButton(normalTextureID,
	//	mouseOverTextureID,
	//	412,
	//	350,
	//	0,
	//	255,
	//	200,
	//	100,
	//	false,
	//	W_GO_TO_MM_COMMAND);

	//// AND NOW LOAD IT INTO A ScreenGUI
	//deafeatScreen->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_IN_GAME_HELP, helpScreen);
}

void AstroJumpDataLoader::initAboutScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *aboutScreen = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_ABOUT_SCREEN_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1367;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	imageToAdd->roationInRadians = 0.0f;
	aboutScreen->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN NEXT LEVEL BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_BACK_PATH);
	int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		500,
		0,
		255,
		200,
		100,
		false,
		W_GO_TO_MM_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	aboutScreen->addButton(buttonToAdd);

	//// AND LET'S ADD A EXIT BUTTON
	//buttonToAdd = new Button();

	//// - GET THE BUTTON COMMAND AND IMAGE IDs

	//normalTextureID = guiTextureManager->loadTexture(W_EXIT_PATH);
	//mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	//// - INIT THE START BUTTON
	//buttonToAdd->initButton(normalTextureID,
	//	mouseOverTextureID,
	//	412,
	//	350,
	//	0,
	//	255,
	//	200,
	//	100,
	//	false,
	//	W_GO_TO_MM_COMMAND);

	//// AND NOW LOAD IT INTO A ScreenGUI
	//deafeatScreen->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_IN_GAME_ABOUT, aboutScreen);
}


/*
initCursor - initializes a simple little cursor for the gui.
*/
void AstroJumpDataLoader::initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - FIRST LOAD THE GREEN CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(W_GREEN_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - AND NOW THE RED ONE
	imageID = guiTextureManager->loadTexture(W_RED_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(imageIDs,
		*(imageIDs->begin()),
		0,
		0,
		0,
		255,
		32,
		32);
	gui->setCursor(cursor);
}

/*
initSplashScreen - initializes the game's splash screen gui.
*/
void AstroJumpDataLoader::initSplashScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		0,
		0,
		0,
		255,
		game->getGraphics()->getScreenWidth(),
		game->getGraphics()->getScreenHeight(),
		false,
		W_GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

/*
initMainMenu - initializes the game's main menu gui.
*/
void AstroJumpDataLoader::initMainMenu(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_MAIN_MENU_PATH);
	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 1367;
	imageToAdd->height = 768;
	imageToAdd->imageID = imageID;
	imageToAdd->roationInRadians = 0.0f;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_SELECT_LEVEL_PATH);
	int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		200,
		0,
		255,
		200,
		100,
		false,
		W_START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD AN HELP BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	normalTextureID = guiTextureManager->loadTexture(W_HELP_PATH);
	mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		300,
		0,
		255,
		200,
		100,
		false,
		W_HELP_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);


	// AND LET'S ADD AN ABOUT BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	normalTextureID = guiTextureManager->loadTexture(W_ABOUT_PATH);
	mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		400,
		0,
		255,
		200,
		100,
		false,
		W_ABOUT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_QUIT_PATH);
	mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		412,
		500,
		0,
		255,
		200,
		100,
		false,
		W_EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_MAIN_MENU, mainMenuGUI);
}

/*
initInGameGUI - initializes the game's in-game gui.
*/
void AstroJumpDataLoader::initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_PATH);
	unsigned int mouseOverTextureID = normalTextureID;//guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		0,
		0,
		0,
		255,
		200,
		100,
		false,
		W_QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_IN_PROGRESS, inGameGUI);
}

/*
initViewport - initializes the game's viewport.
*/
void AstroJumpDataLoader::initViewport(GameGUI *gui, map<wstring, wstring> *properties)
{
	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportOffsetX, viewportOffsetY, toggleOffsetY, screenWidth, screenHeight;
	wstring viewportOffsetXProp = (*properties)[W_VIEWPORT_OFFSET_X];
	wstring viewportOffsetYProp = (*properties)[W_VIEWPORT_OFFSET_Y];
	wstring toggleOffsetYProp = (*properties)[W_TOGGLE_OFFSET_Y];
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(viewportOffsetXProp) >> viewportOffsetX;
	wstringstream(viewportOffsetYProp) >> viewportOffsetY;
	wstringstream(toggleOffsetYProp) >> toggleOffsetY;
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;
	int viewportWidth = screenWidth - viewportOffsetX;
	int viewportHeight = screenHeight - viewportOffsetY;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setViewportOffsetX(viewportOffsetX);
	viewport->setViewportOffsetY(viewportOffsetY);
	viewport->setToggleOffsetY(toggleOffsetY);
}