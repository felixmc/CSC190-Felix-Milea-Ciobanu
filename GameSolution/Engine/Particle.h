#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "EnhancedGraphics.h"
#include "Matrix3.h"

namespace Engine {

	struct Particle {
		Vector2 position, velocity;
		int radius;
		int startColor;
		int endColor;
		float lifeTime;
		const float maxLifeTime;

		const float PI;

		Particle(float l) : maxLifeTime(l), lifeTime(0), PI(3.14159265358979323846f) {}

		bool isDead() {
			return lifeTime >= maxLifeTime;
		}

		void update(float dt) {
			lifeTime += dt;
			position += velocity;
		}

		void draw(EnhancedGraphics& g) {

			for (int i = 0; i < radius; i++) {
				g.setColor(Color::interpolate(startColor, endColor, (float)i / radius));
				float ps = 2 * PI * radius;
				for (int j = 0; j < ps; j++) {
					Vector2 p = Matrix3::rotation(j/ps*2*PI) * Vector2(0,(float)i);
					g.drawPoint(position+p);
				}
			}

		}

	private:
		void operator=(Particle e) { e; }
	};

}

#endif