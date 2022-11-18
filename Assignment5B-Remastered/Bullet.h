#pragma once
#include "GameObject.h"

class Bullet :public GameObject {

//-ATTRIBUTES//
protected:
	float angle;

public:
	bool isRanger;
	double degrees;
	bool isBulletFromEnemy;
//ATTRIBUTES//
	
//FUNCTIONS//
	Bullet(int x, int y);
	virtual ~Bullet();

	virtual void Move() = 0; //abstract
	virtual void Move(int playerX, int playerY) = 0; //overloaded function //abstract
//-FUNCTIONS//

};
