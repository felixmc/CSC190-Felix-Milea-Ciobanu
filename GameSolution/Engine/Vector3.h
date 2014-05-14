#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace Engine {

	struct Vector3 {
		float x, y, z;
		Vector3() : x(0), y(0), z(0) {};
		explicit Vector3(float xv, float yv, float zv) : x(xv), y(yv), z(zv) {};
	};

}

#endif