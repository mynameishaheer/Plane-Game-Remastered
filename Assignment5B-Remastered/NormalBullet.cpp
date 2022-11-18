#include "NormalBullet.h"

NormalBullet::NormalBullet(int x, int y) :Bullet(x, y) {
	initialPlayerX = 0;
	initialPlayerY = 0;
	initialBullX = 0;
	initialBullY = 0;
	hasAimed = false;
}

NormalBullet::~NormalBullet() {}



void NormalBullet::Move() {

	if (isBulletFromEnemy == false) {

		//from player
		if (unitBounds->y > 5) {
			unitBounds->y = unitBounds->y - 2;
		}
		else {
			alive = false;
		}
	}
	else
	{
		//from enenmy
		if (unitBounds->y < 719)
		{
			unitBounds->y = unitBounds->y + 2;
		}
		else {
			alive = false;
		}
	}
}

//overloaded function
void NormalBullet::Move(int playerX, int playerY)
{
		if (this->hasAimed == false)
		{
			initialBullX = this->unitBounds->x;
			initialBullY = this->unitBounds->y;
			this->angle = atan2f(abs(playerY - this->unitBounds->y), abs(playerX - this->unitBounds->x));
			this->degrees = 180.0 - (90.0 + (this->angle * (180.0 / 3.14159)));

			if (playerX > this->unitBounds->x)
			{
				//for move in opp direction
				this->degrees = -this->degrees;
			}

			initialPlayerX = playerX;
			this->hasAimed = true;
			
		}
		if (initialBullX > initialPlayerX) 
		{
			this->unitBounds->x = this->unitBounds->x - ceil(2 * cos(this->angle));
		}
		else 
		{
			this->unitBounds->x = this->unitBounds->x + ceil(2 * cos(this->angle));
		}

		this->unitBounds->y = this->unitBounds->y + ceil(3 * sin(angle));

		if (this->unitBounds->x <= 0 || this->unitBounds->x > 1270)
		{
			this->alive = false;
		}
		if (this->unitBounds->y > 720) 
		{
			this->alive = false;
		}

}
