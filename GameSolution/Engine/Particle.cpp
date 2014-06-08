#include "Particle.h"

bool Engine::Particle::loaded[20];
float * Engine::Particle::cache[20];

float* Engine::Particle::particleMap(const int radius) {
	assert(radius < 20 && radius > 0);
	if (!loaded[radius]) {
		int size = (int)pow((radius*2)+1,2);
		cache[radius] = new float[size];
		std::fill(cache[radius], cache[radius] + size, 1.0f);

		for (int i = 0; i <= radius; i++) {
			float mu = ((float)i / (float)radius);
			float ps = 2 * Engine::Math::PI * radius * 2;
			for (int j = 0; j < ps; j++) {
				Vector2 p = Matrix3::rotation(j/ps*2*Engine::Math::PI) * Vector2(0,(float)i);
				int x = (int) floor(p.x + 0.5);
				int y = (int) floor(p.y + 0.5);
				int coor = ((y+radius) * ((radius*2)+1)) + (x+radius);

				float c = cache[radius][coor];

				cache[radius][coor] = (c + mu) / 2;
			}
		}

		loaded[radius] = true;
	}

	return cache[radius];
}