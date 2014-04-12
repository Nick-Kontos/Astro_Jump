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
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "Box2D/box2D.h"

const float DEFAULT_GRAVITY = -10.0f;
const float timeStep = 1.0f / 60.0f;
int velocityIt = 6;
int positionIt = 2;
b2World *world;

class Physics
{
//private:
public:
	// THIS IS APPLIED TO EVERY SPRITE EVERY FRAME
	float gravity;

	// THIS IS THE TIME IN THIS FRAME THAT HAS PASSED SO FAR,
	// NOT THAT ALL GAME OBJECTS WILL BE BROUGHT UP TO THIS MOMENT
	float currentCollisionTime;

	// THIS IS THE CUSTOM EVENT HANDLER FOR PROVIDING GAME-SPECIFIC
	// EVENTS TO COLLISIONS BETWEEN GAME OBJECTS
	CollisionListener *collisionListener;

	// WE USE LISTS BECAUSE WE ONLY REMOVE AND ADD FROM THE END FOR THESE 
	list<Collision*> recycledCollisions;
	list<CollidableObject*> recycledCollidableObjectsList;

	// WE USE A LIST BECAUSE WE'LL NEED TO PERIODICALLY REMOVE
	// FROM THE CENTER, AND WHILE WE DO SORT IT, WE DON'T SEARCH
	// IT FOR SINGLE ELEMENTS
	list<Collision*> activeCollisions;

	// SWEEP AND PRUNE STUFF
	map<unsigned int, vector<CollidableObject*>*> sortedSweptShapes;

	// THIS MAKES SURE WE AREN'T CHECKING A SLIGHLY PENETRATING COLLISION
	// PAIR OVER AND OVER AGAIN. THAT SCENARIO IS VERY HARD TO AVOID
	// IN A CONTINUOUS SYSTEM
	map<CollidableObject*, set<Tile*>> spriteToTileCollisionsThisFrame;

	// USED FOR TESTING PHYSICS BY TURNING IT ON AND OFF IN VARIOUS WAYS
	bool activated;
	bool activatedForSingleUpdate;

	// CONSTRUCDT/DESTRUCTOR
	Physics();
	~Physics();

	// INLINED GET/SET METHODS
	float				getGravity()					{ return gravity;					}
	CollisionListener*	getCollisionListener()			{ return collisionListener;			}
	bool				isActivated()					{ return activated;					}
	bool				isActivatedForSingleUpdate()	{ return activatedForSingleUpdate;	}
	void				activateForSingleUpdate()										{ activatedForSingleUpdate = true;				}
	void				setGravity(float initGravity)									{ gravity = initGravity;						}
	void				setCollisionListener(CollisionListener *initCollisionListener)	{ collisionListener = initCollisionListener;	}

	// PUBLIC METHODS DEFINED INSIDE Physics.cpp - YOU ARE WELCOME TO ADD MORE OR CHANGE WHAT YOU LIKE
	void addCollidableObject(CollidableObject *collidableObjectToAdd);
	void removeCollidableObject(CollidableObject *collidableObjectToRemove);
	void update(Game *game);
	bool willSpriteCollideOnTile(CollidableObject *co, AABB *tileAABB);

};

/*
	Provides a custom criteria for sorting for our swepts shapes when
	we want the sorted by left edge.
*/
struct SweptShapesComparitorByLeft
{
	inline bool operator()(CollidableObject *a, CollidableObject *b)
	{
		AABB *aSH = a->getSweptShape();
		AABB *bSH = b->getSweptShape();
		return aSH->getLeft() < bSH->getLeft();
	}
};

/*
	Provides a custom criteria for sorting for our swepts shapes when
	we want the sorted by right edge.
*/
struct SweptShapesComparitorByRight
{
	inline bool operator()(CollidableObject *a, CollidableObject *b)
	{
		AABB *aSH = a->getSweptShape();
		AABB *bSH = b->getSweptShape();
		return aSH->getRight() < bSH->getRight();
	}
};