#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "GameObject.h"
#include "ExplosionParticleSystem.h"
#include "Projectile.h"
#include <vector>

using namespace Engine;

typedef bool (*ShipController)();

/* A bit more code, but decoupled ship control from keyboard */
struct PlayerShip : GameObject {
	GameObject* gun;
	ParticleSystem * leftPs, * rightPs;
	std::vector<Projectile*> projectiles;
	bool isDead;
	int hp;

	PlayerShip(Vector2);

	void registerRotateLeft(ShipController);
	void registerRotateRight(ShipController);
	void registerMoveUp(ShipController);
	void registerMoveDown(ShipController);
	void registerFire(ShipController);

	void hit(EnemyProjectile&);

	void update(float);
	void draw(EnhancedGraphics&);

private:
	static const float BASE_A;
	static const float MAX_V;
	static const float ROT_D;
	static const float SPEED;
	static const float FRICTION;
	static const float TURRET_OFFSET;
	static const float FIRE_DELAY;

	ULONGLONG lastFired;

	ShipController rotateLeftController;
	ShipController rotateRightController;
	ShipController moveUpController;
	ShipController moveDownController;
	ShipController fireController;

	void rotate(float);
	void move(float);
};

#endif