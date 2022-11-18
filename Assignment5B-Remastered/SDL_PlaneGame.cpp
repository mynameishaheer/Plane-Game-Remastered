#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "Player.h"
#include "doublyList.h"
#include "NormalBullet.h"
#include "Node.h"
#include "Ranger.h"
#include "Nimble.h"
#include <Windows.h>
#include <thread>
#include "Missle.h"
#include "TextController.h"
#include <iostream>
#include <string>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int targetX = 0;
int targetY = 0;

//Bullet* get(list<Bullet*> _list, int _i) {
//	list<Bullet*>::iterator it = _list.begin();
//	for (int i = 0; i < _i; i++) {
//		++it;
//	}
//	return *it;
//}


int main(int argc, char* argv)
{

	SDL_Renderer* gameRenderer;
	doublyList enemyList;
	doublyList bulletList;

	//doublyList bullet_list;
	//doublyList missile_list;

	TextController* txtC = new TextController();

	SDL_Surface* background;
	SDL_Surface* WindowSurface;


	Player* player1 = new Player(200, 520);


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{

		std::cout << "SDL Failed to initialize. Error Code : " << SDL_GetError() << std::endl;

	}

	SDL_Window* window = SDL_CreateWindow("Plane Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	WindowSurface = SDL_GetWindowSurface(window);

	if (window == NULL) {
		std::cout << "Could not initialize SDL Window. Error Code : " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if (!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
		std::cout << "Could not initialize PNG. Error Code : " << SDL_GetError() << std::endl;
	}

	SDL_Event window_event;

	background = IMG_Load("media/gameBG.jpg");


	if (background == NULL) {
		std::cout << "Could not load background image. Error Code : " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	gameRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player1->setImage(gameRenderer, "media/player_sprite.png");
	//Load Player Plane
	//SDL_Texture* Player = NULL;
	//Player = IMG_LoadTexture(R, "media/player_sprite.png");
	SDL_Texture* gameBG = IMG_LoadTexture(gameRenderer, "media/gameBG.jpg");
	SDL_Texture* button = IMG_LoadTexture(gameRenderer, "media/button.png");
	SDL_Texture* text = IMG_LoadTexture(gameRenderer, "media/text.png");
	SDL_Texture* escape = IMG_LoadTexture(gameRenderer, "media/x.png");
	SDL_Texture* title = IMG_LoadTexture(gameRenderer, "media/title.png");

	SDL_Rect* esc = new SDL_Rect();
	esc->x = 10;
	esc->y = 20;
	esc->w = 32;
	esc->h = 16;


	SDL_Rect* titleRec = new SDL_Rect();
	titleRec->x = 396;
	titleRec->y = 104;
	titleRec->w = 512;
	titleRec->h = 248;

	player1->setUnitBounds(64, 64, 200, 520);

	SDL_Rect* Background_Rect = new SDL_Rect();
	Background_Rect->w = SCREEN_WIDTH;
	Background_Rect->h = SCREEN_HEIGHT;
	Background_Rect->x = 0;
	Background_Rect->y = 0;
	int bullXBound = 0;
	int bullYBound = 0;
	int gameFrames = 0;
	int random = 0;
	int randomDodge = 0;
	int xDiff = 0;
	int yDiff = 0;
	bool game_running = false;
	bool flag = true;
	int score = 0;
	int gameRestart = 0;


	while (flag)
	{
		while (!game_running)
		{

			SDL_Rect* rect = new SDL_Rect();
			rect->x = 500;
			rect->y = 550;
			rect->h = 64;
			rect->w = 256;


			SDL_RenderClear(gameRenderer);
			SDL_RenderCopy(gameRenderer, gameBG, NULL, NULL);
			SDL_RenderCopy(gameRenderer, button, NULL, rect);
			SDL_RenderCopy(gameRenderer, text, NULL, rect);
			SDL_RenderCopy(gameRenderer, escape, NULL, esc);
			SDL_RenderCopy(gameRenderer, title, NULL, titleRec);

			SDL_RenderPresent(gameRenderer);
			if (SDL_PollEvent(&window_event))
			{

				if (SDL_QUIT == window_event.type)
				{
					flag = false;
					break;
				}

				if (SDL_KEYDOWN == window_event.type)
				{
					if (SDLK_SPACE == window_event.key.keysym.sym)
					{
						gameRestart = 1;
						game_running = true;
					}

					if (SDLK_ESCAPE == window_event.key.keysym.sym)
					{
						flag = !flag;
						break;
					}
				}
			}
		}

		while (game_running == true)
		{
			gameFrames++;
			if (SDL_PollEvent(&window_event))
			{

				if (SDL_QUIT == window_event.type)
				{
					break;
				}

				if (SDL_KEYDOWN == window_event.type)
				{
					if (SDLK_DOWN == window_event.key.keysym.sym) {
						//player1->unitBounds->y = player1->unitBounds->y + 5;
						player1->Translate(0, 3);
					}
					if (SDLK_UP == window_event.key.keysym.sym) {
						//player1->unitBounds->y = player1->unitBounds->y - 5;
						player1->Translate(0, -3);
					}
					if (SDLK_LEFT == window_event.key.keysym.sym) {
						//player1->unitBounds->x = player1->unitBounds->x - 5;
						player1->Translate(-3, 0);
					}
					if (SDLK_RIGHT == window_event.key.keysym.sym) {
						//player1->unitBounds->x = player1->unitBounds->x + 5;
						player1->Translate(3, 0);
					}
					if (SDLK_SPACE == window_event.key.keysym.sym)
					{
						Bullet* bulletA = new NormalBullet(player1->unitBounds->x + 16, player1->unitBounds->y - 16);
						Bullet* bulletB = new NormalBullet(player1->unitBounds->x + 40, player1->unitBounds->y - 16);
						bulletA->isBulletFromEnemy = false;
						bulletB->isBulletFromEnemy = false;
						bulletA->setImage(gameRenderer, "media/player_bullet.png");
						bulletB->setImage(gameRenderer, "media/player_bullet.png");
						bulletA->setUnitBounds(8, 16, player1->unitBounds->x + 16, player1->unitBounds->y - 16);
						bulletB->setUnitBounds(8, 16, player1->unitBounds->x + 40, player1->unitBounds->y - 16);



						bulletList.insertAtTail(bulletA);
						bulletList.insertAtTail(bulletB);
					}

					if (SDLK_b == window_event.key.keysym.sym)
					{

						if (player1->missleCount <= 10 && player1->missleCount >= 1)
						{
							std::cout << player1->missleCount << std::endl;
							Bullet* missle = new Missle(player1->unitBounds->x + 32, player1->unitBounds->y - 16);
							missle->setImage(gameRenderer, "media/rocket.png");
							missle->setUnitBounds(16, 32, player1->unitBounds->x + 24, player1->unitBounds->y - 16);

							/*GameObject* target = nullptr;
							int xDistance = 1000;

							for (int countEnemy = 0; countEnemy < gameobject_list.returnSize(); countEnemy++)
							{
								GameObject* tempEnem = gameobject_list.returnAt(countEnemy);

								if (abs(tempEnem->unitBounds->x - missle->unitBounds->x < xDistance))
								{
									xDistance = abs(tempEnem->unitBounds->x - missle->unitBounds->x);
									target = tempEnem;
									break;
								}

							}
							if (target == nullptr)
								missle->setTarget(target);
							else {
								missle->setTarget(target);
							}*/

							//targetX = target->unitBounds->x;
							//targetY = target->unitBounds->y;


							bulletList.insertAtTail(missle);
							player1->missleCount = player1->missleCount--;

						}
					}
					if (SDLK_ESCAPE == window_event.key.keysym.sym)
					{
						score = 0;
						player1->setUnitBounds(64, 64, 200, 520);
						player1->missleCount = 10;
						gameRestart = 1;
						game_running = false;
						break;
					}
				}
			}

			if (gameFrames % 250 == 0)
			{
				random = rand() % 1216;
				Enemy* newRanger = new Ranger(random, 0);
				//add bullet mechanism here
				//set bullet from enemy to true

				newRanger->setImage(gameRenderer, "media/rangerEnem.png");
				newRanger->setUnitBounds(64, 64, random, 0);

				newRanger->isRanger = true;
				enemyList.insertAtTail(newRanger);


			}

			if (gameFrames % 400 == 0)
			{

				random = rand() % 1216;
				Enemy* newNimble = new Nimble(random, 0);
				//add bullet mechanism here
				//set bullet from enemy to true

				newNimble->setImage(gameRenderer, "media/nimbleEnem.png");
				newNimble->setUnitBounds(64, 64, random, 0);
				newNimble->isRanger = false;

				enemyList.insertAtTail(newNimble);


			}

			//bullet & plane
			for (int countBullet = 0; countBullet < bulletList.returnSize(); countBullet++)
			{
				Bullet* bullet = (Bullet*)bulletList.returnAt(countBullet);
				//player bullet & enemy plane
				if (bullet->alive != false && bullet->isBulletFromEnemy == false)
				{
					for (int countEnemy = 0; countEnemy < enemyList.returnSize(); countEnemy++)
					{

						Enemy* tempEnem = (Enemy*)enemyList.returnAt(countEnemy);

						//GameObject* tempEnem = gameobject_list.returnAt(countEnemy);
						if (tempEnem->alive != false)
						{
							xDiff = bullet->unitBounds->x - tempEnem->unitBounds->x;
							yDiff = bullet->unitBounds->y - tempEnem->unitBounds->y;

							if (tempEnem->isRanger == false)
							{

								if (yDiff <= 200 && yDiff >= 40)
								{
									if (xDiff >= -7 && xDiff <= 71)
									{
										if (xDiff >= -7 && xDiff <= 32)
										{
											tempEnem->Translate(2, 0);
										}
										else if (xDiff >= 33 && xDiff <= 71)
										{
											tempEnem->Translate(-2, 0);
										}
									}
								}
								if (xDiff >= -6 && xDiff <= 70 && yDiff >= 0 && yDiff <= 64)
								{

									tempEnem->health--;
									if (tempEnem->health < 1)
									{
										tempEnem->setImage(gameRenderer, "media/explosion.png");
									}

									bullet->alive = false;
									//tempEnem->alive = false;
								}
							}
							else if (tempEnem->isRanger == true)
							{
								if (xDiff >= -6 && xDiff <= 70 && yDiff >= 0 && yDiff <= 64)
								{

									tempEnem->health--;
									if (tempEnem->health < 1) {
										printf("enemy destroyed");
										tempEnem->setImage(gameRenderer, "media/explosion.png");
										score++;
									}
									bullet->alive = false;
									//tempEnem->alive = false;
								}
							}

						}
					}
				}
				//enemy bullet and player plane
				else if (bullet->alive != false && bullet->isBulletFromEnemy == true)
				{
					xDiff = bullet->unitBounds->x - player1->unitBounds->x;
					yDiff = bullet->unitBounds->y - player1->unitBounds->y;

					if (xDiff >= -6 && xDiff <= 70 && yDiff >= 0 && yDiff <= 62)
					{
						game_running = false;

						std::cout << "PlayerHit" << std::endl;
					}

				}

			}
			//player and enemy plane
			for (int countEnemy = 0; countEnemy < enemyList.returnSize(); countEnemy++)
			{
				Enemy* enemy = (Enemy*)enemyList.returnAt(countEnemy);
				if (enemy->alive != false)
				{
					xDiff = enemy->unitBounds->x - player1->unitBounds->x;
					yDiff = enemy->unitBounds->y - player1->unitBounds->y;

					if (xDiff >= -62 && xDiff <= 62 && yDiff >= 0 && yDiff <= 62)
					{
						game_running = false;

						std::cout << "PlayerHit" << std::endl;
					}
				}
			}

			//player missle and enemy plane
			for (int countMissle = 0; countMissle < bulletList.returnSize(); countMissle++)
			{
				Missle* missile = (Missle*)bulletList.returnAt(countMissle);
				//player bullet & enemy plane
				if (missile != nullptr)
				{
					if (missile->alive != false)
					{
						for (int countEnemy = 0; countEnemy < enemyList.returnSize(); countEnemy++)
						{
							Enemy* enemy = (Enemy*)enemyList.returnAt(countEnemy);
							if (enemy->alive != false)
							{
								xDiff = missile->unitBounds->x - enemy->unitBounds->x;
								yDiff = missile->unitBounds->y - enemy->unitBounds->y;


								if (xDiff >= -6 && xDiff <= 70 && yDiff >= 0 && yDiff <= 64)
								{

									enemy->health-=3;
									if (enemy->health < 1)
									{
										printf("enemy destroyed");
										enemy->setImage(gameRenderer, "media/explosion.png");

									}
									missile->alive = false;
								}
							}
						}
					}
				}
			}


			//printf("%d", bullet_list.size());

			Node* bulletNode = bulletList.returnHead();
			//int ind = 0;
			//Bullet* tempBullet = bullet_list.at(ind);
			Node* enemyNode = enemyList.returnHead();
			Node* missileNode = bulletList.returnHead();

			//int ind2 = 0;
			//Bullet* tempMiss = bullet_list.at(ind2);

			player1->Move();

			SDL_RenderCopy(gameRenderer, gameBG, NULL, Background_Rect);
			SDL_RenderCopy(gameRenderer, player1->unitTexture, NULL, player1->unitBounds);
			//SDL_RenderCopy(gameRenderer, escape, NULL, esc);
			txtC->showText(gameRenderer, 10, 0, "Menu (ESC)", 255, 0, 0);
			txtC->showText(gameRenderer, 1120, 0, "Score:    ", 255, 255, 255);
			txtC->showText(gameRenderer, 1250, 0, "" + std::to_string(score), 23, 183, 23);
			txtC->showText(gameRenderer, 1120, 20, "Missiles: ", 255, 255, 255);
			txtC->showText(gameRenderer, 1250, 20, "" + std::to_string(player1->missleCount), 23, 183, 23);


			//Enemy Movement
			while (enemyNode != nullptr)
			{
				Enemy* enemy = (Enemy*)enemyNode->gmObject;

				if (enemyNode != nullptr)
				{
					enemy->Move();
				}

				if (true)
				{
					if (gameFrames % 500 == 0)
					{
						random = rand() % 10;
						if (random < 9)
						{
							Bullet* enemyBulletA = new NormalBullet(enemy->x + 20, enemy->y + 75);
							Bullet* enemyBulletB = new NormalBullet(enemy->x + 40, enemy->y + 75);
							enemyBulletA->isBulletFromEnemy = true;
							enemyBulletB->isBulletFromEnemy = true;

							if (enemy->isRanger == true)
							{
								enemyBulletA->setImage(gameRenderer, "media/ranger_bullet.png");
								enemyBulletB->setImage(gameRenderer, "media/ranger_bullet.png");
								enemyBulletA->isRanger = true;
								enemyBulletB->isRanger = true;
							}
							else
							{
								enemyBulletA->setImage(gameRenderer, "media/nimble_bullet.png");
								enemyBulletB->setImage(gameRenderer, "media/nimble_bullet.png");
								enemyBulletA->isRanger = false;
								enemyBulletB->isRanger = false;
							}

							enemyBulletA->setUnitBounds(8, 16, enemy->unitBounds->x + 20, enemy->unitBounds->y + 75);
							enemyBulletB->setUnitBounds(8, 16, enemy->unitBounds->x + 40, enemy->unitBounds->y + 75);

							//bullet_list.emplace_back(enemyBulletA);
							//bullet_list.emplace_back(enemyBulletB);
							bulletList.insertAtTail(enemyBulletA);
							bulletList.insertAtTail(enemyBulletB);
						}
					}
					else if (gameFrames % 750 == 0)

					{
						random = rand() % 10;
						if (random < 9)
						{
							Bullet* enemyBulletA = new NormalBullet(enemy->x + 20, enemy->y + 75);
							Bullet* enemyBulletB = new NormalBullet(enemy->x + 40, enemy->y + 75);
							enemyBulletA->isBulletFromEnemy = true;
							enemyBulletB->isBulletFromEnemy = true;

							if (enemy->isRanger == true)
							{
								enemyBulletA->setImage(gameRenderer, "media/ranger_bullet.png");
								enemyBulletB->setImage(gameRenderer, "media/ranger_bullet.png");
								enemyBulletA->isRanger = true;
								enemyBulletB->isRanger = true;
							}
							else
							{
								enemyBulletA->setImage(gameRenderer, "media/nimble_bullet.png");
								enemyBulletB->setImage(gameRenderer, "media/nimble_bullet.png");
								enemyBulletA->isRanger = false;
								enemyBulletB->isRanger = false;
							}

							enemyBulletA->setUnitBounds(8, 16, enemy->unitBounds->x + 20, enemy->unitBounds->y + 75);
							enemyBulletB->setUnitBounds(8, 16, enemy->unitBounds->x + 40, enemy->unitBounds->y + 75);

							//bullet_list.emplace_back(enemyBulletA);
							//bullet_list.emplace_back(enemyBulletB);
							bulletList.insertAtTail(enemyBulletA);
							bulletList.insertAtTail(enemyBulletB);
						}
					}

					SDL_RenderCopy(gameRenderer, enemy->unitTexture, NULL, enemy->unitBounds);

				}

				if (enemyNode != nullptr)
				{
					enemyNode = enemyNode->next;
				}
			}

			//Bullet Movement
			while (bulletNode != nullptr)
			{
				Bullet* bullet = (Bullet*)bulletNode->gmObject;

				if (bulletNode != nullptr)
				{
					if (bullet->isRanger == true)
					{
						//Bullet* bullet = (Bullet*)bullet;
						//tempBullet->gmObject->seekingMove(player1->unitBounds->x, player1->unitBounds->y);
						bullet->Move(player1->unitBounds->x, player1->unitBounds->y);
					}
					else
					{
						bullet->Move();
					}
				}

				if (bullet->Alive() == true)
				{
					if (bullet->isRanger == true) {
						//SDL_RenderCopy(gameRenderer, tempBullet->gmObject->unitTexture, NULL, tempBullet->gmObject->unitBounds);
						SDL_RenderCopyEx(gameRenderer, bullet->unitTexture, NULL, bullet->unitBounds, bullet->degrees, nullptr, SDL_FLIP_NONE);
					}
					else
					{
						SDL_RenderCopy(gameRenderer, bullet->unitTexture, NULL, bullet->unitBounds);
					}
				}

				if (bulletNode != nullptr)
				{
					bulletNode = bulletNode->next;
				}
			}

			//Missile Movement
			while (missileNode != nullptr)
			{
				Bullet* missile = (Bullet*)missileNode->gmObject;

				if (missileNode != nullptr) {
					missile->Move();
					//tempMiss->gmObject->seekingMove(targetX, targetY);
				}

				if (missile->Alive() == true)
				{
					SDL_RenderCopy(gameRenderer, missile->unitTexture, NULL, missile->unitBounds);

				}

				if (missileNode != nullptr)
				{
					missileNode = missileNode->next;
				}
			}

			SDL_RenderPresent(gameRenderer);
			SDL_RenderClear(gameRenderer);
			//SDL_UpdateWindowSurface(window);
			
			//TEXTURE CLEAN UP
			
			//bullet clean up
			for (int count = 0; count < bulletList.returnSize(); count++)
			{
				if (bulletList.returnAt(count)->Alive() == false)
				{
					SDL_DestroyTexture(bulletList.returnAt(count)->unitTexture);
					bulletList.deleteNode(count);
				}
			}

			//enemy clean up
			if (gameFrames % 83 == 0)
			{
				for (int count = 0; count < enemyList.returnSize(); count++)
				{
					if (enemyList.returnAt(count)->Alive() == false)
					{
						SDL_DestroyTexture(enemyList.returnAt(count)->unitTexture);
						enemyList.deleteNode(count);
					}
				}
			}

			//bullet clean up - might be possible to remove cuz repeated
			for (int count = 0; count < bulletList.returnSize(); count++)
			{
				if (bulletList.returnAt(count)->Alive() == false)
				{
					SDL_DestroyTexture(bulletList.returnAt(count)->unitTexture);
					bulletList.deleteNode(count);
				}
			}


			//PLAYER MISSILE COUNT INCREASE OVER TIME
			if (gameFrames % 666 == 0)
			{
				if (player1->missleCount < 10)
				{
					player1->missleCount = player1->missleCount + 1;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(5));

		}
		gameRestart = 0;
		game_running = false;
		/*gameobject_list.clear();
		bullet_list.clear();
		missile_list.clear();*/
	}

	SDL_FreeSurface(background);
	SDL_FreeSurface(WindowSurface);

	background = NULL;
	WindowSurface = NULL;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gameRenderer);

	SDL_Quit();

	this_thread::sleep_for(10000ms);
	return EXIT_SUCCESS;
}