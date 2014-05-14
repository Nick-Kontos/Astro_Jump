#pragma once
#include "stdafx.h"
#include "sssf\input\KeyEventHandler.h"

class Game;

class AstroJumpKeyEventHandler : public KeyEventHandler
{
public:

	float force;
	bool jumping;
	bool jumped;
	bool pullingback;
	bool pulledback;
	bool space;
	AstroJumpKeyEventHandler()		{ force = 0;
	jumping = false;
	jumped = false;
	pullingback = false;
	pulledback = false;
	space = false;
	}
	~AstroJumpKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
};