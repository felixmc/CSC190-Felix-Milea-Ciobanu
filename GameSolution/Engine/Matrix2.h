#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include "Vector2.h"
#include <cmath>

namespace Engine {

	struct Matrix2 {
		float x1, x2, y1, y2;

		Matrix2() : x1(1), y1(0), x2(0), y2(1) {}
		Matrix2(const Vector2& v1, const Vector2& v2) : x1(v1.x), y1(v1.y), x2(v2.x), y2(v2.y) {}

		static Matrix2 rotation(float a) {
			return Matrix2(Vector2(cos(a), sin(a)), Vector2(-sin(a), cos(a)));
		}

		static Matrix2 scale(float s) {
			return Matrix2(Vector2(s, 0), Vector2(0, s));
		}
		
		static Matrix2 scaleX(float s) {
			return Matrix2(Vector2(s, 0), Vector2(0, 1));		
		}
		
		static Matrix2 scaleY(float s) {
			return Matrix2(Vector2(1, 0), Vector2(0, s));		
		}

		inline Matrix2 operator*(const Matrix2& m) {
			return Matrix2(Vector2(x1 * m.x1 + x2 * m.y1, y1 * m.x1 + y2 * m.y1)
				, Vector2(x1 * m.x2 + x2*m.y2, y1*m.x2+y2*m.y2));
		}
		
		inline Vector2 operator*(const Vector2& v) {
			return Vector2(x1*v.x + x2*v.y, y1*v.x + y2*v.y);
		}

		inline friend std::ostream& operator<< (std::ostream& stream, const Matrix2& m) {
			return stream << "[" << m.x1 << " " << m.x2 << "]\n[" << m.y1 << " " << m.y2 << "]";
		}
	};

}

#endif