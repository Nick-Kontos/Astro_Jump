#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\TopDownSprite.h"

void TopDownSprite::updateSprite()
{
	// CALL THE PARENT METHOD TO UPDATE ANIMATION
	frameCount++;
	if (frameCount >= 30)
	{
		frameCount = 0;
		oxygen--;
	}
	AnimatedSprite::updateSprite();

}