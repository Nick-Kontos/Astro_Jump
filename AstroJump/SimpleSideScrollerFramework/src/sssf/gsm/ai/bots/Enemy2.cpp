#include "sssf\gsm\ai\bots\Enemy2.h"

void Enemy2::think()
{
	float x = Xlist[targetAsteroid];
	float y = Ylist[targetAsteroid];
	float x1 = getX();
	float y1 = getY();
	float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
	if (d <= .2)
	{
		nextAsteroid();
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
		body->SetLinearVelocity(b2Vec2(5 * vx*speed, 5 * vy*speed));
	}
}
void Enemy2::nextAsteroid()
{
	targetAsteroid++;
	if (targetAsteroid >= Xlist.size())
		targetAsteroid = 0;
}