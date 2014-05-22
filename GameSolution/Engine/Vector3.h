#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "Vector2.h"

namespace Engine {

	struct Vector3 {
		float x, y, z;
		Vector3() : x(0), y(0), z(0) {};
		explicit Vector3(float xv, float yv, float zv) : x(xv), y(yv), z(zv) {};
		explicit Vector3(const Vector2& v) : x(v.x), y(v.y), z(0) {};

		operator Vector2 () const { return Vector2(x,y); }
	};

}

#endif