#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "Box2D\box2D.h"

class MyContactListener : public b2ContactListener
{
public:
	SpriteManager *spritemanager;

	MyContactListener(SpriteManager *sm);
	MyContactListener(){}
	~MyContactListener(){}
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	bool getPlayerAndAsteriod(b2Contact* contact);
};