#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

static const float Pi = 3.1415926535897932384626433f;

class TopDownSprite : public AnimatedSprite
{
protected:
	// USED TO RENDER A ROTATED SPRITE, NOT INVOLVED IN PHYSICS
	float rotationInRadians;
	int frameCount = 0;

public:
    
	void updateSprite();
};