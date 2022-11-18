#pragma once
#include "GameObject.h"

class Plane : public GameObject {
protected:

	//ATTRIBUTES//
	float frictionCoff;
	float tx;
	float ty;
	//-ATTRIBUTES//

public:

	//FUNCTIONS//
	Plane(int x, int y);
	virtual ~Plane();

	void Translate(float xVal, float yVal);
	
	virtual void Move() = 0; //abstract
	//-FUNCTIONS//

};