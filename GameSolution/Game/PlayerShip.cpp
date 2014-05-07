#include "PlayerShip.h"
#include "Shape.h"
#include <cmath>

// this should make the ship 59x59 pixels
static Vector2 ship[] = {
	// top
	Vector2(0,-29),
	
	// right side
	Vector2(3,-4), Vector2(25,14),Vector2(27,1),
	Vector2(29,22),Vector2(10,11),Vector2(9,15),Vector2(4,14),
	
	// bottom
	Vector2(0,29),

	// left side
	Vector2(-4,14),Vector2(-9,15),Vector2(-10,11),
	Vector2(-29,22),Vector2(-27,1),Vector2(-25,14),Vector2(-3,-4)
};

const float PlayerShip::BASE_V = 25.f;
const float PlayerShip::MAX_V = 170.0f;

PlayerShip::PlayerShip(Vector2 startPos)
: GameObject(startPos, SHAPE(ship)) {}

void PlayerShip::update(float dt) {
	moveLeft();
	moveRight();
	moveUp();
	moveDown();
	stopX();
	stopY();
	GameObject::update(dt);
}

void PlayerShip::moveLeft() {
	if (moveLeftController != NULL && moveLeftController())
		velocity.x = max(-MAX_V, velocity.x - BASE_V);
}

void PlayerShip::moveRight() {
	if (moveRightController != NULL && moveRightController())
		velocity.x = min(MAX_V, velocity.x + BASE_V);
}

void PlayerShip::moveUp() {
	if (moveUpController != NULL && moveUpController())
		velocity.y = max(-MAX_V, velocity.y - BASE_V);
}

void PlayerShip::moveDown() {
	if (moveDownController != NULL && moveDownController())
		velocity.y = min(MAX_V, velocity.y + BASE_V);
}

void PlayerShip::stopX() {
	if (stopXController != NULL && stopXController())
		if (velocity.x > 0) {
			velocity.x = max(0, velocity.x - BASE_V);
		} else {
			velocity.x = min(0, velocity.x + BASE_V);
		}
}

void PlayerShip::stopY() {
	if (stopYController != NULL && stopYController())
		if (velocity.y > 0) {
			velocity.y = max(0, velocity.y - BASE_V);
		} else {
			velocity.y = min(0, velocity.y + BASE_V);
		}
}

void PlayerShip::registerMoveLeft(ShipController c) { moveLeftController = c; }
void PlayerShip::registerMoveRight(ShipController c) { moveRightController = c; }
void PlayerShip::registerMoveUp(ShipController c) { moveUpController = c; }
void PlayerShip::registerMoveDown(ShipController c) { moveDownController = c; }
void PlayerShip::registerStopX(ShipController c) { stopXController = c; }
void PlayerShip::registerStopY(ShipController c) { stopYController = c; }