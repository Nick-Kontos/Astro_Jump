#include "sssf\gsm\ai\BlackHole.h"

float BlackHole::getDistance(float x, float y)
{
	float x1 = getX();
	float y1 = getY();
	float d = (sqrt(((x - x1)*(x - x1)) + ((y - y1)*(y - y1))));
	return d;
}