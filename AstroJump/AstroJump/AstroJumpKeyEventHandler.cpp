/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

BugsKeyEventHandler.cpp

See BugsKeyEventHandler.h for a class description.
*/

#include "AstroJump\stdafx.h"
#include "AstroJump.h"
#include "AstroJumpKeyEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

/*
handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
key states since the last frame, which can allow us to respond to key presses, including when keys
are held down for multiple frames.
*/
void AstroJumpKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	SpriteManager *spritemanager = gsm->getSpriteManager();
	AnimatedSprite *player = spritemanager->getPlayer();
	Viewport *viewport = game->getGUI()->getViewport();

	//check various things and set the player's animation state


	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		player->rotateClockwise(0.0f);
		//check various things and set the player's animation state

		if (input->isKeyDown(UP_KEY))
		{
			spritemanager->lockScreen = false;
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			spritemanager->lockScreen = false;
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY))
		{
			spritemanager->lockScreen = false;
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY))
		{
			spritemanager->lockScreen = false;
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());
		
		if (input->isKeyDown(A_KEY)){
			//rotate player counter-clockwise
			if (player->getCurrentState() != TURN_LEFT || player->getCurrentState() != PULLEDBACK){
				player->setCurrentState(TURN_LEFT);
			}
			player->rotateCClockwise(4.0f);
		}
		else if (input->isKeyDown(D_KEY)){
			//rotate player clockwise
			if (player->getCurrentState() != TURN_RIGHT || player->getCurrentState() != PULLEDBACK){
				player->setCurrentState(TURN_RIGHT);
			}
			player->rotateClockwise(4.0f);
		}
		else if(!jumping && !pullingback && !pulledback){
			player->setCurrentState(IDLE);
		}
		if (input->isKeyDownForFirstTime(SPACE_KEY))
		{
 			if (!spritemanager->getIsOnAsteriod()){
				spritemanager->attachPlayerToAsteriod(gsm->getPhysics()->world);
				jumping = false;
				jumped = false;
				player->setCurrentState(IDLE);
			}
			else {
					force = 0.0f;
					pullingback = true;
			}
		}
		else if (input->wasHeldDown(SPACE_KEY) && (pullingback == true || pulledback == true))
		{
			if (force < MAX_JUMP_FORCE){
				force += 100.0f;
				if (player->getCurrentState() != PULLBACK){
					player->setCurrentState(PULLBACK);
				}
				pullingback = true;
				pulledback = false;
			}
			else {
				if (player->getCurrentState() != PULLEDBACK){
					player->setCurrentState(PULLEDBACK);
				}
				pulledback = true;
				pullingback = false;
			}		
		}
		if ((pullingback == true || pulledback == true) && !(input->isKeyDown(SPACE_KEY)))
		{
			jumping = true;
			pullingback = false;
			pulledback = false;
			game->getEffectsAudio()->start(L"Media\\Jump.wav");
			player->setCurrentState(JUMPING);
			spritemanager->jumpOffAsteriod(force, gsm->getPhysics()->world);
		}
		if (input->isKeyDown(SHIFT_KEY))
		{
			spritemanager->lockScreen = true;
		}
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;
		cursor->setActiveCursorID(id);
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}