#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "Vector2.h"

namespace Engine {

	struct Matrix3 {
		const float x1, x2, x3, y1, y2, y3, z1, z2, z3;

		Matrix3() : x1(1), y1(0), z1(0), x2(0), y2(0), z2(1), x3(0), y3(0), z3(1) {}
		Matrix3(Vector2& v1, Vector2& v2) : x1(v1.x), y1(v1.y), z1(0), x2(v2.x), y2(v2.y), z2(0), x3(0), y3(0), z3(0) {}

		static Matrix3 rotation(float);
		static Matrix3 scale(float);
		static Matrix3 scaleX(float);
		static Matrix3 scaleY(float);
		static Matrix3 translation(float, float);
		static Matrix3 translation(Vector2&);

		Matrix3 operator*(Matrix3&);
		Matrix3 operator*(Vector2&);
	};

}

#endif