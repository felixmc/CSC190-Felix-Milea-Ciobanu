#include "Projectile.h"
#include "Game.h"
#include "ExplosionParticleSystem.h"

static Vector2 proShape[] = { Vector2(0, -4), Vector2(1, 2), Vector2(-1, 2) };
static Shape* projShape = SHAPE(proShape);

const float Projectile::PROJ_V = 350;

Projectile::Projectile(Vector2 p, float rot) : GameObject(p, *projShape) {
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

	for (unsigned int i = 0; i < Game::enemyManager->enemies->size(); i++) {
		Enemy * target = Game::enemyManager->enemies->at(i);
		if (target->position.distance(position) <= target->radius) {
			detonate();
			if (!target->isDying && target->explode(*this))
				Game::score += target->points;

			break;
		}
	}
}

void EnemyProjectile::update(float dt) {
	GameObject::update(dt);

	if (Game::player->position.distance(position) <= 10) {
		detonate();
		//Game::player->hit(*this);
	}
}

bool Projectile::isDead() const {
	return isDetonated;
}

void Projectile::detonate() {
	if (!isDetonated) {
		isDetonated = true;
	}
}

Projectile::~Projectile() {

}