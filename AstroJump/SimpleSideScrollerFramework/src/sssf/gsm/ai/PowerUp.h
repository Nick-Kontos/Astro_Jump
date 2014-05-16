#pragma once

#include "sssf\gsm\sprite\AnimatedSprite.h"

class PowerUp : public AnimatedSprite
{
public:
	int type;
	bool remove = false;
	int portalnum;
};