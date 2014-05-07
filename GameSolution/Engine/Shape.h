#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Vector2.h"
#include <cstdarg>

namespace Engine {

	#define SHAPE(arr) Shape(sizeof(arr)/sizeof(Vector2), arr)

	struct Shape {
		const Vector2 * points;
		const int size;

		Shape(int _size, const Vector2 pts[]) : size(_size), points(pts) {}


		inline Shape operator= (const Shape& other) const {
			return other;
		}

	};
}

#endif