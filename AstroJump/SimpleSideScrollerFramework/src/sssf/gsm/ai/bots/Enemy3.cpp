#include "sssf\gsm\ai\bots\Enemy3.h"

void Enemy3::think(float x, float y)
{
	float x1 = getX();
	float y1 = getY();
	float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
	if (d <= distance)
	{
		float vx = (x - x1) / d;
		if (vx < 0)
		{
			currentState = L"RUNNING_BACK";
		}
		else
			currentState = L"RUNNING";
		float vy = (y - y1) / d;
		body->SetLinearVelocity(b2Vec2(5 * vx, 5 * vy));
	}
	else
	{
		float vx = 0;
		currentState = L"IDLE";
		float vy = 0;
		body->SetLinearVelocity(b2Vec2(5 * vx*speed, 5 * vy*speed));
	}
}