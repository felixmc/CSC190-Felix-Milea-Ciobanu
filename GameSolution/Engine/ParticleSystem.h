#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include "Particle.h"
#include <vector>

using std::vector;

namespace Engine {

	class ParticleSystem {
		vector<Particle*> * particles;

		float random(float a, float b) {
			float random = ((float) rand()) / (float) RAND_MAX;
		    float diff = b - a;
			float r = random * diff;
			return a + r;
		}

		void createParticle() {
			Particle *p = new Particle(random(minLifeTime,maxLifeTime));
			p->position = position + Vector2(random(minPositionOffset.x,maxPositionOffset.x),random(minPositionOffset.y,maxPositionOffset.y));
			p->velocity = Vector2(random(minVelocity.x,maxVelocity.x),random(minVelocity.y,maxVelocity.y));
			p->radius = (int)random((float)minRadius,(float)maxRadius);
			p->startColor = startColor;
			p->endColor = endColor;
			particles->push_back(p);
		}

		void operator=(ParticleSystem e) { e; }

	public:
		Vector2 position, minPositionOffset, maxPositionOffset, minVelocity, maxVelocity;
		int minRadius, maxRadius;
		int startColor, endColor;
		const unsigned int size;
		float minLifeTime, maxLifeTime;

		ParticleSystem(unsigned int s) : size(s) {
			minLifeTime = maxLifeTime = 10;
			minRadius = maxRadius = 10;
			startColor = endColor = RGB(255,255,255);
			particles = new vector<Particle*>();
		}

		void update(float dt) {
		
			for (unsigned int i = 0; i < particles->size(); i++) {
				Particle* p = (*particles)[i];
				p->update(dt);
			}

			particles->erase(std::remove_if(particles->begin(), particles->end(), 
				[](Particle* p) {
					return p->isDead();
				}), particles->end());

			while (particles->size() <= size) {
				createParticle();
			}

		}

		void draw(EnhancedGraphics& g) {
			for (unsigned int i = 0; i < particles->size(); i++) {
				Particle* p = (*particles)[i];
				p->draw(g);
			}
		}		

	};

}


#endif