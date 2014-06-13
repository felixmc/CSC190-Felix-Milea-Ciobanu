#include "LerpEnemy.h"
#include "Shape.h"
#include "DebugMemory.h"

static Vector2 diamond[] = {
	Vector2(0,-20),Vector2(20,0),
	Vector2(0,20),Vector2(-20,0)
};

const float LerpEnemy::SPEED = 300.0f;

LerpEnemy::LerpEnemy(Shape& pth)
	: GameObject(pth.points[0], SHAPE(diamond)), path(pth) {
	mu = 0;
	pointIndex = 0;
	muInc = SPEED / (path.points[0] - path.points[1]).length();
}

void LerpEnemy::update(float dt) {
	int nextIndex = (pointIndex + 1) % path.size;

	mu += (muInc * dt);

	while (mu > 1) {
		mu -= 1;
		pointIndex = nextIndex;
		nextIndex = (pointIndex + 1) % path.size;
		muInc = SPEED / (path.points[pointIndex] - path.points[nextIndex]).length();
	}

	position = Vector2::lerp(path.points[pointIndex], path.points[nextIndex], mu);

}