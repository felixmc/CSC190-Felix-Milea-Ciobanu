#include "EnemyManager.h"
#include "EngineMath.h"

EnemyManager::EnemyManager(float itv) : baseInterval(itv), interval(itv) {
	enemies = new vector<Enemy*>();
	timer.start();
	baseColor = RGB(255,0,128);
}

void EnemyManager::update(float dt) {
	enemies->erase(std::remove_if(enemies->begin(), enemies->end(), 
	[&](Enemy* p) {
		p->update(dt);
		return p->isDead;
	}), enemies->end());

	interval = baseInterval + (enemies->size() / 1000.0f);

	if (timer.intervalElapsed() >= interval) {
		spawnEnemy();
		timer.interval();
	}
}

void EnemyManager::spawnEnemy() {
	EnemyMinionShip * enemy = new EnemyMinionShip();
	enemy->position = spawnPosition;
	enemy->color = baseColor;
	enemy->rotation = Math::random(0,2*Math::PI);
	enemies->push_back(enemy);
}

void EnemyManager::draw(EnhancedGraphics& g) {
	for (unsigned int i = 0; i < enemies->size(); i++) {
		enemies->at(i)->draw(g);
	}
}