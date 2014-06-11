#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
#include "Projectile.h"

using namespace Engine;

struct Enemy : public GameObject {
	float radius;
	bool isDead, isDying;
	int points;

	Enemy(const Vector2 sp, const Shape& sh) : GameObject(sp, sh) {
		isDead = false;
		isDying = false;
	}

	void virtual update(float) = 0;
	bool virtual explode(Projectile&) = 0;
};

#endif