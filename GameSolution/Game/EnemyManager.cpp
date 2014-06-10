#include "EnemyManager.h"
#include "EngineMath.h"

EnemyManager::EnemyManager() {
	enemies = new vector<Enemy*>();
	queue = new vector<Enemy*>();
}

void EnemyManager::update(float dt) {
	for (unsigned int i = 0; i < queue->size(); i++) {
		enemies->push_back(queue->at(i));
	}

	queue->clear();

	enemies->erase(std::remove_if(enemies->begin(), enemies->end(), 
	[&](Enemy* p) {
		p->update(dt);
		return p->isDead;
	}), enemies->end());
}

void EnemyManager::add(Enemy * e) {
	enemies->push_back(e);
}

void EnemyManager::spawnMinion(GameObject * object) {
	EnemyMinionShip * enemy = new EnemyMinionShip(object);
	enemy->position = spawnPosition;
	enemy->rotation = Math::random(0,2*Math::PI);
	enemies->push_back(enemy);
}

void EnemyManager::draw(EnhancedGraphics& g) {
	for (unsigned int i = 0; i < enemies->size(); i++) {
		enemies->at(i)->draw(g);
	}
}