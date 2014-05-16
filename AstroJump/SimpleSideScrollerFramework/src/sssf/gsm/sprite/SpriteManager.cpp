/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.cpp

	See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\BlackHole.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"

/*
	addSpriteToRenderList - This method checks to see if the sprite
	parameter is inside the viewport. If it is, a RenderItem is generated
	for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	
	// IS THE SPRITE VIEWABLE?
	
	if (viewport->areWorldCoordinatesInViewport(	
									sprite->getX() / .02f,
									sprite->getY() / .02f,
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight()))
	{
	
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		int x = (int)floor(((sprite->getX() / .02f) - viewport->getViewportX()) + 0.5f) - spriteType->getTextureWidth() / 2;
		int y = (int)floor(((sprite->getY() / .02f) - viewport->getViewportY()) + 0.5f) - spriteType->getTextureHeight() / 2;

		renderList->addRenderItem(	sprite->getCurrentImageID(),
			(int)floor(((sprite->getX() / .02f) - viewport->getViewportX())) - spriteType->getTextureWidth()/2,
			(int)floor(((sprite->getY() / .02f) - viewport->getViewportY())) - spriteType->getTextureHeight() / 2,
									0,
									sprite->getAlpha(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight(),
									sprite->getRotationInRadians());
	}
}

//void SpriteManager::addBackgroundToRender(AnimatedSprite *backgroundsprite, RenderList *renderList, Viewport *viewport)
//{
//	AnimatedSpriteType *spriteType = backgroundsprite->getSpriteType();
//	renderList->addRenderItem(backgroundsprite->getCurrentImageID(),
//								0 - viewport->getViewportX() + 0.5f,
//								0 - viewport->getViewportY() + 0.5f,
//								0, 255, spriteType->getTextureWidth(), spriteType->getTextureHeight(), 0);
//}

void SpriteManager::addGUISpriteToRenderList(	AnimatedSprite *sprite,
											RenderList *renderList,
											Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();

	RenderItem itemToAdd;
	itemToAdd.id = sprite->getFrameIndex();
	renderList->addRenderItem(sprite->getCurrentImageID(),
		(int)floor((sprite->getX() - viewport->getViewportX()) + 0.5f),
		(int)floor((sprite->getY() - viewport->getViewportY()) + 0.5f),
		0,
		sprite->getAlpha(),
		spriteType->getTextureWidth(),
		spriteType->getTextureHeight(),
		sprite->getRotationInRadians());
}
/*
	addSpriteItemsToRenderList - This method goes through all of the sprites,
	including the player sprite, and adds the visible ones to the render list.
	This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{

		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();
		//add background image
		//add platforms
		vector<AnimatedSprite*>::iterator platformsIterator;
		platformsIterator = platforms.begin();
		while (platformsIterator != platforms.end())
		{
			AnimatedSprite *platform = (*platformsIterator);
			addSpriteToRenderList(platform, renderList, viewport);
			platformsIterator++;
		}
		//add BlackHoles
		vector<BlackHole*>::iterator BlackHoleIterator;
		BlackHoleIterator = bH.begin();
		while (BlackHoleIterator != bH.end())
		{
			AnimatedSprite *platform = (*BlackHoleIterator);
			addSpriteToRenderList(platform, renderList, viewport);
			BlackHoleIterator++;
		}
		//add asteroids
		vector<AnimatedSprite*>::iterator asteroidsIterator;
		asteroidsIterator = asteroids.begin();
		while (asteroidsIterator != asteroids.end())
		{
			AnimatedSprite *asteroid = (*asteroidsIterator);
			addSpriteToRenderList(asteroid, renderList, viewport);
			asteroidsIterator++;
		}
		addSpriteToRenderList(&winAsteroid, renderList, viewport);
		vector<PowerUp*>::iterator PowerUpIterator;

		vector<PowerUp*>::iterator portalsIterator;
		portalsIterator = portals.begin();
		while (portalsIterator != portals.end())
		{
			AnimatedSprite *power = (*portalsIterator);
			addSpriteToRenderList(power, renderList, viewport);
			portalsIterator++;
		}
		PowerUpIterator = powerUps.begin();
		while (PowerUpIterator != powerUps.end())
		{
			AnimatedSprite *power = (*PowerUpIterator);
			addSpriteToRenderList(power, renderList, viewport);
			PowerUpIterator++;
		}
		// NOW ADD THE REST OF THE SPRITES
		vector<Enemy*>::iterator enemyIterator;
		enemyIterator = enemies.begin();
		while (enemyIterator != enemies.end())
		{			
			Enemy *enemy = (*enemyIterator);
			addSpriteToRenderList(enemy, renderList, viewport);
			enemyIterator++;
		}
		vector<Enemy2*>::iterator enemy2Iterator;
		enemy2Iterator = enemies2.begin();
		while (enemy2Iterator != enemies2.end())
		{
			Enemy2 *enemy = (*enemy2Iterator);
			addSpriteToRenderList(enemy, renderList, viewport);
			enemy2Iterator++;
		}
		vector<Enemy3*>::iterator enemy3Iterator;
		enemy3Iterator = enemies3.begin();
		while (enemy3Iterator != enemies3.end())
		{
			Enemy3 *enemy = (*enemy3Iterator);
			addSpriteToRenderList(enemy, renderList, viewport);
			enemy3Iterator++;
		}
		//add GUI sprites
		//addGUISpriteToRenderList(&healthbar, renderList, viewport);
		//addGUISpriteToRenderList(&lives, renderList, viewport);

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);
	}
}

/*
	addSprite - This method is for adding a new sprite to 
	this sprite manager. Once a sprite is added it can be 
	scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}
void SpriteManager::addEnemy(Enemy *enemyToAdd)
{
	enemies.push_back(enemyToAdd);
}
void SpriteManager::addEnemy2(Enemy2 *enemyToAdd)
{
	enemies2.push_back(enemyToAdd);
}
void SpriteManager::addEnemy3(Enemy3 *enemyToAdd)
{
	enemies3.push_back(enemyToAdd);
}

void SpriteManager::addAsteriod(AnimatedSprite *asteriodToAdd)
{
	asteroids.push_back(asteriodToAdd);
}

void SpriteManager::addPlatform(AnimatedSprite *platformToAdd)
{
	platforms.push_back(platformToAdd);
}
void SpriteManager::addBlackHole(BlackHole *bhToAdd)
{
	bH.push_back(bhToAdd);
}
void SpriteManager::addPowerUp(PowerUp *p)
{
	if (p->type < 3)
		powerUps.push_back(p);
	else
		portals.push_back(p);
}
/*
	addSpriteType - This method is for adding a new sprite
	type. Note that one sprite type can have many sprites. For
	example, we may say that there may be a "Bunny" type of
	sprite, and specify properties for that type. Then there might
	be 100 different Bunnies each with their own properties, but that
	share many things in common according to what is defined in
	the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
	clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	spriteTypes.clear();
	bots.clear();
}

/*
	getSpriteType - This gets the sprite type object that cborresponds
	to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
	unloadSprites - This method removes all artwork from memory that
	has been allocated for game sprites.
*/
void SpriteManager::unloadSprites(GameStateManager *gsm)
{
	Physics *physic = gsm->getPhysics();
	while (asteroids.size()>=1)
	{
		AnimatedSprite *asteroid = asteroids.back();
		physic->removeSprite(asteroid);		
		asteroids.pop_back();
	}
	while (enemies.size() >= 1)
	{
		AnimatedSprite *enemy = enemies.back();
		physic->removeSprite(enemy);
		enemies.pop_back();
	}
	while (enemies2.size() >= 1)
	{
		AnimatedSprite *enemy = enemies2.back();
		physic->removeSprite(enemy);
		enemies2.pop_back();
	}
	while (enemies3.size() >= 1)
	{
		AnimatedSprite *enemy = enemies3.back();
		physic->removeSprite(enemy);
		enemies3.pop_back();
	}
	while (platforms.size() >= 1)
	{
		AnimatedSprite *platform = platforms.back();
		physic->removeSprite(platform);
		platforms.pop_back();
	}
	while (bH.size() >= 1)
	{
		AnimatedSprite *blackHole = bH.back();
		physic->removeSprite(blackHole);
		bH.pop_back();
	}
	while (powerUps.size() >= 1)
	{
		AnimatedSprite *p = powerUps.back();
		physic->removeSprite(p);
		powerUps.pop_back();
	}
	while (portals.size() >= 1)
	{
		AnimatedSprite *p = portals.back();
		physic->removeSprite(p);
		portals.pop_back();
	}
	physic->removeSprite(&player);
	isOnAsteriod = true;
	physic->removeSprite(&winAsteroid);
	won = false;
	isOverAsteriod = true;

}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	return NULL;
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
}
/*
void SpriteManager::findSpriteCollisionsForSprite(Physics *physics, CollidableObject *sprite){
	AABB *ss1 = sprite->getSweptShape();
	AABB *ss2;
	list<Bot*>::iterator botsIt = bots.begin();
	while (botsIt != bots.end()){
		CollidableObject *sprite2 = (*botsIt);
		ss2 = sprite2->getSweptShape();
		if (ss1->overlaps(ss2)){
			physics->addSpriteCollision(sprite, sprite2);
		}
		botsIt++;
	}
}
*/
/*
	update - This method should be called once per frame. It
	goes through all of the sprites, including the player, and calls their
	update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	// UPDATE THE PLAYER SPRITE
	player.updateSprite();
	if (player.oxygen <= 0 && isOnAsteriod){
		isOnAsteriod = false;
	}
	if (player.getBody()->GetLinearVelocity().x == 0 && player.getBody()->GetLinearVelocity().y == 0 && !isOnAsteriod){
		player.oxygen -= 1;
	}

	vector<PowerUp*>::iterator PowerUpIterator;
	PowerUpIterator = powerUps.begin();
	while (PowerUpIterator != powerUps.end())
	{
		PowerUp *power = (*PowerUpIterator);
		if (power->remove)
		{
			game->getGSM()->getPhysics()->removeSprite(power);
			PowerUpIterator = powerUps.erase(PowerUpIterator);
		}
		else
			PowerUpIterator++;
	}
	vector<PowerUp*>::iterator portalIterator;
	portalIterator = portals.begin();
	while (portalIterator != portals.end())
	{
		PowerUp *portal = (*portalIterator);
		portal->updateSprite();
		portalIterator++;
	}
	// NOW UPDATE THE REST OF THE SPRITES
	vector<Enemy*>::iterator enemyIterator;
	enemyIterator = enemies.begin();
	while (enemyIterator != enemies.end())
	{
		Enemy *enemy = (*enemyIterator);
		int t = enemy->getTargetAsteroid();
		int a = asteroids.size();
		if (a == t)
		{
			enemy->resetTarget();
			t = 0;
		}
		float x = asteroids[t]->getX();
		float y = asteroids[t]->getY();
		enemy->think(x,y);
		enemy->updateSprite();
		enemyIterator++;
	}
	vector<Enemy2*>::iterator enemy2Iterator;
	enemy2Iterator = enemies2.begin();
	while (enemy2Iterator != enemies2.end())
	{
		Enemy2 *enemy = (*enemy2Iterator);
		enemy->think();
		enemy->updateSprite();
		enemy2Iterator++;
	}
	vector<Enemy3*>::iterator enemy3Iterator;
	enemy3Iterator = enemies3.begin();
	while (enemy3Iterator != enemies3.end())
	{
		Enemy3 *enemy = (*enemy3Iterator);
		enemy->think(player.getX(),player.getY());
		enemy->updateSprite();
		enemy3Iterator++;
	}
	vector<BlackHole*>::iterator BlackHoleIterator;
	BlackHoleIterator = bH.begin();
	while (BlackHoleIterator != bH.end())
	{
		BlackHole *b = (*BlackHoleIterator);
		if (b->over)
		{
			float x = b->getX();
			float y = b->getY();
			float x1 = player.getX();
			float y1= player.getY();
			float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
			if (d < .1)
			{
				player.oxygen = 0;
			}
			float vx = (x - x1) / d;
			float vy = (y - y1) / d;
			player.getBody()->SetLinearVelocity(b2Vec2(vx,vy));
		}
		BlackHoleIterator++;
	}
	if (invincible)
	{
		inviTimer++;
		if (inviTimer / 33 > 25)
		{
			player.setCurrentState(L"IDLE");
			invincible = false;
			inviTimer = 0;
		}
		else
		{
			player.setCurrentState(L"INVINCIBLE");
		}
	}
	if (won && !(game->getCurrentLevelFileName().compare("level4.lua")))
	{
//		game->getAudio()->start(L"Media\\Wavs\\spacejam.wav");
		game->getGSM()->goToGameVictory();
	}
	else if (won)
	{
		game->getGSM()->goToVictory();

	}
	if (player.oxygen <= 0)
	{
		player.setCurrentState(L"DEAD");
		if (player.oxygen == -200)
			game->getGSM()->goToGameOver();
	}
	//Update Viewport
	if (lockScreen)
	{
		Viewport *view = game->getGUI()->getViewport();
		int x = (player.getX()/.02) - (view->getViewportWidth() / 2);
		if (x < 0)
			x = 0;
		else if (x>3200-1367)
			x = 3200-1367;
		int y = (player.getY()/.02) - (view->getViewportHeight() / 2);
		if (y < 0)
			y = 0;
		else if (y>1920-768)
			y = 1920-768;
		view->setViewportX(x);
		view->setViewportY(y);
	}

}
void SpriteManager::attachPlayerToAsteriod(b2World *world)
{
	if (isOverAsteriod){
		if (attachedAsteroid == &winAsteroid)
			won = true;
		b2RevoluteJointDef jointDef;
		jointDef.bodyA = player.getBody();
		jointDef.bodyB = attachedAsteroid->getBody();
		jointDef.collideConnected = false;
		jointDef.localAnchorA.Set(0, 0);
		jointDef.localAnchorB.Set(attachedAsteroid->getBody()->GetLocalPoint(player.getBody()->GetPosition()).x,
			attachedAsteroid->getBody()->GetLocalPoint(player.getBody()->GetPosition()).y);
		playerAsteroidJoint = (b2RevoluteJoint*) world->CreateJoint(&jointDef);
		isOnAsteriod = true;
	}
}
void SpriteManager::jumpOffAsteriod(float jump, b2World *world)
{
	/*player.getBody()->SetLinearVelocity(b2Vec2(0, 0));
	(player.getBody())->ApplyLinearImpulse(b2Vec2(jump * cos(player.getRotationInRadians()), jump * sin(player.getRotationInRadians())),
		player.getBody()->GetWorldCenter(), true);*/
	if (isOnAsteriod)
	{
		//destroy the joint
		world->DestroyJoint(playerAsteroidJoint);
		//now apply the force
		player.getBody()->ApplyForceToCenter(b2Vec2((jump) * cos(player.getRotationInRadians()), (jump) * sin(player.getRotationInRadians())),
			 true);
		attachedAsteroid->getBody()->ApplyForce(b2Vec2(-jump * cos(player.getRotationInRadians()), -jump * sin(player.getRotationInRadians())),
			player.getBody()->GetPosition(), true);
		isOnAsteriod = false;
	}	
}

