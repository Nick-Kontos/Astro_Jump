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
#include "sssf\gsm\sprite\SpriteManager.h"

/*
	The default constructor initializes box2D.
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
	gravity = initGravity;
	world->SetGravity(g);
}

void Physics::initContactListener(SpriteManager *sm)
{
	//ILLEGAL listener is out of scope
	spritemanager = sm;
	world->SetContactListener(spritemanager);
}

/*
	Informs the physics system of additional dynamic, collidable object
	to keep track of
*/
void Physics::addSprite(AnimatedSprite *sprite)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	float x = sprite->getSpawnX();
	float y = sprite->getSpawnY();
	bodyDef.position.Set(x, y);
	b2Vec2* initforce = new b2Vec2(sprite->getSpawnVx(), sprite->getSpawnVy());	
	bodyDef.userData = sprite;
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
	sprite->getBody()->ApplyForceToCenter(*initforce, true);
}
void Physics::addEnemy(AnimatedSprite *player, float x, float y)
{
	//add some things to the sprite fields
	player->setRadius(player->getSpriteType()->getTextureWidth() / 2 * .02f);
	player->setSpawnX(x);
	player->setSpawnY(y);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(player->getSpawnX(), player->getSpawnY());
	bodyDef.userData = player;
	bodyDef.linearDamping = player->getDamping();
	b2Body* body = world->CreateBody(&bodyDef);

	//create the fixture
	b2CircleShape c;
	c.m_p.Set(0, 0);
	c.m_radius = player->getRadius();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &c;
	fixtureDef.density = player->getDensity();
	fixtureDef.friction = player->getFriction();
	//add collision filtering
	//player is 0 bit
	fixtureDef.filter.categoryBits = 4;
	//they collide with world boundries
	fixtureDef.filter.maskBits = 5;
	//set restitution values
	fixtureDef.restitution = 0.7f;
	body->CreateFixture(&fixtureDef);

	player->setBody(body);

	//add an initial velocity
	b2Vec2* initforce = new b2Vec2(x, y);
	player->getBody()->ApplyForceToCenter(*initforce, true);

}
void Physics::addPlayer(AnimatedSprite *player, float x, float y)
{
	//add some things to the sprite fields
	player->setRadius(player->getSpriteType()->getTextureHeight() / 2 * .02f);
	player->setSpawnX(x);
	player->setSpawnY(y);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(player->getSpawnX(), player->getSpawnY());
	bodyDef.userData = player;
	bodyDef.linearDamping = player->getDamping();
	b2Body* body = world->CreateBody(&bodyDef);

	//create the fixture
	b2CircleShape c;
	c.m_p.Set(0, 0);
	c.m_radius = player->getRadius();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &c;
	fixtureDef.density = player->getDensity();
	fixtureDef.friction = player->getFriction();
	//add collision filtering
	//player is 0 bit
	fixtureDef.filter.categoryBits = 4;
	//they collide with world boundries
	fixtureDef.filter.maskBits = 5;
	//set restitution values
	fixtureDef.restitution = 0.7f;
	body->CreateFixture(&fixtureDef);
	//now create a sensor fixture for detecting collision with asteriods
	b2FixtureDef sensor;
	sensor.shape = &c;
	sensor.density = 0;
	sensor.isSensor = true;
	sensor.filter.maskBits = 2;
	body->CreateFixture(&sensor);

	player->setBody(body);

	//add an initial velocity
	b2Vec2* initforce = new b2Vec2(x, y);
	player->getBody()->ApplyForceToCenter(*initforce, true);
}

void Physics::addAsteriod(AnimatedSprite *asteriod, float x, float y)
{
	//add some things to the sprite fields
	asteriod->setRadius(asteriod->getSpriteType()->getTextureWidth() / 2 * .02f);
	asteriod->setSpawnX(x);
	asteriod->setSpawnY(y);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);	
	bodyDef.userData = asteriod;
	bodyDef.linearDamping = asteriod->getDamping();
	b2Body* body = world->CreateBody(&bodyDef);

	//create the fixture
	b2CircleShape c;
	c.m_p.Set(0, 0);
	c.m_radius = asteriod->getRadius();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &c;
	fixtureDef.density = asteriod->getDensity();
	fixtureDef.friction = asteriod->getFriction();
	//add collision filtering
	//asteriods are 2 bit
	fixtureDef.filter.categoryBits = 2;
	//they collide with walls and other asteriods
	fixtureDef.filter.maskBits = 3;
	//set resitution values
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);
	asteriod->setBody(body);

	//add an initial velocity
	asteriod->getBody()->ApplyForceToCenter(b2Vec2(asteriod->getSpawnVx(), asteriod->getSpawnVy()), true);
}

void Physics::constructBoundries(int height, int width)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2EdgeShape edgeShape;
	edgeShape.Set(b2Vec2(0, 0), b2Vec2(width, 0));
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &edgeShape;
	//add north boundary
	b2Body* northbound = world->CreateBody(&myBodyDef);
	northbound->CreateFixture(&myFixtureDef);
	//add west boundary
	edgeShape.Set(b2Vec2(0, 0), b2Vec2(0, height));
	myFixtureDef.shape = &edgeShape;
	b2Body* westbound = world->CreateBody(&myBodyDef);
	westbound->CreateFixture(&myFixtureDef);
	//add south boundary
	edgeShape.Set(b2Vec2(0, height), b2Vec2(width, height));
	myFixtureDef.shape = &edgeShape;
	b2Body* southbound = world->CreateBody(&myBodyDef);
	southbound->CreateFixture(&myFixtureDef);
	//add east boundary
	edgeShape.Set(b2Vec2(width, 0), b2Vec2(width, height));
	myFixtureDef.shape = &edgeShape;
	b2Body* eastbound = world->CreateBody(&myBodyDef);
	eastbound->CreateFixture(&myFixtureDef);

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


