#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <string>
using namespace std;

GameObject::GameObject(int x, int y)
{
	this->x = x;
	this->y = y;

	alive = true;

	unitBounds = new SDL_Rect();
	unitTexture = NULL;
}

GameObject::~GameObject() {}

bool GameObject::Alive()
{
	return alive;
}

void GameObject::setImage(SDL_Renderer* gRender, string path)
{
	char* c = const_cast<char*>(path.c_str());
	unitTexture = IMG_LoadTexture(gRender, c);

}

void GameObject::setUnitBounds(int widthBound, int heightBound, int xPos, int yPos)
{
	unitBounds->w = widthBound;
	unitBounds->h = heightBound;
	unitBounds->x = xPos;
	unitBounds->y = yPos; 
}


/*
	void GameObject::Translate(float xVal, float yVal)
	{
		this->tx = xVal;
		this->ty = yVal;
	}
*/

