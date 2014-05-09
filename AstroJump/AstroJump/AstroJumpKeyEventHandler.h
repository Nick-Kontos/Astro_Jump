#pragma once
#include "stdafx.h"
#include "sssf\input\KeyEventHandler.h"

class Game;

class AstroJumpKeyEventHandler : public KeyEventHandler
{
public:

	float force;
	bool jumping;
	bool space;
	AstroJumpKeyEventHandler()		{ force = 0;
	jumping = false;
	space = false;
	}
	~AstroJumpKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
};