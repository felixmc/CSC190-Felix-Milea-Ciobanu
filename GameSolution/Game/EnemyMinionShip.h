#ifndef _ENEMY_MINION_SHIP_H_
#define _ENEMY_MINION_SHIP_H_

#include "Enemy.h"
#include "Interpolation.h"

struct EnemyMinionShip : public Enemy {
	static const float PING_DELAY;
	static const float SPEED;
	float mu, muInc;
	Timer timer;
	Vector2 start, targetPosition;

	Interpolation * hueInter;
	GameObject* target;

	EnemyMinionShip(GameObject* target);
	~EnemyMinionShip();
	void update(float);
	void draw(EnhancedGraphics&);
	bool explode(Projectile&);

	float cosInter(float,float,float);
	float inter(float a, float b, float mu);
};

#endif