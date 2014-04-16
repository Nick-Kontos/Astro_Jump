/*
Author: Richard McKenna
Stony Brook University
Computer Science Department

BugsTextGenerator.cpp

See BugsTextGenerator.h for a class description.
*/

#include "AstroJump\stdafx.h"
#include "AstroJump.h"
#include "AstroJumpTextGenerator.h"
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\text\GameText.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

static const wstring	W_MOUSE_COORDS_TEXT = L"Mouse: (";
static const int		W_TEXT_X = 200;
static const int		W_TEXT_Y = 10;
static const int		W_PATHFINDING_TEXT_X = 800;
static const int		W_PATHFINDING_TEXT_Y = 10;
static const wstring	W_ROTATION_IN_RADIANS = L"Ant Rotation in Radians: ";
static const wstring	W_ROTATION_IN_DEGREES = L"Ant Rotation in Degrees: ";
static const wstring	W_RADIANS = L" radians";
static const wstring	W_DEGREES = L" degrees";
static const wstring	SIN_THETA = L"sin(theta): ";
static const wstring	COS_THETA = L"cos(theta): ";
static const wstring	W_ANT_CENTER_TEXT = L"Ant Center: (";
static const wstring	W_ANT_GRID_TEXT = L"Ant Center Col,Row: (";
static const wstring	W_ANT_LEFT_TOP_TEXT = L"Ant Left, Top: (";
static const wstring	W_ANT_RIGHT_BOTTOM_TEXT = L"Ant Right, Bottom: (";

void AstroJumpTextGenerator::appendPathfindingText(Game *game)
{
	wstringstream wss;
	if (game->getGSM()->isGameInProgress())
	{
		/*
		GridPathfinder *pathfinder = game->getGSM()->getSpriteManager()->getPathfinder();
		TopDownSprite *ant = game->getGSM()->getSpriteManager()->getPlayer();
		pathfindingText.append(W_ANT_CENTER_TEXT);
		wss << ant->getBoundingVolume()->getCenterX();
		wss << L", ";
		wss << ant->getBoundingVolume()->getCenterY();
		wss << L")\n";
		wss << W_ANT_GRID_TEXT;
		int col = (int)(ant->getBoundingVolume()->getCenterX() / pathfinder->getGridWidth());
		wss << col;
		wss << L", ";
		int row = ant->getBoundingVolume()->getCenterY() / pathfinder->getGridHeight();
		wss << row;
		wss << L")\n";
		wss << W_ANT_LEFT_TOP_TEXT;
		wss << ant->getPhysicalProperties()->getX();
		wss << ", ";
		wss << ant->getPhysicalProperties()->getY();
		wss << ")\n";
		wss << W_ANT_RIGHT_BOTTOM_TEXT;
		wss << ant->getPhysicalProperties()->getX() + ant->getSpriteType()->getTextureWidth();
		wss << ", ";
		wss << ant->getPhysicalProperties()->getY() + ant->getSpriteType()->getTextureHeight();
		wss << ")\n";
		pathfindingText.append(wss.str());
		*/
	}
}

void AstroJumpTextGenerator::appendMouseCoords(Game *game)
{
	wstringstream wss;
	WindowsInput *input = (WindowsInput*)game->getInput();
	textToGenerate.append(W_MOUSE_COORDS_TEXT);
	wss << input->getMousePoint()->x;
	wss << L", ";
	wss << input->getMousePoint()->y;
	wss << L")";
	wss << L"\n";
	textToGenerate.append(wss.str());
}

void AstroJumpTextGenerator::appendAntRotationInfo(Game *game)
{
	wstringstream wss;
	TopDownSprite *ant = game->getGSM()->getSpriteManager()->getPlayer();
	float rad = ant->getRotationInRadians();

	wss << W_ROTATION_IN_RADIANS;
	wss << rad;
	wss << W_RADIANS + L"\n";
	wss << W_ROTATION_IN_DEGREES;
	wss << (rad * 180) / PI;
	wss << W_DEGREES + L"\n";
	wss << SIN_THETA;
	wss << sin(rad);
	wss << L"\n";
	wss << COS_THETA;
	wss << cos(rad);
	wss << L"\n";
	textToGenerate.append(wss.str());
}

/*
initText - Provides an example of how to render text to our screen every frame,
allowing for the text to continually change. This method adds a text object
to the text manager (GameText), which allows it to be updated each frame. This
method should be called only once for each object.
*/
void AstroJumpTextGenerator::initText(Game *game)
{
	/*
	// FIRST UPDATE THE TEXT THIS GENERATOR IS USING
	appendMouseCoords(game);

	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();
	text->addText(&textToGenerate, W_TEXT_X, W_TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());

	// LET'S ALSO DISPLAY SOME STUFF FOR PATHFINDING
	appendPathfindingText(game);
	text->addText(&pathfindingText, W_PATHFINDING_TEXT_X, W_PATHFINDING_TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight
	*/
}

/*
updateText - updates the text. Note that the text must already have been added
to the text manager via the initText method. Also not that there should be a
separate TextGenerator for each line of text we wish to render.
*/
void AstroJumpTextGenerator::updateText(Game *game)
{
	// THE TEXT MANAGER (GameText) HAS A POINTER TO OUR TEXT, SO WE CAN
	// SIMPLY CLEAR IT OUT OF OLD CHARACTER DATA AND FILL IT IN WITH
	// WHAT WE WANT.
	/*
	textToGenerate.clear();
	appendMouseCoords(game);
	appendAntRotationInfo(game);

	pathfindingText.clear();
	appendPathfindingText(game);
	*/
}

