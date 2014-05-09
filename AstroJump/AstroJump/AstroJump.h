#pragma once
#include "stdafx.h"

/*
AstroJump.h

This file contains setup data for making the Bugs game. Note that nearly
all of this data would better serve us if loaded from files.
*/

// HERE IS THE Bugs GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE
static const wstring	W_LEVEL_1_DIR = L"data/levels/SideScrollerDesert/";
static const wstring	W_LEVEL_1_NAME = L"SideScrollerDesertLevel.tmx";
static const wstring	W_LEVEL_1_PATH = W_LEVEL_1_DIR + W_LEVEL_1_NAME;
static const wstring	W_INIT_FILE = L"data/AstroJumpInit.txt";
static const wstring	W_GUI_INIT_FILE = L"data/gui/AstroGUI.txt";
static const string		W_DEBUG_FILE = "DebugOutput.txt";

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE = L"TITLE";
static const wstring	W_SCREEN_WIDTH = L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT = L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE = L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE = L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X = L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y = L"VIEWPORT_OFFSET_Y";
static const wstring	W_TOGGLE_OFFSET_Y = L"TOGGLE_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED = L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN = L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE = L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED = L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN = L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE = L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND = L"Go To Main Menu";
static const wstring	W_LEVEL1_COMMAND = L"Level1";
static const wstring	W_LEVEL2_COMMAND = L"Level2";
static const wstring	W_LEVEL3_COMMAND = L"Level3";
static const wstring	W_START_COMMAND = L"Start";
static const wstring	W_EXIT_COMMAND = L"Exit";
static const wstring	W_RESTART_COMMAND = L"Restart";
static const wstring	W_SELECT_LEVEL_COMMAND = L"Select_Level";
static const wstring	W_NEXT_LEVEL_COMMAND = L"Next_Level";
static const wstring	W_QUIT_COMMAND = L"Quit";
static const wstring	W_QUIT_MM_COMMAND = L"Quit_MM";
static const wstring	W_HELP_COMMAND = L"Help";
static const wstring	W_ABOUT_COMMAND = L"About";
static const wstring	W_GREEN_CURSOR_PATH = L"data/gui/cursor/green_cursor.png";
static const wstring	W_RED_CURSOR_PATH = L"data/gui/cursor/red_cursor.png";
//SCREENS
static const wstring	W_SPLASH_SCREEN_PATH = L"data/gui/overlays/Astro_Jump_Splash_Screen1.png";
static const wstring	W_MAIN_MENU_PATH = L"data/gui/overlays/Astro_Jump_Main_Menu_Screen1.png";
static const wstring	W_SELECT_LEVEL_SCREEN_PATH = L"data/gui/overlays/Astro_Jump_Select_Level_Screen1.png";
static const wstring	W_VICTORY_PATH = L"data/gui/overlays/Astro_Jump_Victory_Screen1.png";
static const wstring	W_DEFEAT_PATH = L"data/gui/overlays/Astro_Jump_Defeat_Screen1.png";
static const wstring	W_HELP_SCREEN_PATH = L"data/gui/overlays/Astro_Jump_Help_Screen1.png";
static const wstring	W_ABOUT_SCREEN_PATH = L"data/gui/overlays/Astro_Jump_About_Screen1.png";
static const wstring	W_TOP_PANEL_PATH = L"data/gui/overlays/Top_Panel.png";
//BUTTONS
static const wstring	W_LEVEL1_PATH = L"data/gui/buttons/Astro_Jump_Level1_Button.png";
static const wstring	W_LEVEL2_PATH = L"data/gui/buttons/Astro_Jump_Level2_Button.png";
static const wstring	W_LEVEL3_PATH = L"data/gui/buttons/Astro_Jump_Level3_Button.png";

static const wstring	W_SELECT_LEVEL_PATH = L"data/gui/buttons/Astro_Jump_Select_Level_Button.png";
static const wstring	W_EXIT_PATH = L"data/gui/buttons/Astro_Jump_Exit_Button.png";
static const wstring	W_RESTART_PATH = L"data/gui/buttons/Astro_Jump_Restart_Button.png";
static const wstring	W_NEXT_LEVEL_PATH = L"data/gui/buttons/Astro_Jump_Next_Level_Button.png";
static const wstring	W_QUIT_PATH = L"data/gui/buttons/Astro_Jump_Quit_Button.png";
static const wstring	W_HELP_PATH = L"data/gui/buttons/Astro_Jump_Help_Button.png";
static const wstring	W_ABOUT_PATH = L"data/gui/buttons/Astro_Jump_About_Button.png";
static const wstring	W_BACK_PATH = L"data/gui/buttons/Astro_Jump_Back_Button.png";
//EXTRAS WHICH WE DONT USE
static const wstring	W_START_IMAGE_PATH = L"data/gui/buttons/start_game.png";
static const wstring	W_START_IMAGE_MO_PATH = L"data/gui/buttons/start_game_mo.png";
static const wstring	W_EXIT_IMAGE_PATH = L"data/gui/buttons/exit_game.png";
static const wstring	W_EXIT_IMAGE_MO_PATH = L"data/gui/buttons/exit_game_mo.png";
static const wstring	W_QUIT_IMAGE_PATH = L"data/gui/buttons/Astro_Jump_Quit_Button.png";
static const wstring	W_QUIT_IMAGE_MO_PATH = L"data/gui/buttons/quit_mo.png";
static const wstring	W_GRID_CELL_SELECTOR_PATH = L"data/gui/overlays/GridCellSelector.png";

// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";
static const wstring	JUMPING = L"JUMPING";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 20.0f;
static const float		W_GRAVITY = 0.0f;
static const float		JUMPING_BOT_MIN_CYCLES = 30;
static const float		JUMPING_BOT_MAX_CYCLES = 120;
static const float		JUMPING_BOT_MAX_VELOCITY = 40;
static const float		PLAYER_INIT_X = 80.0f;
static const float		PLAYER_INIT_Y = 105.0f;
static const float		JUMP_SPEED = -24.0f;
static const float		PLAYER_SPEED = 6.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;
static const wstring	ATTACKING_RIGHT(L"ATTACKING_RIGHT");
static const wstring	ATTACKING_LEFT(L"ATTACKING_LEFT");
static const wstring	IDLE(L"IDLE");

// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int T_KEY = (unsigned int)'T';
const unsigned int L_KEY = (unsigned int)'L';
const unsigned int F_KEY = (unsigned int)'F';
const unsigned int SHIFT_KEY = VK_SHIFT;
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';