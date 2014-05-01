
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
#include "sssf\gsm\physics\MyContactListener.h"
#include <vector>
#include <list>
#include "Box2D\Box2D.h"

MyContactListener::MyContactListener(Game *g)
{
	game = g;
}

void MyContactListener::BeginContact(b2Contact *contact){
	if (getPlayerAndAsteriod(contact)){
		game->getGSM()->getSpriteManager()->setIsOverAsteriod(true);
	}
}

void MyContactListener::EndContact(b2Contact *contact){
	if (getPlayerAndAsteriod(contact)){
		game->getGSM()->getSpriteManager()->setIsOverAsteriod(false);
	}
}

bool MyContactListener::getPlayerAndAsteriod(b2Contact *contact)
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