void SpriteManager::BeginContact(b2Contact* contact){
	if (getPlayerAndAsteroid(contact)){
		isOverAsteriod = true;
		if (contact->GetFixtureA()->IsSensor()){
			attachedAsteroid = (AnimatedSprite*)(contact->GetFixtureA()->GetBody()->GetUserData());
		}
		else {
			attachedAsteroid = (AnimatedSprite*)(contact->GetFixtureB()->GetBody()->GetUserData());
		}
	}
	if (getPlayerAndEnemy(contact) || getPlayerAndEnemy2(contact) || getPlayerAndEnemy3(contact)) {
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0)
		{
			if (!invincible)
			{
				player.getBody()->ApplyForceToCenter(b2Vec2(300.0f * contact->GetFixtureB()->GetBody()->GetLinearVelocity().x,
					10.0f * contact->GetFixtureB()->GetBody()->GetLinearVelocity().y), true);
				player.oxygen -= 10;
			}
			else
			{
				contact->GetFixtureB()->GetBody()->ApplyForceToCenter(b2Vec2(300.0f * contact->GetFixtureA()->GetBody()->GetLinearVelocity().x,
					10.0f * contact->GetFixtureA()->GetBody()->GetLinearVelocity().y), true);
			}
		}
		else 
		{
			if (!invincible)
			{
				player.getBody()->ApplyForceToCenter(b2Vec2(300.0f * contact->GetFixtureA()->GetBody()->GetLinearVelocity().x,
					10.0f * contact->GetFixtureA()->GetBody()->GetLinearVelocity().y), true);
				player.oxygen -= 10;
			}
			else
			{
				contact->GetFixtureA()->GetBody()->ApplyForceToCenter(b2Vec2(300.0f * contact->GetFixtureB()->GetBody()->GetLinearVelocity().x,
					10.0f * contact->GetFixtureB()->GetBody()->GetLinearVelocity().y), true);
			}
		}
	}
	if (getPlayerAndEnemy(contact)){
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0){
			((Enemy*)contact->GetFixtureB()->GetBody()->GetUserData())->nextAsteroid();
		}
		else{
			((Enemy*)contact->GetFixtureA()->GetBody()->GetUserData())->nextAsteroid();
		}
	}
	if (getPlayerAndBlackHole(contact))
	{
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0)
		{
			((BlackHole*)contact->GetFixtureB()->GetBody()->GetUserData())->over = true;
		}
		else
		{
			((BlackHole*)contact->GetFixtureA()->GetBody()->GetUserData())->over = true;
		}
	}
	if (getPlayerAndPowerUp(contact))
	{
		int i;
		int x;
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0)
		{
			i =((PowerUp*)contact->GetFixtureB()->GetBody()->GetUserData())->type;
			x = ((PowerUp*)contact->GetFixtureB()->GetBody()->GetUserData())->portalnum;
		}
		else
		{
			i = ((PowerUp*)contact->GetFixtureA()->GetBody()->GetUserData())->type;
			x = ((PowerUp*)contact->GetFixtureB()->GetBody()->GetUserData())->portalnum;
		}
		if (i == 1)
		{
			player.oxygen += 30;
		}
		else if (i==2)
		{
			invincible = true;
			inviTimer = 0;
		}
		else
		{
			overPortal = true;
			portalOver = x;
		}
	}
}

