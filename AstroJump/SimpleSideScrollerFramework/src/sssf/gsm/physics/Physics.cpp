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
	map<CollidableObject*,set<Tile*>>::iterator tileSetToRemoveIt = spriteToTileCollisionsThisFrame.find(collidableObjectToRemove);
	spriteToTileCollisionsThisFrame.erase(tileSetToRemoveIt);
	removeCollidableObject(LEFT_EDGE,	collidableObjectToRemove);
	removeCollidableObject(RIGHT_EDGE,	collidableObjectToRemove);
}

/*
	Called when a collision is detected between a world tile
	and a sprite, this records that collision so that it
	can be resolved later if needed.
*/
void Physics::addTileCollision(CollidableObject *dynamicObject, Tile *tile, float tileX, float tileY, float tileWidth, float tileHeight)
{
	// IF WE'VE ALREADY HANDLED A COLLISION BETWEEN THESE TWO OBJECTS THIS
	// FRAME THEN IGNORE IT
	set<Tile*> doTiles = spriteToTileCollisionsThisFrame[dynamicObject];
	if (doTiles.find(tile) != doTiles.end())
		return;

	// GET A DUMMY COLLIABLE OBJECT TO USE FOR THE TILE
	CollidableObject *tileInfoForCollision = recycledCollidableObjectsList.back();

	// FILL IT WITH DATA
	AABB *bv = tileInfoForCollision->getBoundingVolume();
	bv->setCenterX(tileX + (tileWidth/2));
	bv->setCenterY(tileY + (tileHeight/2));
	bv->setWidth(tileWidth);
	bv->setHeight(tileHeight);

	// FIRST WE'RE GOING TO DO A MORE NARROW CHECK TO SEE IF THE dynamicObject
	// REALLY DOES COLLIDE WITH THE TILE. TO DO SO WE'LL CALCULATE THE TIME
	// OF COLLISION. IF IT HAPPENS AFTER THIS FRAME IS OVER (> 1), THEN WE
	// WILL IGNORE IT
	unsigned int co1Edge, co2Edge;
	float timeUntilCollision = calculateTimeUntilCollision(dynamicObject, tileInfoForCollision, co1Edge, co2Edge, 0.0f);
	if (timeUntilCollision > 1.0f)
		return;

	// IF IT MADE IT HERE, A COLLISION IS HAPPENING
	// AND REMOVE IT FROM THE RECYCLING CENTER
	recycledCollidableObjectsList.pop_back();

	// NOW LET'S MAKE A COLLISION FOR THE TILE-SPRITE
	Collision *collisionToAdd = recycledCollisions.back();
	collisionToAdd->setCO1(dynamicObject);
	collisionToAdd->setCO2(tileInfoForCollision);
	collisionToAdd->setCO1Edge(co1Edge);
	collisionToAdd->setCO2Edge(co2Edge);
	collisionToAdd->setCollisionWithTile(true);
	collisionToAdd->setTimeOfCollision(timeUntilCollision);
	collisionToAdd->setTile(tile);
	recycledCollisions.pop_back();
	activeCollisions.push_back(collisionToAdd);
}

void Physics::addSpriteCollision(CollidableObject *sprite1, CollidableObject *sprite2)
{
	unsigned int co1Edge, co2Edge;
	float timeUntilCollision = calculateTimeUntilCollision(sprite1, sprite2, co1Edge, co2Edge, 0.0f);
	if (timeUntilCollision > 1.0f)
		return;

	// NOW LET'S MAKE A COLLISION FOR THE TILE-SPRITE
	Collision *collisionToAdd = recycledCollisions.back();
	collisionToAdd->setCO1(sprite1);
	collisionToAdd->setCO2(sprite2);
	collisionToAdd->setCO1Edge(co1Edge);
	collisionToAdd->setCO2Edge(co2Edge);
	collisionToAdd->setCollisionWithTile(false);
	collisionToAdd->setTimeOfCollision(timeUntilCollision);
	recycledCollisions.pop_back();
	activeCollisions.push_back(collisionToAdd);
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

