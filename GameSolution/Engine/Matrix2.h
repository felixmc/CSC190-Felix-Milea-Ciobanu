#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include "Vector2.h"

namespace Engine {

	struct Matrix2 {
		const float x1, x2, y1, y2;

		Matrix2() : x1(1), y1(0), x2(0), y2(1) {}
		Matrix2(Vector2& v1, Vector2& v2) : x1(v1.x), y1(v1.y), x2(v2.x), y2(v2.y) {}

		static Matrix2 rotation(float);
		static Matrix2 scale(float);
		static Matrix2 scaleX(float);
		static Matrix2 scaleY(float);

		Matrix2 operator*(Matrix2&);
		Matrix2 operator*(Vector2&);
	};

}

#endif