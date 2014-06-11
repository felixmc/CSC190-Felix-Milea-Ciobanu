#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "GameObject.h"
#include "ParticleSystem.h"

using namespace Engine;

struct Projectile : public GameObject {
	static const float PROJ_V;

	ParticleSystem *tail;

	Projectile(Vector2, float);
	~Projectile();

	virtual void update(float);
	void detonate();
	bool isDead() const;

private:
	bool isDetonated;
};

struct EnemyProjectile : public Projectile {
	EnemyProjectile(Vector2, float);
	void update(float);
};

#endif