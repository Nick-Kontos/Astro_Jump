/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	Physics.cpp

	See Physics.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\physics\Collision.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\world\SparseLayer.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\WorldLayer.h"
#include <vector>
#include <list>
#include "Box2D\Box2D.h"

/*
	The constructor initializes the data structures and loads
	the necessary ones with recyclable objects for collision tests.
*/
Physics::Physics()
{
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, DEFAULT_GRAVITY);

	// Construct a world object
	world = new b2World(gravity);


	
}

/*
	The destructor deletes all the recyclable objects.
*/
Physics::~Physics()
{
	// WE ARE DONE WITH ALL OF THESE
	world->~b2World();
}

/*
	Informs the physics system of additional dynamic, collidable object
	to keep track of
*/
void Physics::addCollidableObject(CollidableObject *collidableObjectToAdd)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	int x = collidableObjectToAdd->getPhysicalProperties()->getX();
	int y = collidableObjectToAdd->getPhysicalProperties()->getY();
	bodyDef.position.Set(x, y);
	bodyDef.userData = &collidableObjectToAdd;
	b2Body* body = world->CreateBody(&bodyDef);
	b2PolygonShape box;
	int width = collidableObjectToAdd->getBoundingVolume()->getWidth()/2;
	int height = collidableObjectToAdd->getBoundingVolume()->getHeight() / 2;
	box.SetAsBox(width, height);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = collidableObjectToAdd->getPhysicalProperties()->getDensity();
	fixtureDef.friction = collidableObjectToAdd->getPhysicalProperties()->getFriction();
	body->CreateFixture(&fixtureDef);
}

/*
	Removes a dynamic, collidable object from the physics system. Note that
	this method should not be used mid-collision, as a result of a collition 
	event, since it does not update all the swept shape positions. Also note 
	that it does not test to see if the added object overlaps an object already 
	in the game.
*/
void Physics::removeCollidableObject(CollidableObject *collidableObjectToRemove)
{
	b2Body b = collidableObjectToRemove->getBody();
}

/*
	This is where all game physics starts each frame. It is called each frame 
	by the game statem manager after player input and AI have been processed. It
	updates the physical state of all dynamic objects in the game and
	moves all objects to their end of frame positions, updates all necessary
	object velocities, and calls all collision event handlers.
*/
void Physics::update(Game *game)
{
	world->Step(timeStep, velocityIt, positionIt);
}

/*
	This method helps us employ walking and jumping on/from tiles. It is a look
	ahead function which basically tells us if the sprite (co) will collide
	on top of the tile's AABB.
*/
bool Physics::willSpriteCollideOnTile(CollidableObject *co, AABB *tileAABB)
{
	float yDiff = tileAABB->getTop() - co->getBoundingVolume()->getBottom() - co->getPhysicalProperties()->getVelocityY();
	if (yDiff < 0.0f)
		return true;
	else
		return false;
}

