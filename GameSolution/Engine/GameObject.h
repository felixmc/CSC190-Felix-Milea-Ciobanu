#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Core.h"
#include "EnhancedGraphics.h"
#include "Shape.h"
#include "Matrix3.h"
#include "Vector3.h"

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
		
		inline void update(float dt) {
			velocity += acceleration * dt;
			position += velocity * dt;
		}

		inline virtual void draw(EnhancedGraphics& g)  {
			Matrix3 trans = Matrix3::translation(position)*Matrix3::rotation(rotation)*Matrix3::scale(scale);
			g.setColor(color);
			for (int i = 0; i < shape.size; i++) {
				Vector3 p1 = trans * Vector3(shape.points[i]);
				Vector3 p2 = trans * Vector3(shape.points[(i + 1) % shape.size]);
				g.drawLine(p1,p2);
			}
		}

		virtual inline GameObject operator= (const GameObject& other) const {
			return other;
		}
	};
}

#endif