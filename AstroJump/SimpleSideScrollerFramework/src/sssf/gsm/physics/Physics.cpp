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
	world->~b2World();
}

void Physics::setGravity(float initGravity)
{
	b2Vec2 g(0.0f, initGravity);
	world->SetGravity(g);
}

/*
	Informs the physics system of additional dynamic, collidable object
	to keep track of
*/
void Physics::addSprite(AnimatedSprite *sprite)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	float x =0.01f * sprite->getSpawnX();
	float y =0.01f * sprite->getSpawnY();
	bodyDef.position.Set(x, y);
	bodyDef.linearVelocity.Set(sprite->getSpawnVx(), sprite->getSpawnVy());
	bodyDef.userData = &sprite;
	bodyDef.linearDamping = sprite->getDamping();
	b2Body* body = world->CreateBody(&bodyDef);
	b2CircleShape c;
	c.m_p.Set(0,0);
	c.m_radius = sprite->getRadius();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &c;
	fixtureDef.density = sprite->getDensity();
	fixtureDef.friction = sprite->getFriction();
	body->CreateFixture(&fixtureDef);
	sprite->setBody(body);
}

/*
	Removes a dynamic, collidable object from the physics system. Note that
	this method should not be used mid-collision, as a result of a collition 
	event, since it does not update all the swept shape positions. Also note 
	that it does not test to see if the added object overlaps an object already 
	in the game.
*/
void Physics::removeSprite(AnimatedSprite *sprite)
{
	b2Body *b = sprite->getBody();
	world->DestroyBody(b);
	
}

void Physics::update(Game *game)
{
	world->Step(timeStep, velocityIt, positionIt);
}


