#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

static const float Pi = 3.1415926535897932384626433f;

class TopDownSprite : public AnimatedSprite
{
protected:
	// USED TO RENDER A ROTATED SPRITE, NOT INVOLVED IN PHYSICS
	float rotationInRadians;

public:
    
	float getRotationInRadians()
	{
		return rotationInRadians;
	}
	void setRotationInRadians(float initRotation)
	{
		rotationInRadians = initRotation;
	}
	void updateSprite();
};