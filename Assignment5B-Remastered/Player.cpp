#pragma once
#include "Player.h" 


Player::Player(int x, int y):Plane(x, y) {
	this->missleCount = 10;
}

Player::~Player(){}

//abstract implemented
void Player::Move()
{
	//x = x + (int)tx;
	//y = y + (int)ty;

	unitBounds->x = unitBounds->x + (int)tx;
	unitBounds->y = unitBounds->y + (int)ty;

	if (unitBounds->x < 0)
	{
		unitBounds->x = 0;
	}

	else if (unitBounds->x > 1216)
	{
		unitBounds->x = 1216;
	}

	if (unitBounds->y < 0)
	{
		unitBounds->y = 0;
	}
	else if (unitBounds->y > 656) {
		unitBounds->y = 656;
	}
	tx *= frictionCoff;
	ty *= frictionCoff;

}