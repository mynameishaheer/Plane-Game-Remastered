#include "Ranger.h"

Ranger::Ranger(int x, int y) :Enemy(x, y)
{
	this->health = 3;
	this->isRanger = true;
}

Ranger::~Ranger() {}
