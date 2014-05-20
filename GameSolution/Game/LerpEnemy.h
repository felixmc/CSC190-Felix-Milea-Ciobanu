#ifndef _LERP_ENEMY_H_
#define _LERP_ENEMY_H_

#include "GameObject.h"
#include "Shape.h"

using namespace Engine;

struct LerpEnemy : GameObject {
	Shape path;

	LerpEnemy(Shape&);

	void update(float);

private:
	static const float SPEED;
	float mu;
	float muInc;
	int pointIndex;
};

#endif