void SpriteManager::EndContact(b2Contact* contact){
	if (getPlayerAndAsteroid(contact))
	{
		isOverAsteriod = false;
	}
	if (getPlayerAndBlackHole(contact))
	{
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0)
		{
			((BlackHole*)contact->GetFixtureB()->GetBody()->GetUserData())->over = false;
		}
		else
		{
			((BlackHole*)contact->GetFixtureA()->GetBody()->GetUserData())->over = false;
		}
	}
	if (getPlayerAndPowerUp(contact))
	{
		PowerUp *p;
		if (((AnimatedSprite*)contact->GetFixtureA()->GetBody()->GetUserData())->getSpriteType()->getSpriteTypeID() == 0)
		{
			p = ((PowerUp*)contact->GetFixtureB()->GetBody()->GetUserData());
			
		}
		else
		{
			p = ((PowerUp*)contact->GetFixtureA()->GetBody()->GetUserData());
		}
		if (p->type != 3)
			p->remove = true;
		else
			overPortal = false;
	}
}

bool SpriteManager::getPlayerAndAsteroid(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 1)
			|| (A->getSpriteType()->getSpriteTypeID() == 1 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}
bool SpriteManager::getPlayerAndBlackHole(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 6)
			|| (A->getSpriteType()->getSpriteTypeID() == 6 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}
bool SpriteManager::getPlayerAndPowerUp(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 7)
			|| (A->getSpriteType()->getSpriteTypeID() == 7 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}

bool SpriteManager::getPlayerAndEnemy(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 2)
			|| (A->getSpriteType()->getSpriteTypeID() == 2 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}

bool SpriteManager::getPlayerAndEnemy2(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 3)
			|| (A->getSpriteType()->getSpriteTypeID() == 3 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}

bool SpriteManager::getPlayerAndEnemy3(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	AnimatedSprite* A = (AnimatedSprite*)fixtureA->GetBody()->GetUserData();
	AnimatedSprite* B = (AnimatedSprite*)fixtureB->GetBody()->GetUserData();
	if (A && B){
		if ((A->getSpriteType()->getSpriteTypeID() == 0 && B->getSpriteType()->getSpriteTypeID() == 4)
			|| (A->getSpriteType()->getSpriteTypeID() == 4 && B->getSpriteType()->getSpriteTypeID() == 0))
			return true;
	}
	return false;
}