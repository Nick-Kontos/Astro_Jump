/*	
	Author: Richard McKenna

	Physics.h

	This class will be used to manage all game collisions
	and physics. This includes collision detection, and resolution.
	Each frame we will update the collided objects velocities and
	positions accordingly.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Collision.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "Box2D/box2D.h"

const float DEFAULT_GRAVITY = -10.0f;
const float timeStep = 1.0f / 60.0f;



class Physics
{
//private:
public:
	// THIS IS APPLIED TO EVERY SPRITE EVERY FRAME
	float gravity;

	int velocityIt = 6;
	int positionIt = 2;

	// THIS IS THE TIME IN THIS FRAME THAT HAS PASSED SO FAR,
	// NOT THAT ALL GAME OBJECTS WILL BE BROUGHT UP TO THIS MOMENT
	float currentCollisionTime;
	
	b2World *world;

	// THIS IS THE CUSTOM EVENT HANDLER FOR PROVIDING GAME-SPECIFIC
	// EVENTS TO COLLISIONS BETWEEN GAME OBJECTS
	CollisionListener *collisionListener;

	// CONSTRUCDT/DESTRUCTOR
	Physics();
	~Physics();

	// INLINED GET/SET METHODS
	float				getGravity()					{ return gravity;					}
	CollisionListener*	getCollisionListener()			{ return collisionListener;			}
	void				setGravity(float initGravity)									{ gravity = initGravity;						}
	void				setCollisionListener(CollisionListener *initCollisionListener)	{ collisionListener = initCollisionListener;	}

	// PUBLIC METHODS DEFINED INSIDE Physics.cpp - YOU ARE WELCOME TO ADD MORE OR CHANGE WHAT YOU LIKE
	void addSprite(AnimatedSprite *sprite);
	void removeSprite(AnimatedSprite *sprite);
	void update(Game *game);

};

