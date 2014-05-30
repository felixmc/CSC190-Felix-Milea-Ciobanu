#ifndef _ENGINE_MATH_H
#define _ENGINE_MATH_H

#include <cstdlib>

namespace Engine {

	namespace Math {
		const float PI = 3.14159265358979323846f;

		inline float random(float a, float b) {
			if (a > b)
				return random(b, a);

			float random = ((float) rand()) / (float) RAND_MAX;
		    float diff = b - a;
			float r = random * diff;
			return a + r;
		}

	}

}

#endif