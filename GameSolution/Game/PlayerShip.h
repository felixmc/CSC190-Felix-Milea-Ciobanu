#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "GameObject.h"
#include "Vector2.h"
#include <vector>

using namespace Engine;

typedef bool (*ShipController)();

/* A bit more code, but decoupled ship control from keyboard */
struct PlayerShip : GameObject {
	PlayerShip(Vector2);

	GameObject* gun;

	void registerRotateLeft(ShipController);
	void registerRotateRight(ShipController);
	void registerMoveUp(ShipController);
	void registerMoveDown(ShipController);
	void registerFire(ShipController);

	void update(float);
	void draw(Core::Graphics&);

private:
	static const float BASE_A;
	static const float MAX_V;
	static const float ROT_D;
	static const float SPEED;
	static const float FRICTION;
	static const float TURRET_OFFSET;
	static const float FIRE_DELAY;
	static const float PROJ_V;

	std::vector<GameObject*> projectiles;
	ULONGLONG lastFired;

	ShipController rotateLeftController;
	ShipController rotateRightController;
	ShipController moveUpController;
	ShipController moveDownController;
	ShipController fireController;

	void rotate();
	void move(float);
};

#endif