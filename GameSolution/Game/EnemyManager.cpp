#include "EnemyManager.h"
#include "EngineMath.h"
#include "Game.h"

EnemyManager::EnemyManager() {
	enemies = new vector<Enemy*>();
	queue = new vector<Enemy*>();
	projectiles = new vector<EnemyProjectile*>();
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

	projectiles->erase(std::remove_if(projectiles->begin(), projectiles->end(), 
		[&](Projectile* p) {
			p->update(dt);

			Vector2 pos = p->position;
			bool isDead = p->isDead() || pos.x < -5 || pos.x > Game::SCREEN_WIDTH + 5 || pos.y < -5 || pos.y > Game::SCREEN_HEIGHT + 5;

			if (isDead) {
				delete p;
				return true;
			}

			return false;
	}), projectiles->end());
}

void EnemyManager::add(Enemy * e) {
	enemies->push_back(e);
}

void EnemyManager::spawnMinion(GameObject * object, Vector2& pos) {
	EnemyMinionShip * enemy = new EnemyMinionShip(object);
	enemy->position = pos;
	enemy->rotation = Math::random(0,2*Math::PI);
	enemies->push_back(enemy);
}

void EnemyManager::draw(EnhancedGraphics& g) {
	for (unsigned int i = 0; i < enemies->size(); i++) {
		enemies->at(i)->draw(g);
	}

	for (unsigned int i = 0; i < projectiles->size(); i++) {
		projectiles->at(i)->draw(g);
	}

}