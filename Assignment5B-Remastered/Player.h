#pragma once 
#include "Plane.h"

class Player :public Plane
{
public:
	//ATTRIBUTES//
	int missleCount = 0;
	//-ATTRIBUTES//

	//FUNCTIONS//
	Player(int x, int y);
	~Player();

	void Move(); //abstract implemented
	//-FUNCTIONS//
};