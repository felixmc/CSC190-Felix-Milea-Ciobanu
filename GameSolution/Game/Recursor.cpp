#include "Recursor.h"
#include "Shape.h"
#include "Matrix2.h"
#include "Core.h"
#include <cmath>

static int l = 10;

static Vector2 baseShape[] = {
	Vector2(0, -sin(3.14f/2)*l), Vector2(cos(.524f)*l, -sin(.524f)*l), Vector2(cos(5.759f)*l, -sin(5.759f)*l),
	Vector2(0, -sin(4.712f)*l), Vector2(-cos(.524f)*l, sin(.524f)*l), Vector2(-cos(.524f)*l, -sin(.524f)*l)
};

const float Recursor::ROT_SPD = 0.2f;

Recursor::Recursor(Vector2 pos, int c) : oldPos(pos), GameObject(pos,*SHAPE(baseShape)) {
	parent = NULL;
	if (c > 0) {
		child = new Recursor(pos + (Vector2(15,15) * (float)c * 1.7f), c - 1);
		child->parent = this;
		scale += (c*1.25f);
	} else {
		child = NULL;
	}
}

int Recursor::getLevel() {
	if (parent == NULL) {
		return 1;
	} else {
		return parent->getLevel() + 1;
	}
}

Vector2 Recursor::getDynamicPosition() {
	if (parent == NULL)
		return position;

	Vector2 dest = parent->position;
	Vector2 diff = dest - position;
	Matrix3 trans = Matrix3::translation(position+diff)*Matrix3::rotation(rotation)*Matrix3::translation(diff)*Matrix3::scale(scale);
	Vector3 result = trans * position;
	return	Vector2(result.x, result.y);
}

void Recursor::update(float dt) {
	if (child != NULL)
		child->update(dt);

	if (parent != NULL) {
		oldPos = position;
		Vector2 dest = parent->position;
		Vector2 diff = position + (dest - parent->oldPos) - dest;
		Vector2 rotated = Matrix2::rotation(1.2f*getLevel()*dt) * diff;
		position = rotated + dest;
	}

	rotation += (.8f * dt * getLevel());
	GameObject::update(dt);	
}

void Recursor::draw(EnhancedGraphics& g) {
	
	if (parent == NULL)
		GameObject::draw(g);
	else {
		Matrix3 trans = Matrix3::translation(position)*Matrix3::rotation(rotation)*Matrix3::scale(scale);
		g.setColor(color);
		for (int i = 0; i < shape.size; i++) {
			Vector3 p1 = trans * Vector3(shape.points[i]);
			Vector3 p2 = trans * Vector3(shape.points[(i + 1) % shape.size]);
			g.drawLine(p1, p2);
		}
	}

	if (child != NULL)
		child->draw(g);
}