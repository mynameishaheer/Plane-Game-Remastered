#pragma once
#include "Plane.h"

class Enemy : public Plane {
protected:
	
	//ATTRIBUTES//
	bool canDodge;
	//-ATTRIBUTES//

public:

	//ATTRIBUTES//
	bool isRanger;
	int health;
	//-ATTRIBUTES//

	//FUNCTIONS//
	Enemy(int x, int y);
	virtual ~Enemy();

	void Move(); //abstract implemented
	//-FUNCTIONS//
};