#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class BlackHole : public AnimatedSprite
{
public:
	float speed;
	bool over;
	float getDistance(float x, float y);
};