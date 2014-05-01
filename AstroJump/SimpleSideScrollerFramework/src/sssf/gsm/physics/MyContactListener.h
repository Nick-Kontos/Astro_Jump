#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "Box2D\box2D.h"

class MyContactListener : public b2ContactListener
{
public:
	Game *game;

	MyContactListener(Game *g);
	MyContactListener(){}
	~MyContactListener(){}
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	bool getPlayerAndAsteriod(b2Contact *contact);
};