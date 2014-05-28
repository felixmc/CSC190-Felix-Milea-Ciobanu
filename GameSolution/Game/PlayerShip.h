#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "GameObject.h"
#include "ExplosionParticleSystem.h"
#include "Vector2.h"
#include <vector>

using namespace Engine;

typedef bool (*ShipController)();

/* A bit more code, but decoupled ship control from keyboard */
struct PlayerShip : GameObject {
	GameObject* gun, *target;
	ParticleSystem * leftPs, * rightPs;

	PlayerShip(Vector2);

	void registerTarget(GameObject*);
	void registerRotateLeft(ShipController);
	void registerRotateRight(ShipController);
	void registerMoveUp(ShipController);
	void registerMoveDown(ShipController);
	void registerFire(ShipController);

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
	static const float PROJ_V;
	static const float PROJ_R;

	std::vector<GameObject*> projectiles;
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