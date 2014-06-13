#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Core.h"
#include "EnhancedGraphics.h"
#include "Shape.h"
#include "Matrix3.h"
#include "Vector3.h"
#include "DebugMemory.h"

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
			shape.draw(g,color,position,scale,rotation);
		}

		virtual inline GameObject operator= (const GameObject& other) const {
			return other;
		}
	};
}

#endif