#include "Nimble.h"


Nimble::Nimble(int x, int y) :Enemy(x, y)
{
	canDodge = true;
	this->health = 1;
	this->isRanger = false;
}

Nimble::~Nimble() {}


