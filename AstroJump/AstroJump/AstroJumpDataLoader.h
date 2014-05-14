/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

BugsDataLoader.h

This class provides a custom importer for the BugsGame to import
game data, gui data, and world (i.e. level) data.
*/
#pragma once
#include "stdafx.h"
#include "sssf\data_loader\GameDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"
//Lua INCLUDES
#include "LuaPlusFramework\LuaPlus.h"
namespace lua
{
	extern GameStateManager* gsm;
}
class AstroJumpDataLoader : public GameDataLoader
{
private:
	// WE NEED THESE GUYS TO INIT OUR WINDOWS WINDOW
	HINSTANCE hInstance;
	int nCmdShow;
	GameStateManager *gsm;


public:
	AstroJumpDataLoader()	{}
	~AstroJumpDataLoader()	{}

	// INLINED MUTATOR METHOD
	void initWinHandle(HINSTANCE initHInstance, int initNCmdShow)
	{
		hInstance = initHInstance;
		nCmdShow = initNCmdShow;
	}


	// THESE SHOULD BE LOADING DATA FROM FILES. THEY
	// ARE ALL DEFINED IN BugsDataLoader.cpp
	void loadGame(Game *game, wstring gameInitFile);
	void loadGUI(Game *game, wstring guiInitFile);
	void loadWorld(Game *game, string levelInitFile);

	// THESE ARE HARD-CODED EXAMPLES OF GUI DATA LOADING
	void hardCodedLoadGUIExample(Game *game);

	// SOME HELPER METHODS FOR SETTING UP THE GAME
	void initColors(GameGraphics *graphics, map<wstring, wstring> *properties);
	void initViewport(GameGUI *gui, map<wstring, wstring> *properties);

	// AND SOME HELPER METHODS FOR LOADING THE GUI
	void initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initSplashScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initGameWinScreen(Game *game, GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initMainMenu(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initVictoryScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initDefeatScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initLevelSelectScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initAboutScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initHelpScreen(GameGUI *gui, DirectXTextureManager *guiTextureManager);
};