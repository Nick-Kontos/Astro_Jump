/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	AnimatedSprite.h

	This class represents a sprite that can can
	be used to animate a game character or object.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gui\Viewport.h"
#include "Box2D\Box2D.h"

class AnimatedSprite
{
protected:
	// SPRITE TYPE FOR THIS SPRITE. THE SPRITE TYPE IS THE ID
	// OF AN AnimatedSpriteType OBJECT AS STORED IN THE SpriteManager
	AnimatedSpriteType *spriteType;

	b2Body* body;

	// TRANSPARENCY/OPACITY
	int alpha;

	// THE "current" STATE DICTATES WHICH ANIMATION SEQUENCE 
	// IS CURRENTLY IN USE, BUT IT MAP ALSO BE USED TO HELP
	// WITH OTHER GAME ACTIVITIES, LIKE PHYSICS
	wstring currentState;

	// THE INDEX OF THE CURRENT FRAME IN THE ANIMATION SEQUENCE
	// NOTE THAT WE WILL COUNT BY 2s FOR THIS SINCE THE VECTOR
	// THAT STORES THIS DATA HAS (ID,DURATION) TUPLES
	unsigned int frameIndex;

	// USED TO ITERATE THROUGH THE CURRENT ANIMATION SEQUENCE
	unsigned int animationCounter;

	float spawnX;
	float spawnY;
	float spawnVy;
	float spawnVx;
	float density;
	float friction;
	float radius;
	float rotationInRadians;
	float damping;

public:
	int oxygen = 100;
	wstring oxy;
	// INLINED ACCESSOR METHODS
	float				getDensity()		{ return density; }
	float				getFriction()		{ return friction; }
	float				getRadius()			{ return radius; }
	int					getAlpha()			{ return alpha;				}
	wstring				getCurrentState()	{ return currentState;		}
	wstring*				getOxygen()			{ return &oxy; }
	unsigned int		getFrameIndex()		{ return frameIndex;		}
	AnimatedSpriteType*	getSpriteType()		{ return spriteType;		}
	b2Body*				getBody()			{ return body; }
	float				getSpawnX()			{ return spawnX; }
	float				getSpawnY()			{ return spawnY; }
	float				getSpawnVx()			{ return spawnVx; }
	float				getSpawnVy()			{ return spawnVy; }
	float				getDamping()			{ return damping; }
	float				setDamping(float f)			{ damping = f; }
	float				getRotationInRadians()
	{
		return body->GetAngle();
	}
	float				getX()
	{
		b2Vec2 b = body->GetPosition();
		return (b.x);
	}
	float				getY()
	{
		b2Vec2 b = body->GetPosition();
		return (b.y);
	}
	// INLINED MUTATOR METHODS
	void setAlpha(int initAlpha)
	{	alpha = initAlpha;						}
	void setSpriteType(AnimatedSpriteType *initSpriteType)
	{	spriteType = initSpriteType;			}
	void setDensity(float f)
	{
		density = f;
	}
	void setFriction(float f)
	{
		friction = f;
	}
	void setBody(b2Body* b)
	{
		body = b;
	}
	void setSpawnX(float x)
	{
		spawnX = x;
	}
	void setSpawnY(float y)
	{
		spawnY = y;
	}
	void setSpawnVx(float Vx)
	{
		spawnVx = Vx;
	}
	void setSpawnVy(float Vy)
	{
		spawnVy = Vy;
	}
	void setRadius(float r)
	{
		radius = r;
	}

	// METHODS DEFINED IN AnimatedSprite.cpp
	AnimatedSprite();
	AnimatedSprite(float x, float y, int r);
	~AnimatedSprite();
	void changeFrame();
	unsigned int getCurrentImageID();
	void setCurrentState(wstring newState);
	void updateSprite();
	void addImpulse(float f);
	void addVelocity(float f);
	void rotateClockwise(float increment);
	void rotateCClockwise(float increment);
};