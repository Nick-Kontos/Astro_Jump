#pragma once
#include "stdafx.h"
#include "sssf\input\KeyEventHandler.h"

class Game;

class AstroJumpKeyEventHandler : public KeyEventHandler
{
public:
	AstroJumpKeyEventHandler()		{}
	~AstroJumpKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
};