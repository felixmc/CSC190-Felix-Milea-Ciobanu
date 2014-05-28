#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "EnhancedGraphics.h"
#include "Matrix3.h"
#include "EngineMath.h"

namespace Engine {

	struct Particle {
		Vector2 position, velocity;
		int radius;
		int startColor;
		int endColor;
		float lifeTime;
		const float maxLifeTime;

		Particle(float l) : maxLifeTime(l), lifeTime(0) {}

		inline bool isDead() {
			return lifeTime >= maxLifeTime || radius <= 0;
		}

		inline void update(float dt) {
			lifeTime += dt;
			position += velocity * dt;
		}

		inline void draw(EnhancedGraphics& g) {

			for (int i = 0; i < radius; i++) {
				g.setColor(Color::interpolate(startColor, endColor, (float)i / radius));
				float ps = 2 * Math::PI * radius;
				for (int j = 0; j < ps; j++) {
					Vector2 p = Matrix3::rotation(j/ps*2*Engine::Math::PI) * Vector2(0,(float)i);
					g.drawPoint(position+p);
				}
			}

		}

	private:
		void operator=(Particle e) { e; }
	};

}

#endif