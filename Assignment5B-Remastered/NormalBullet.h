#pragma once
#include<iostream>
#include <stdlib.h> 
#include "Bullet.h"

using namespace std;

class NormalBullet :public Bullet
{
private:
	//ATTRIBUTES//
	int initialPlayerX;
	int initialPlayerY;
	int initialBullX;
	int initialBullY;
	bool hasAimed;
	//-ATTRIBUTES//

public:
	//FUNCTIONS//
	NormalBullet(int x, int y);
	~NormalBullet();
	
	void Move(); //abstract implemented
	void Move(int playerX, int playerY); //overloaded function //abstract implemented
	//-FUNCTIONS//
};

/*
	//void seekingMove(int playerX, int playerY);
	//void setTarget(GameObject* Target);
*/