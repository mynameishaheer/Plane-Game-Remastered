#include "Plane.h"

Plane::Plane(int x, int y) :GameObject(x, y)
{
	frictionCoff = 0.995;

	tx = 0.0;
	ty = 0.0;
}

Plane::~Plane(){}

void Plane::Translate(float xVal, float yVal)
{
	this->tx = xVal;
	this->ty = yVal;
}