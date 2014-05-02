#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"

class GameObject {
	Vector2 position, velocity, acceleration;


public:
	GameObject(const Vector2& startPos) : position(startPos) {
	
	}

	void update(float dt) {
	
	}

	void draw() {
	
	}

	Vector2 getPosition() {
		return position;
	}

	Vector2 getVelocity() {
		return velocity;
	}

	Vector2 getAcceleration() {
		return acceleration;
	}
};

#endif