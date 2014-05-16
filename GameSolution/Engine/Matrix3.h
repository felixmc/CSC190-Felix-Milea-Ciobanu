#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "Vector2.h"
#include "Vector3.h"

namespace Engine {

	struct Matrix3 {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;

		Matrix3() : x1(1), y1(0), z1(0), x2(0), y2(1), z2(0), x3(0), y3(0), z3(1) {}
		Matrix3(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3)
			: x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2), x3(x3), y3(y3), z3(z3) {}
		Matrix3(const Vector2& v1, const Vector2& v2) : x1(v1.x), y1(v1.y), z1(0), x2(v2.x), y2(v2.y), z2(0), x3(0), y3(0), z3(1) {}

		static Matrix3 rotation(float a) {
			return Matrix3(Vector2(cos(a), sin(a)), Vector2(-sin(a), cos(a)));
		}

		static Matrix3 scale(float s) {
			return Matrix3(Vector2(s, 0), Vector2(0, s));
		}

		static Matrix3 scaleX(float s) {
			return Matrix3(Vector2(s, 0), Vector2(0, 1));		
		}

		static Matrix3 scaleY(float s) {
			return Matrix3(Vector2(1, 0), Vector2(0, s));
		}

		static Matrix3 translation(float x, float y) {
			return Matrix3(1,0,x,0,1,y,0,0,1);
		}

		static Matrix3 translation(const Vector2& v) {
			return translation(v.x, v.y);
		}

		Matrix3 operator*(const Matrix3& m) {
			return Matrix3(
				x1*m.x1+x2*m.y1+x3*m.z1, x1*m.x2+x2*m.y2+x3*m.z2, x1*m.x3+x2*m.y3+x3*m.z3,
				y1*m.x1+y2*m.y1+y3*m.z1, y1*m.x2+y2*m.y2+y3*m.z2, y1*m.x3+y2*m.y3+y3*m.z3,
				z1*m.x1+z2*m.y1+z3*m.z1, z1*m.x2+z2*m.y2+z3*m.z2, z1*m.x3+z2*m.y3+z3*m.z3
			);
		}

		Vector3 operator*(const Vector2& v) {
			return *this * Vector3(v.x, v.y, 1);
		}

		Vector3 operator*(const Vector3& v) {
			return Vector3(
				x1*v.x+x2*v.y+x3,
				y1*v.x+y2*v.y+y3,
				z1*v.x+z2*v.y+z3
			);
		}
	};

}

#endif