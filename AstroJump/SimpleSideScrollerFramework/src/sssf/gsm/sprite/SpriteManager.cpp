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
			(int)floor(((sprite->getX() / .02f) - viewport->getViewportX()) + 0.5f) - spriteType->getTextureWidth()/2,
			(int)floor(((sprite->getY() / .02f) - viewport->getViewportY()) + 0.5f) - spriteType->getTextureWidth() / 2,
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

		//add asteroids
		vector<AnimatedSprite*>::iterator asteroidsIterator;
		asteroidsIterator = asteroids.begin();
		while (asteroidsIterator != asteroids.end())
		{
			AnimatedSprite *asteroid = (*asteroidsIterator);
			addSpriteToRenderList(asteroid, renderList, viewport);
			asteroidsIterator++;
		}
		// NOW ADD THE REST OF THE SPRITES
		list<Enemy*>::iterator enemyIterator;
		enemyIterator = enemies.begin();
		while (enemyIterator != enemies.end())
		{			
			Enemy *enemy = (*enemyIterator);
			addSpriteToRenderList(enemy, renderList, viewport);
			enemyIterator++;
		}
		//add GUI sprites
		//addGUISpriteToRenderList(&healthbar, renderList, viewport);
		//addGUISpriteToRenderList(&lives, renderList, viewport);

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&winAsteroid, renderList, viewport);
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

void SpriteManager::addAsteriod(AnimatedSprite *asteriodToAdd)
{
	asteroids.push_back(asteriodToAdd);
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
	physic->removeSprite(&player);
	isOnAsteriod = true;
	physic->removeSprite(&winAsteroid);

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

	// NOW UPDATE THE REST OF THE SPRITES
	list<Enemy*>::iterator enemyIterator;
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
	if (won)
	{
		game->getGSM()->goToVictory();
	}
	if (!isOnAsteriod)
	{
		if (player.getBody()->GetLinearVelocity().x == 0 && player.getBody()->GetLinearVelocity().y == 0)
		{
			game->getGSM()->goToGameOver();
		}
	}

}
void SpriteManager::attachPlayerToAsteriod()
{
	//may leak memory
	vector<AnimatedSprite*>::iterator asteriodIterator;
	asteriodIterator = asteroids.begin();
	float radius;
	int num = 0;
	while (asteriodIterator != asteroids.end())
	{
		AnimatedSprite *asteriod = *asteriodIterator;
		radius = asteriod->getSpriteType()->getTextureWidth() / 2 * .02f;
		if (radius >= sqrt((player.getX() - asteriod->getX()) * (player.getX() - asteriod->getX())
			+ (player.getY() - asteriod->getY()) * (player.getY() - asteriod->getY()))){
			//player is on top of asteriod -- stick to it
			//for now hold place with break so we can put a breakpoint here
			isOnAsteriod = true;
			initial = false;
			attachedAsteroid = num;
			break;
		}
		asteriodIterator++;
		num++;
	}
	if (radius >= sqrt((player.getX() - winAsteroid.getX()) * (player.getX() - winAsteroid.getX()) + (player.getY() - winAsteroid.getY()) * (player.getY() - winAsteroid.getY())))
	{
		won = true;
	}
}
void SpriteManager::jumpOffAsteriod(float jump)
{
	(player.getBody())->ApplyLinearImpulse(b2Vec2(jump * cos(player.getRotationInRadians()), jump * sin(player.getRotationInRadians())),
		player.getBody()->GetWorldCenter(), true);
	if (!initial)
	{
		(asteroids[attachedAsteroid]->getBody()->ApplyLinearImpulse(b2Vec2(-jump * cos(player.getRotationInRadians()), -jump * sin(player.getRotationInRadians())),
			asteroids[attachedAsteroid]->getBody()->GetWorldCenter(), true));
	}
	isOnAsteriod = false;
}