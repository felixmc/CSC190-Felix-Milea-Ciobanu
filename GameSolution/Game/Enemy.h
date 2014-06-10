#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
#include "Projectile.h"

using namespace Engine;

struct Enemy : public GameObject {
	float radius;
	bool isDead;
	int points;

	Enemy(const Vector2 sp, const Shape& sh) : GameObject(sp, sh) {
		isDead = false;
	}

	void virtual update(float) = 0;
	void virtual explode(Projectile&) = 0;
};

#endif