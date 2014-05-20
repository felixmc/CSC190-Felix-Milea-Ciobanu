#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Core.h"
#include "Shape.h"
#include "Matrix3.h"
#include "Vector3.h"
#include "Color.h"

namespace Engine {

	struct GameObject {
		float rotation;
		float scale;
		int color;
		Vector2 position, velocity, acceleration;
		const Shape shape;

		GameObject(const Vector2 startPos, const Shape& _shape) : position(startPos), shape(_shape) {
			rotation = 0;
			scale = 1;
			color = Color::WHITE;
		}
		
		void update(float dt) {
			velocity += acceleration * dt;
			position += velocity * dt;
		}

		virtual void draw(Core::Graphics& g)  {
			Matrix3 trans = Matrix3::translation(position)*Matrix3::rotation(rotation)*Matrix3::scale(scale);
			g.SetColor(color);
			for (int i = 0; i < shape.size; i++) {
				Vector3 p1 = trans * Vector3(shape.points[i]);
				Vector3 p2 = trans * Vector3(shape.points[(i + 1) % shape.size]);
				g.DrawLine(p1.x, p1.y, p2.x, p2.y);
			}
		}

		virtual inline GameObject operator= (const GameObject& other) const {
			return other;
		}
	};
}

#endif