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
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "Box2D/box2D.h"

const float DEFAULT_GRAVITY = 0.0f;
const float timeStep = 1.0f / 60.0f;



class Physics
{
//private:
public:
	// THIS IS APPLIED TO EVERY SPRITE EVERY FRAME
	float gravity;

	int velocityIt = 8;
	int positionIt = 4;
	
	b2World *world;


	// CONSTRUCDT/DESTRUCTOR
	Physics();
	~Physics();
	Physics(float f1, float f2);

	// INLINED GET/SET METHODS
	float				getGravity()					{ return gravity;					}
	void				setGravity(float initGravity);

	// PUBLIC METHODS DEFINED INSIDE Physics.cpp - YOU ARE WELCOME TO ADD MORE OR CHANGE WHAT YOU LIKE
	void constructBoundries(int height, int width);
	void addSprite(AnimatedSprite *sprite);
	void addPlayer(AnimatedSprite *player, float x, float y);
	void addEnemy(AnimatedSprite *enemy, float x, float y);
	void addAsteriod(AnimatedSprite *asteriod, float x, float y);
	void removeSprite(AnimatedSprite *sprite);
	void update(Game *game);

};

