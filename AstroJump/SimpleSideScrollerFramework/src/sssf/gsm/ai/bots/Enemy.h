#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class Enemy : public AnimatedSprite
{
public:
	float speed;
	int targetAsteroid;
	vector<int> asteroidList;
	int getTargetAsteroid(){ return asteroidList[targetAsteroid]; }
	void resetTarget(){ targetAsteroid = 0; }
	void think(float x, float y);
	void addToList(int num)
	{
		asteroidList.push_back(num);
	}
	void nextAsteroid();
};