#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Vector2.h"
#define NOMINMAX
#include <algorithm>

namespace Engine {
	using std::min;
	using std::max;

	#define SHAPE(arr) new Shape(sizeof(arr)/sizeof(Vector2), arr)

	struct Shape {
		const Vector2 * points;
		const int size;

		Shape(int _size, const Vector2 pts[]) : size(_size), points(pts) {
			
		}

		float getMostLeft() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = min(most, points[i].x);
			}
			return most;
		}

		float getMostRight() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = max(most, points[i].x);
			}
			return most;
		}

		float getMostUp() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = min(most, points[i].y);
			}
			return most;
		}
		
		float getMostDown() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = max(most, points[i].y);
			}
			return most;
		}

		float getWidth() const {
			return abs(getMostLeft()) + getMostRight();
		}

		float getHeight() const {
			return abs(getMostUp()) + getMostDown();
		}

	private:
		inline void operator= (const Shape& other) const { other; }

	};
}

#endif