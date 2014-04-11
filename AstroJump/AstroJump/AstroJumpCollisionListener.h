#pragma once

#include "stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\physics\Collision.h"

class AstroJumpCollisionListener : public CollisionListener
{
public:
	void respondToCollision(Game *game, Collision *collision);
};