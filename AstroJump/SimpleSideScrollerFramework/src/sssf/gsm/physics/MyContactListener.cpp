
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\world\SparseLayer.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\WorldLayer.h"
#include "sssf\gsm\physics\MyContactListener.h"
#include <vector>
#include <list>

MyContactListener::MyContactListener(SpriteManager *sm)
{
	spritemanager = sm;
}

void MyContactListener::BeginContact(b2Contact* contact){
	if (getPlayerAndAsteriod(contact)){
		spritemanager->setIsOverAsteriod(true);
	}
}

void MyContactListener::EndContact(b2Contact* contact){
	if (getPlayerAndAsteriod(contact)){
		spritemanager->setIsOverAsteriod(false);
	}
}

bool MyContactListener::getPlayerAndAsteriod(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();
	if (!(sensorA ^ sensorB))
		return false;
	return true;
}