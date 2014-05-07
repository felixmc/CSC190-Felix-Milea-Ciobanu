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
const float PlayerShip::FRICTION = 5.f;
const float PlayerShip::MAX_V = 350.0f;

PlayerShip::PlayerShip(Vector2 startPos)
: GameObject(startPos, *SHAPE(ship)) {}

void PlayerShip::update(float dt) {
	moveX();
	moveY();
	GameObject::update(dt);
}

void PlayerShip::moveX() {
	if (moveLeftController != NULL && moveLeftController())
		velocity.x = max(-MAX_V, velocity.x - BASE_V);
	else if (moveRightController != NULL && moveRightController())
		velocity.x = min(MAX_V, velocity.x + BASE_V);
	else if (velocity.x > 0) {
		velocity.x = max(0, velocity.x - FRICTION);
	} else {
		velocity.x = min(0, velocity.x + FRICTION);
	}
}

void PlayerShip::moveY() {
	if (moveUpController != NULL && moveUpController())
		velocity.y = max(-MAX_V, velocity.y - BASE_V);
	else if (moveDownController != NULL && moveDownController())
		velocity.y = min(MAX_V, velocity.y + BASE_V);
	else if (velocity.y > 0) {
		velocity.y = max(0, velocity.y - FRICTION);
	} else {
		velocity.y = min(0, velocity.y + FRICTION);
	}
}

void PlayerShip::registerMoveLeft(ShipController c) { moveLeftController = c; }
void PlayerShip::registerMoveRight(ShipController c) { moveRightController = c; }
void PlayerShip::registerMoveUp(ShipController c) { moveUpController = c; }
void PlayerShip::registerMoveDown(ShipController c) { moveDownController = c; }