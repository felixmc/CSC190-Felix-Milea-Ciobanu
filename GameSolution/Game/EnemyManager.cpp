#include "EnemyManager.h"
#include "EngineMath.h"
#include "Game.h"

EnemyManager::EnemyManager() {
	enemies = vector<Enemy*>();
	queue = vector<Enemy*>();
	projectiles = vector<EnemyProjectile*>();
}

EnemyManager::~EnemyManager() {

	for (unsigned int i = 0; i < enemies.size(); i++) {
		delete enemies.at(i);
	}

	for (unsigned int i = 0; i < queue.size(); i++) {
		delete queue.at(i);
	}

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		delete projectiles.at(i);
	}

}

void EnemyManager::update(float dt) {
	for (unsigned int i = 0; i < queue.size(); i++) {
		enemies.push_back(queue.at(i));
	}

	queue.clear();

	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
		[&](Enemy* p) {
			//if (p == NULL) return true;
			p->update(dt);
			return p->isDead;
	}), enemies.end());

	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), 
		[&](Projectile* p) {
			p->update(dt);

			Vector2 pos = p->position;
			bool isDead = p->isDead() || pos.x < -5 || pos.x > Game::SCREEN_WIDTH + 5 || pos.y < -5 || pos.y > Game::SCREEN_HEIGHT + 5;

			if (isDead) {
				delete p;
				return true;
			}

			return false;
	}), projectiles.end());
}

void EnemyManager::add(Enemy * e) {
	queue.push_back(e);
}

EnemyMinionShip* EnemyManager::spawnMinion(GameObject * target, Vector2& pos) {
	EnemyMinionShip * enemy = new EnemyMinionShip(target);
	enemy->position = pos;
	enemy->rotation = Math::random(0,2*Math::PI);
	queue.push_back(enemy);
	return enemy;
}

void EnemyManager::draw(EnhancedGraphics& g) {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->draw(g);
	}

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles.at(i)->draw(g);
	}

}