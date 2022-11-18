#include "Enemy.h"

Enemy::Enemy(int x, int y) :Plane(x, y)
{
	canDodge = false;
	isRanger = false;
	health = 0;
}

Enemy::~Enemy() {}

//abstract implemented
void Enemy::Move() 
{
	if (health < 1) {
		alive = false;
	}


	if (isRanger) {
		unitBounds->x = this->x + (int)tx;
	}
	else {
		unitBounds->x = this->unitBounds->x + (int)tx;
	}


	if (unitBounds->x < 0)
	{
		unitBounds->x = 0;
	}
	else if (unitBounds->x > 1216)
	{
		unitBounds->x = 1216;
	}


	if (unitBounds->y < 721)
	{
		unitBounds->y = unitBounds->y + 1;
	}
	else {
		alive = false;
	}


	if (!isRanger) {
		tx *= frictionCoff;
		ty *= frictionCoff;
	}
}