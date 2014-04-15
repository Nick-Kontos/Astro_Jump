#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\TopDownSprite.h"

void TopDownSprite::updateSprite()
{
	// CALL THE PARENT METHOD TO UPDATE ANIMATION
	AnimatedSprite::updateSprite();

	// AND NOW CALCULATE THE RADIANS
	// FOR RENDERING THIS SPRITE
	float vX = body->GetLinearVelocity().x;
	float vY = body->GetLinearVelocity().y;
	float epsilon = 0.00001f;

	// IF THE Y VELOCITY IS 0 WE HAVE TO BE CAREFUL DIVIDING
	if (fabs(vY) < epsilon)
	{
		// IF X ISN'T MOVING EITHER, LEAVE IT WHAT IT IS
		// AND PUT IT INTO AN IDLE STATE
		if (fabs(vX) > epsilon)
		{
			if (vX < 0.0f)
			{
				rotationInRadians = Pi;
			}
			else
				rotationInRadians = 0.0f;
		}
	}
	else
	{
		float tanTheta = vY / vX;
		rotationInRadians = atan(tanTheta);
		if (vX < 0.0f)
		{
			if (vY < 0.0f)
				rotationInRadians += Pi;
			else
				rotationInRadians -= Pi;
		}
	}
}