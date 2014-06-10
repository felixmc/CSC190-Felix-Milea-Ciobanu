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
	//tail = new ParticleSystem(10);
	//tail->minLifeTime = .05f;
	//tail->maxLifeTime  = .1f;
	//tail->minRadius = 3;
	//tail->maxRadius = 4;
	//tail->startColor = RGBA(255,200,0,200);
	//tail->endColor = RGBA(255,0,0,255);

	//Game::particleManager->add(tail);
}

void Projectile::update(float dt) {
	GameObject::update(dt);

	for (unsigned int i = 0; i < Game::enemyManager->enemies->size(); i++) {
		Enemy * target = Game::enemyManager->enemies->at(i);
		if (target->position.distance(position) <= target->radius) {
			detonate();
			target->explode(*this);
			if (target->isDead)
				Game::score += target->points;
			break;
		}
	}

	//tail->position = Matrix3::translation(position)*Matrix3::rotation(rotation)*Vector2(0,2);
	//tail->minVelocity = Matrix3::rotation(rotation)*(Vector2(-1,0));
	//tail->maxVelocity = velocity + Matrix3::rotation(rotation)*(Vector2(1,1));
	//tail->minPositionOffset = Matrix3::rotation(rotation)*Vector2(0,0);
	//tail->maxPositionOffset = Matrix3::rotation(rotation)*Vector2(0,1);
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
	/*tail->dead = true;*/
}