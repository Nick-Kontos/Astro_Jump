#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class Enemy2 : public AnimatedSprite
{
public:
	float speed;
	int targetAsteroid;
	vector<float> Xlist;
	vector<float> Ylist;
	void think();
	void addToList(float x, float y)
	{
		Xlist.push_back(x);
		Ylist.push_back(y);
	}
	void nextAsteroid();
};