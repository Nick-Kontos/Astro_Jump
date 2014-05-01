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
		float vx = abs(x - x1) / d;
		float vy = abs(y - y1) / d;
		body->SetLinearVelocity(b2Vec2(vx, vy));
	}
}