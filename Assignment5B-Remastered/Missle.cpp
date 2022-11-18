#include "Missle.h"

Missle::Missle(int x, int y) :Bullet(x, y)
{
	yourTarget = nullptr;
}

Missle::~Missle() {}

void Missle::Move()
{
	if (unitBounds->y > 5)
	{
		unitBounds->y = unitBounds->y - 2;
	}
	else
	{
		alive = false;
	}
}

//overloaded function 
//not working
void Missle::Move(int enemyX, int enemyY)
{
	if (this->yourTarget != nullptr)
	{
		this->angle = atan2f(abs(yourTarget->unitBounds->y - this->unitBounds->y), abs(yourTarget->unitBounds->x - this->unitBounds->x));

		// target is at right of player
		if (yourTarget->unitBounds->x > this->x)
		{
			this->unitBounds->x = this->unitBounds->x + ceil(7 * cos(this->angle));

			//enemy is below you
			if (yourTarget->unitBounds->y > this->unitBounds->y)
			{
				this->y = this->y + ceil(7 * sin(this->angle));
				this->degrees = 90.0 + (this->angle * (1800 / 3.14159));
			}
			else
			{
				this->y = this->y - ceil(7 * sin(this->angle));
				this->degrees = 90.0 - (this->angle * (1800 / 3.14159));
			}
		}
		else
		{
			this->unitBounds->x = this->unitBounds->x - ceil(7 * cos(this->angle));
			//enemy is below you
			if (yourTarget->unitBounds->y > this->unitBounds->y)
			{
				this->y = this->y + ceil(7 * sin(this->angle));
				this->degrees = -(90.0 + (this->angle * (1800 / 3.14159)));
			}
			else
			{
				this->y = this->y - ceil(7 * sin(this->angle));
				this->degrees = -(90.0 - (this->angle * (1800 / 3.14159)));
			}
		}
	}

}

void Missle::setTarget(GameObject* Target)
{
	this->yourTarget = Target;
}

GameObject* Missle::getTarget()
{
	return yourTarget;
}