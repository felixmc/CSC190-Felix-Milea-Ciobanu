#include "Projectile.h"
#include "Game.h"
#include "DebugMemory.h"
#include "ExplosionParticleSystem.h"

static Vector2 proShape[] = { Vector2(0, -4), Vector2(1, 2), Vector2(-1, 2) };

const float Projectile::PROJ_V = 350;

Projectile::Projectile(Vector2 p, float rot) : GameObject(p, SHAPE(proShape)) {
	color = Color::RED;
	rotation = rot;
	isDetonated = false;
	velocity = Vector2(sin(rot), -cos(rot)) *PROJ_V;
}

EnemyProjectile::EnemyProjectile(Vector2 p, float rot) : Projectile(p, rot) {
	color = RGB(255,170,0);
}

void Projectile::update(float dt) {
	GameObject::update(dt);

	for (unsigned int i = 0; i < Game::enemyManager.enemies.size() && !isDetonated; i++) {
		Enemy * target = Game::enemyManager.enemies.at(i);
		if (target->position.distance(position) <= target->radius) {
			if (!target->isDying && target->explode(*this)) {
				Game::score += target->points;
			}

			detonate();
		}
	}
}

void EnemyProjectile::update(float dt) {
	GameObject::update(dt);

	if (Game::player.position.distance(position) <= 10) {
		detonate();
		Game::player.hit(*this);
	}
}

bool Projectile::isDead() const {
	return isDetonated;
}

void Projectile::detonate() {
	isDetonated = true;
}

Projectile::~Projectile() {

}