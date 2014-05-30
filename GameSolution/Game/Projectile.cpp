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
	tail = new ParticleSystem(10);
	tail->minLifeTime = .05f;
	tail->maxLifeTime  = .1f;
	tail->minRadius = 3;
	tail->maxRadius = 4;
	tail->startColor = RGBA(255,200,0,200);
	tail->endColor = RGBA(255,0,0,255);

	Game::particleManager->add(tail);
}

void Projectile::update(float dt) {
	GameObject::update(dt);
	tail->position = Matrix3::translation(position)*Matrix3::rotation(rotation)*Vector2(0,2);
	tail->minVelocity = Matrix3::rotation(rotation)*(Vector2(-1,0));
	tail->maxVelocity = velocity + Matrix3::rotation(rotation)*(Vector2(1,1));
	tail->minPositionOffset = Matrix3::rotation(rotation)*Vector2(0,0);
	tail->maxPositionOffset = Matrix3::rotation(rotation)*Vector2(0,1);
}

inline bool Projectile::isDead() const {
	return isDetonated;
}

void Projectile::detonate() {
	if (!isDetonated) {
		isDetonated = true;

		ExplosionParticleSystem * ps = new ExplosionParticleSystem(200);
		ps->position = position;
		ps->minVelocity = Vector2(-160,-160);
		ps->maxVelocity = Vector2(160,160);
		ps->minLifeTime = .1f;
		ps->maxLifeTime  = .75f;
		ps->minRadius = 2;
		ps->maxRadius = 3;
		ps->startColor = RGBA(255,50,0,210);
		ps->endColor = RGBA(255,0,0,255);
		
		Game::particleManager->add(ps);
	}
}

Projectile::~Projectile() {
	tail->dead = true;
}