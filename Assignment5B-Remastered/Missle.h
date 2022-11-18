#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Bullet.h"

using namespace std;

class Missle :public Bullet
{
private:

	//ATTRIBUTES//
	GameObject* yourTarget;
	//-ATTRIBUTES//
	
	//FUNCTIONS//
	void setTarget(GameObject* Target);
	GameObject* getTarget();

public:

	Missle(int x, int y);
	~Missle();

	void Move(); //abstract implemented
	void Move(int enemyX, int enemyY); //overloaded function //abstract implemented
	//-FUNCTIONS//

};

