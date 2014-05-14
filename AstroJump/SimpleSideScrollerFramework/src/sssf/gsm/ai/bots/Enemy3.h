#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class Enemy3 : public AnimatedSprite
{
public:
	float distance;
	float speed;
	void think(float x, float y);
};