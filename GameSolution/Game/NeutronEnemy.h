#ifndef _NEUTRON_ENEMY_H_
#define _NEUTRON_ENEMY_H_

#include "Game.h"

struct NeutronEnemy : Enemy {

	GameObject* target;
	bool shrink;
	Timer timer, fireTimer;
	vector<EnemyMinionShip*> minions;
	Interpolation * hueInter, * posInter, * scaleInter;
	int hp;

	static const float MINION_DELAY;
	static const float FIRE_DELAY, FIRE_CHANCE;

	NeutronEnemy(GameObject* target, Vector2 pos);
	void update(float);
	void draw(EnhancedGraphics&);
	bool explode(Projectile&);
};

#endif