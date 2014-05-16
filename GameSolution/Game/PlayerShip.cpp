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

const float PlayerShip::BASE_A = 25.f;
const float PlayerShip::MAX_V = 350.0f;
const float PlayerShip::ROT_D = 0.04f;
const float PlayerShip::SPEED = 5000.0f;
const float PlayerShip::FRICTION = 30.0f;

PlayerShip::PlayerShip(Vector2 startPos)
: GameObject(startPos, *SHAPE(ship)) {}

void PlayerShip::update(float dt) {
	rotate();
	move(dt);
	
	velocity += acceleration * dt;

	// max out velocity
	velocity.x = velocity.x > 0 ? min(MAX_V, velocity.x) : max(-MAX_V, velocity.x);
	velocity.y = velocity.y > 0 ? min(MAX_V, velocity.y) : max(-MAX_V, velocity.y);

	position += velocity * dt;
}

void PlayerShip::rotate() {
	if (rotateLeftController != NULL && rotateLeftController())
		rotation -= ROT_D;
	else if (rotateRightController != NULL && rotateRightController())
		rotation += ROT_D;
}

void PlayerShip::move(float dt) {
	if (moveUpController != NULL && moveUpController())
		acceleration = Vector2(sin(rotation), -cos(rotation)) * SPEED * dt;
	else if (moveDownController != NULL && moveDownController())
		acceleration = Vector2(sin(rotation), -cos(rotation)) * -SPEED * dt;
	else { // friction
		acceleration = Vector2();
		velocity.x = velocity.x > 0 ? max(0, velocity.x - FRICTION*dt) : min(0, velocity.x + FRICTION*dt);
		velocity.y = velocity.y > 0 ? max(0, velocity.y - FRICTION*dt) : min(0, velocity.y + FRICTION*dt);
	}
}

void PlayerShip::registerRotateLeft(ShipController c) { rotateLeftController = c; }
void PlayerShip::registerRotateRight(ShipController c) { rotateRightController = c; }
void PlayerShip::registerMoveUp(ShipController c) { moveUpController = c; }
void PlayerShip::registerMoveDown(ShipController c) { moveDownController = c; }