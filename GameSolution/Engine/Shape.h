#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Vector2.h"
#define NOMINMAX
#include <algorithm>
#include "EnhancedGraphics.h"
#include "Matrix3.h"

namespace Engine {
	using std::min;
	using std::max;

#define SHAPE(arr) new Shape(sizeof(arr)/sizeof(Vector2), arr)

	struct Shape {
		const Vector2 * points;
		const int size;

		Shape(int _size, const Vector2 pts[]) : size(_size), points(pts) {

		}

		static Shape * generate(const unsigned int sides, float scale) {
			Vector2 * shape = new Vector2[sides];

			for (unsigned int i = 0; i < sides; i++) {
				float angle = (3.14f * 2 / sides) * i;
				shape[i] = Vector2(cos(angle), sin(angle))*scale;
			}

			return new Shape(sides,shape);
		}

		inline void draw(EnhancedGraphics& g, int color, Vector2 position, float scale = 1, float rotation = 0) const {
			Matrix3 trans = Matrix3::translation(position)*Matrix3::rotation(rotation)*Matrix3::scale(scale);
			g.setColor(color);
			for (int i = 0; i < size; i++) {
				Vector3 p1 = trans * Vector3(points[i]);
				Vector3 p2 = trans * Vector3(points[(i + 1) % size]);
				g.drawLine(p1,p2);
			}
		}

		inline float getMostLeft() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = min(most, points[i].x);
			}
			return most;
		}

		inline float getMostRight() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = max(most, points[i].x);
			}
			return most;
		}

		inline float getMostUp() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = min(most, points[i].y);
			}
			return most;
		}

		inline float getMostDown() const {
			float most = 0;
			for (int i = 0; i < size; i++) {
				most = max(most, points[i].y);
			}
			return most;
		}

		inline float getWidth() const {
			return abs(getMostLeft()) + getMostRight();
		}

		inline float getHeight() const {
			return abs(getMostUp()) + getMostDown();
		}

	private:
		inline void operator= (const Shape& other) const { other; }

	};
}

#endif