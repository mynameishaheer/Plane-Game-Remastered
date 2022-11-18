#include "Bullet.h"

Bullet::Bullet(int x, int y) : GameObject(x, y) {
	angle = 0;
	isRanger = false;
	degrees = 0;
	isBulletFromEnemy = false;
}

Bullet::~Bullet() {

}
