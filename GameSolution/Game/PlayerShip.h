#ifndef _PLAYERSHIP_H_
#define _PLAYERSHIP_H_

#include "GameObject.h"
#include "Vector2.h"

using namespace Engine;

typedef bool (*ShipController)();

/* A bit more code, but decoupled ship control from keyboard */
struct PlayerShip : GameObject {
	PlayerShip(Vector2&);

	void registerMoveLeft(ShipController);
	void registerMoveRight(ShipController);
	void registerMoveUp(ShipController);
	void registerMoveDown(ShipController);
	void registerStopX(ShipController);
	void registerStopY(ShipController);

	void update(float);

private:
	static const float BASE_V;
	static const float MAX_V;

	ShipController moveLeftController;
	ShipController moveRightController;
	ShipController moveUpController;
	ShipController moveDownController;
	ShipController stopXController;
	ShipController stopYController;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopX();
	void stopY();
};

#endif