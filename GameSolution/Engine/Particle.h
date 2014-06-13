#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "DebugMemory.h"
#include "EnhancedGraphics.h"
#include "Matrix3.h"
#include "EngineMath.h"

namespace Engine {

	struct ENGINE_SHARED Particle {
		Vector2 position, velocity;
		int radius;
		int startColor;
		int endColor;
		float lifeTime;
		float maxLifeTime;

		Particle(float l) : maxLifeTime(l), lifeTime(0) {}

		inline bool isDead() {
			return lifeTime >= maxLifeTime || radius <= 0;
		}

		inline void update(float dt) {
			lifeTime += dt;
			position += velocity * dt;
		}

		inline void draw(EnhancedGraphics& g) {

			int dim = (radius*2)+1;
			float* map = Particle::particleMap(radius);

			for (int yi = 0; yi < dim; yi++) {
				for (int xi = 0; xi < dim; xi++) {
					float mu = map[(yi * dim) + (xi)];
					g.setColor(Color::interpolate(startColor,endColor,mu));
					g.drawPoint(Vector2(xi + position.x - (radius), yi+position.y - (radius)));
				}
			}

		}

	private:
		static bool loaded[20];
		static float * cache[20];

	public:
		static float* particleMap(int);
		static void cleanup() {
			for (int i = 0; i < 20; i++) {
				delete cache[i];
			}
		}
	};

}

#endif