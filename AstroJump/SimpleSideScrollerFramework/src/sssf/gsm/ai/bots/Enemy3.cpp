#include "sssf\gsm\ai\bots\Enemy3.h"

void Enemy3::think(float x, float y)
{
	float x1 = getSpawnX();
	float y1 = getSpawnY();
	float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
	if (d <= distance)
	{
		x1 = getX();
		y1 = getY();
		d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
		float vx = (x-x1) / d;
		float vy = (y - y1) / d;
		body->SetLinearVelocity(b2Vec2(5 * vx, 5 * vy));
	}
	else
	{
		float x2 = x1;
		float y2 = y1;
		x1 = getX();
		y1 = getY();
		d = (sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1))));
		if (d > 1)
		{
			float vx = (x2 - x1) / d;
			float vy = (y2 - y1) / d;
			body->SetLinearVelocity(b2Vec2(5 * vx, 5 * vy));
		}
		else
			body->SetLinearVelocity(b2Vec2(0, 0));
	}
}