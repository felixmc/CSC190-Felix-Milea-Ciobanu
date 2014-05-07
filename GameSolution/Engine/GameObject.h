#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Core.h"
#include "Shape.h"

namespace Engine {

	struct GameObject {
		Vector2 position, velocity, acceleration;
		const Shape shape;

		GameObject(const Vector2 startPos, const Shape& _shape) : position(startPos), shape(_shape) {}
		
		void update(float dt) {
			velocity += acceleration * dt;
			position += velocity * dt;
		}

		virtual void draw(Core::Graphics& g)  {
			for (int i = 0; i < shape.size; i++) {
				Vector2 p1 = shape.points[i] + position;
				Vector2 p2 = shape.points[(i + 1) % shape.size] + position;
				g.DrawLine(p1.x, p1.y, p2.x, p2.y);
			}
		}

		virtual inline GameObject operator= (const GameObject& other) const {
			return other;
		}
	};
}

#endif