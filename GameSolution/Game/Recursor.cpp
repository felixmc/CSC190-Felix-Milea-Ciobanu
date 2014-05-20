#include "Recursor.h"
#include "Shape.h"
#include "Core.h"
#include <cmath>

static Vector2 baseShape[] = { Vector2(0, -14), Vector2(12, 13), Vector2(-12, 13) };

const float Recursor::ROT_SPD = 0.06f;

Recursor::Recursor(Vector2 pos, int c, Recursor* p)
	: parent(p), GameObject(pos,*SHAPE(baseShape)) {
		if (c > 0) {
			child = new Recursor(pos + (Vector2(10,10) * (float)c), c - 1, this);
			scale += c;
		} else {
			child = NULL;
		}

		if (parent == NULL) {
			level = 1;
		} else {
			level = parent->level + 1;
			rotation = parent->rotation + (.3f * level);
		}
}

void Recursor::update(float dt) {
	if (parent != NULL) {
		Vector2 dest = parent->position;
		Vector2 diff = dest - position;
		//float radius = sqrt((diff.x * diff.x) + (diff.y + diff.y));
		float radius = diff.length();
		position = dest + (Vector2(sin(rotation)*radius,-cos(rotation)*radius));
		rotation += (ROT_SPD * level);
	} else {
		GameObject::update(dt);	
	}

	if (child != NULL)
		child->update(dt);
}

void Recursor::draw(Core::Graphics& g) {
	GameObject::draw(g);

	if (child != NULL)
		child->draw(g);
}