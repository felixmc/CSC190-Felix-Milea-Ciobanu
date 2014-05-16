#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "GameObject.h"
#include "Vector2.h"

using namespace Engine;

typedef bool (*ShipController)();

/* A bit more code, but decoupled ship control from keyboard */
struct PlayerShip : GameObject {
	PlayerShip(Vector2);

	void registerRotateLeft(ShipController);
	void registerRotateRight(ShipController);
	void registerMoveUp(ShipController);
	void registerMoveDown(ShipController);

	void update(float);
	void draw(Core::Graphics&);

private:
	GameObject* gun;

	static const float BASE_A;
	static const float MAX_V;
	static const float ROT_D;
	static const float SPEED;
	static const float FRICTION;

	ShipController rotateLeftController;
	ShipController rotateRightController;
	ShipController moveUpController;
	ShipController moveDownController;

	void rotate();
	void move(float);
};

#endif