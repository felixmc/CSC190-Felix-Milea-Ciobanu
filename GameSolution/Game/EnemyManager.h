#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "EnemyMinionShip.h"
#include <vector>

using std::vector;

class EnemyManager {
	Timer timer;
	float interval;
	float baseInterval;

	void spawnEnemy();

public:
	vector<Enemy*> * enemies;
	Vector2 spawnPosition;
	int baseColor;

	EnemyManager(float itv);
	void update(float);
	void draw(EnhancedGraphics&);
};

#endif