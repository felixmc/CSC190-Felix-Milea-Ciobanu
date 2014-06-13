#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include "EngineMath.h"
#include "Particle.h"
#include <vector>
#include <algorithm>
#include "DebugMemory.h"

using std::vector;

namespace Engine {

	class ParticleSystem {
	protected:
		vector<Particle> particles;

		//void operator=(ParticleSystem e) { e; }

		inline Particle createParticle() {
			Particle p = Particle(Math::random(minLifeTime,maxLifeTime));
			p.position = position + Vector2(Math::random(minPositionOffset.x,maxPositionOffset.x),Math::random(minPositionOffset.y,maxPositionOffset.y));
			p.velocity = Vector2(Math::random(minVelocity.x,maxVelocity.x),Math::random(minVelocity.y,maxVelocity.y));
			p.radius = (int)Math::random((float)minRadius,(float)maxRadius);
			p.startColor = startColor;
			p.endColor = endColor;
			particles.push_back(p);

			return p;
		}

	public:
		Vector2 position, minPositionOffset, maxPositionOffset, minVelocity, maxVelocity;
		int minRadius, maxRadius;
		int startColor, endColor;
		float sizeDelta;
		unsigned int size;
		float minLifeTime, maxLifeTime;
		bool dead;

		ParticleSystem(unsigned int s) : size(s) {
			minLifeTime = maxLifeTime = 10;
			minRadius = maxRadius = 10;
			sizeDelta = 0;
			startColor = endColor = RGB(255,255,255);
			particles = vector<Particle>();
			dead = false;
		}

		virtual bool isDead() {
			return dead;
		}

		virtual void update(float dt) {
			for (unsigned int i = 0; i < particles.size(); i++) {
				Particle& p = particles[i];
				p.update(dt);
				p.radius = (int)(p.radius + (sizeDelta * dt));
			}

			particles.erase(std::remove_if(particles.begin(), particles.end(), 
				[](Particle& p) {
					if (p.isDead()) {
						return true;
					}

					return false;
				}), particles.end());

			while (particles.size() < size) {
				createParticle();
			}
		}

		virtual void draw(EnhancedGraphics& g) {
			for (unsigned int i = 0; i < particles.size(); i++) {
				Particle p = particles[i];
				p.draw(g);
			}
		}

	};

}


#endif