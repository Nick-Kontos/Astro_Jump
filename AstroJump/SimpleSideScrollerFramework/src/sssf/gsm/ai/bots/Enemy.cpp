#include "sssf\gsm\ai\bots\Enemy.h"

void Enemy::think(float x, float y)
{
	float x1 = getX();
	float y1 = getY();
	float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
	if (d <= .2)
	{
		targetAsteroid++;
	}
	else
	{
		float vx = (x - x1) / d;
		if (vx < 0)
		{
			currentState = L"RUNNING_BACK";
		}
		else
			currentState = L"RUNNING";
		float vy = (y - y1) / d;
		body->SetLinearVelocity(b2Vec2(5*vx, 5*vy));
	}
}