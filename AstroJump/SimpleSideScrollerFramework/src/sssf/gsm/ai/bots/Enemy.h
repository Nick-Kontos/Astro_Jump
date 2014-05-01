#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class Enemy : public AnimatedSprite
{
public:

	int targetAsteroid;

	int getTargetAsteroid(){ return targetAsteroid; }
	void resetTarget(){ targetAsteroid = 0; }
	void think(float x, float y);
};