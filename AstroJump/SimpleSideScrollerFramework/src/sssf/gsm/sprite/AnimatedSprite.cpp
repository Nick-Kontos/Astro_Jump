/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.cpp

	See AnimatedSprite.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "Box2D\Box2D.h"

/*
	AnimatedSprite - Default constructor, just sets everything to 0.
*/
AnimatedSprite::AnimatedSprite()
{
	radius = 0;
	spriteType = 0;
	frameIndex = 0;
	animationCounter = 0;
	spawnVx = 0;
	spawnVy = 0;
	spawnX = 0;
	spawnY = 0;
	density = 1.0f;
	friction = .3f;
	damping = 1.0f;
	oxy = L"OXYGEN LEVEL: " + to_wstring(oxygen);
}
AnimatedSprite::AnimatedSprite(float x, float y, int r)  
{
	radius = r;
	spriteType = 0;
	frameIndex = 0;
	animationCounter = 0;
	spawnVx = 0;
	spawnVy = 0;
	spawnX = x;
	spawnY = y;
	density = 1.0f;
	friction = .3f;
	damping = 1.0f;
}

/*
	Destructor - Nothing to clean up. We don't want to clean up the
	sprite type because it is a shared variable.
*/
AnimatedSprite::~AnimatedSprite() 
{

}

/*
	changeFrame - This method allows for the changing of an image in an 
	animation sequence for a given animation state.
*/
void AnimatedSprite::changeFrame()
{
	// RESET THE COUNTER
	animationCounter = 0;

	// REMEMBER, WE COUNT BY 2s
	frameIndex += 2;

	// GO BACK TO FIRST INDEX IF NECESSARY
	if (frameIndex == spriteType->getSequenceSize(currentState))
		frameIndex = 0;
}

/*
	getCurrentImageID - This method does the work of retrieving
	the image id that corresponds to this sprite's current state
	and frame index.
*/
unsigned int AnimatedSprite::getCurrentImageID()
{
	return spriteType->getAnimationFrameID(currentState, frameIndex);
}

/*
	setCurrentState - This method sets this sprite to the newState
	state and starts its animtion sequence from the beginning.
*/
void AnimatedSprite::setCurrentState(wstring newState) 
{
	string cs(currentState.begin(), currentState.end());
	string ns(newState.begin(), newState.end());
	if (strcmp(cs.c_str(), ns.c_str()) != 0)
	{
		// SET THE ANIMATINO STATE
		currentState = newState;

		// AND RESET OUR COUNTERS
		animationCounter = 0;
		frameIndex = 0;
	}
}

/*
	updateSprite - To be called every frame of animation. This
    method advances the animation counter appropriately per
	the animation speed. It also updates the sprite location
	per the current velocity.
*/
void AnimatedSprite::updateSprite()
{
	unsigned int duration = spriteType->getDuration(currentState, frameIndex);
	animationCounter++;
	if (oxygen >= 0)
		oxy = L"OXYGEN LEVEL: " + to_wstring(oxygen);
	else
		oxy = L"OXYGEN LEVEL: 0";

	// WE ONLY CHANGE THE ANIMATION FRAME INDEX WHEN THE
	// ANIMATION COUNTER HAS REACHED THE DURATION
	if (animationCounter >= duration)
		changeFrame();
}
void AnimatedSprite::rotateClockwise(float increment)
{
	//to impulse or not to impulse?
	body->SetAngularVelocity(increment);
	//body->ApplyAngularImpulse(increment, true);
}
void AnimatedSprite::rotateCClockwise(float increment)
{
	//to impulse or not to impulse?
	body->SetAngularVelocity(-increment);
	//body->ApplyAngularImpulse(increment, true);
}