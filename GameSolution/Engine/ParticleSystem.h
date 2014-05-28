#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include "Particle.h"
#include <vector>
#include <algorithm>

using std::vector;

namespace Engine {

	class ParticleSystem {
	protected:
		vector<Particle*> * particles;

		inline float random(float a, float b) {
			if (a > b)
				return random(b, a);

			float random = ((float) rand()) / (float) RAND_MAX;
		    float diff = b - a;
			float r = random * diff;
			return a + r;
		}

		void operator=(ParticleSystem e) { e; }

		inline void createParticle() {
			Particle *p = new Particle(random(minLifeTime,maxLifeTime));
			p->position = position + Vector2(random(minPositionOffset.x,maxPositionOffset.x),random(minPositionOffset.y,maxPositionOffset.y));
			p->velocity = Vector2(random(minVelocity.x,maxVelocity.x),random(minVelocity.y,maxVelocity.y));
			p->radius = (int)random((float)minRadius,(float)maxRadius);
			p->startColor = startColor;
			p->endColor = endColor;
			particles->push_back(p);
		}

	public:
		Vector2 position, minPositionOffset, maxPositionOffset, minVelocity, maxVelocity;
		int minRadius, maxRadius;
		int startColor, endColor;
		float sizeDelta;
		unsigned int size;
		float minLifeTime, maxLifeTime;

		ParticleSystem(unsigned int s) : size(s) {
			minLifeTime = maxLifeTime = 10;
			minRadius = maxRadius = 10;
			sizeDelta = 0;
			startColor = endColor = RGB(255,255,255);
			particles = new vector<Particle*>();
		}

		virtual bool isDead() {
			return false;
		}

		virtual void update(float dt) {
			for (unsigned int i = 0; i < particles->size(); i++) {
				Particle* p = (*particles)[i];
				p->update(dt);
				p->radius = (int)(p->radius + (sizeDelta * dt));
			}

			particles->erase(std::remove_if(particles->begin(), particles->end(), 
				[](Particle* p) {
					if (p->isDead()) {
						delete p;
						return true;
					}

					return false;
				}), particles->end());

			while (particles->size() < size) {
				createParticle();
			}
		}

		virtual void draw(EnhancedGraphics& g) {
			for (unsigned int i = 0; i < particles->size(); i++) {
				Particle* p = (*particles)[i];
				p->draw(g);
			}
		}

	};

}


#endif