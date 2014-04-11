#pragma once
#include "stdafx.h"
#include "sssf\input\ButtonEventHandler.h"

class Game;

class AstroJumpButtonEventHandler : public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	AstroJumpButtonEventHandler()	{}
	~AstroJumpButtonEventHandler()	{}

	// DEFINED INSIDE BugsButtonEventHandler.cpp
	void handleButtonEvents(Game *game,
		wstring command);
};