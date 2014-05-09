/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.h

	This class manages all of the sprites in a given game level. Note
	that the player sprite is also managed by this class.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\bots\Enemy.h"
#include "sssf\gsm\ai\BotRecycler.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\TopDownSprite.h"


class SpriteManager : public b2ContactListener
{
private:
	// NOTE THAT MULTIPLE SPRITES MAY SHARE ARTWORK, SO SPRITE TYPES
	// SPECIFIES A TYPE OF SPRITE, OF WHICH THERE MAY BE MANY INSTANCES
	vector<AnimatedSpriteType*> spriteTypes;

	// THESE ARE THE BOTS IN THE GAME, LIKE ENEMIES, ROCKETS, OR ANYTHING
	// THAT MOVES AROUND AND IS NOT THE PLAYER
	list<Bot*> bots;
	
	//These are the asteroids
	vector<AnimatedSprite*> asteroids;

	//These are the bots
	list<Enemy*> enemies;

	// AND THIS IS THE PLAYER. AS-IS, WE ONLY ALLOW FOR ONE PLAYER AT A TIME
	//****change to animatedsprite
	TopDownSprite player;

	//These sprites will be the health bar and lives displays
	AnimatedSprite healthbar;
	AnimatedSprite lives;
	AnimatedSprite winAsteroid;
	
	b2RevoluteJoint* playerAsteroidJoint;
	
	// THE BotRecycler MAKES SURE WE DON'T HAVE TO CONSTRUCT BOTS WHENEVER
	// WE NEED TO SPAWN THEM, INSTEAD IT WILL RECYCLE THEM FOR US
	BotRecycler recyclableBots;

	bool isOnAsteriod;
	bool isOverAsteriod;
	bool won=false;
public:

	AnimatedSprite* attachedAsteroid;

	// NOTHING TO INIT OR DESTROY
	SpriteManager()		{ isOnAsteriod = true; bool isOverAsteriod = false; }
	~SpriteManager()	{}

	// INLINED ACCESSOR METHODS
	int						getNumberOfSprites()	{ return bots.size();		}
	TopDownSprite*			getPlayer()				{ return &player;			}
	AnimatedSprite*			getWinAsteroid()		{ return &winAsteroid; }
	//AnimatedSprite*			getBackground()			{ return &background;       }
	AnimatedSprite*         getHealthBar()          { return &healthbar;        }
	AnimatedSprite*         getLives()              { return &lives;            }
	list<Bot*>::iterator	getBotsIterator()		{ return bots.begin();		}
	list<Bot*>::iterator	getEndOfBotsIterator()	{ return bots.end();		}
	bool					getIsOnAsteriod()		{ return isOnAsteriod;     }
	bool					getIsOverAsteriod()		{ return isOverAsteriod;	}
	void					setIsOnAsteriod(bool b)		{ isOnAsteriod = b;		}
	void					setIsOverAsteriod(bool b)		{ isOverAsteriod = b; }
	AnimatedSprite*			getLastAsteroid()       { return asteroids.back();  }

	// METHODS DEFINED IN SpriteManager.cpp
	void                enterYellowState(Game *game);
	void				addBot(Bot *botToAdd);
	void				addEnemy(Enemy *enemyToAdd);
	void				addAsteriod(AnimatedSprite *asteriodToAdd);
	void				addSpriteItemsToRenderList(Game *game);
	unsigned int		addSpriteType(AnimatedSpriteType *spriteTypeToAdd);
	//void				addBackgroundToRender(AnimatedSprite *backgroundsprite, RenderList *renderList, Viewport *viewport);
	void				addSpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void                addGUISpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				clearSprites();
	AnimatedSpriteType* getSpriteType(unsigned int typeIndex);
	Bot*				removeBot(Bot *botToRemove);
	void				unloadSprites(GameStateManager *gsm);
	void				update(Game *game);
	void				attachPlayerToAsteriod(b2World *world);
	void				jumpOffAsteriod(float jumpval, b2World *world);
	void				BeginContact(b2Contact* contact);
	void				EndContact(b2Contact* contact);
	bool				getPlayerAndAsteriod(b2Contact* contact);
};