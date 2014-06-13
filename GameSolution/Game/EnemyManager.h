#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "EnemyMinionShip.h"
#include <vector>

using std::vector;

struct EnemyManager {
	void spawnMinion(GameObject *, Vector2&);
	Vector2 spawnPosition;

	EnemyManager();
	~EnemyManager();
	void add(Enemy *);
	void update(float);
	void draw(EnhancedGraphics&);

//private:
	vector<Enemy*> enemies, queue;
	vector<EnemyProjectile*> projectiles;
};

#endif