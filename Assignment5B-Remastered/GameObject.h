#pragma once
#include <stdlib.h> 
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Contains attributes and fucntions used by every object in the game (Player/Bullet/Enemy)
class GameObject
{
public:

	//ATTRIBUTES//
	int x;
	int y;

	bool alive;

	SDL_Rect* unitBounds;
	SDL_Texture* unitTexture;
	//-ATTRIBUTES//
	
	//FUNCTIONS//
	GameObject(int x, int y);
	virtual ~GameObject();

	virtual void Move() = 0; //abstract
	bool Alive();
	void setImage(SDL_Renderer* gRender, std::string path);
	void setUnitBounds(int widthBound, int heightBound, int xPos, int yPos);
	//-FUNCTIONS//

};

	/*
		bool hasAimed = false;
		float angle = 0;

		int hp;
		bool isHit;
		int getHealth();


		gameObject();

		float tx = 0.0;
		float ty = 0.0;

		for bullets
		virtual void seekingMove(int targetX, int targetY) = 0;
		virtual void setTarget(GameObject* Target) = 0;

		void fireGun(int xBound, int yBound);
		void setSDLRECT(int x, int y);


		void Translate(float xVal, float yVal);
	*/