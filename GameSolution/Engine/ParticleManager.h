#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "DebugMemory.h"
#include "ParticleSystem.h"

namespace Engine {

	class ParticleManager {
		vector<ParticleSystem*> particles;

	public:
		ParticleManager() {
			particles = vector<ParticleSystem*>();
		}

		~ParticleManager() {
			particles.erase(std::remove_if(particles.begin(), particles.end(), 
			[](ParticleSystem* p) {
				delete p;
				return true;
			}), particles.end());
		}

		void add(ParticleSystem * ps) {
			particles.push_back(ps);
		}

		void update(float dt) {
			particles.erase(std::remove_if(particles.begin(), particles.end(), 
				[&](ParticleSystem* p) {
					if (p->isDead()) {
						delete p;
						return true;
					} else {
						p->update(dt);
						return false;
					}
				}), particles.end());
		}

		void draw(EnhancedGraphics& g) {
			for (unsigned int i = 0; i < particles.size(); i++) {
				ParticleSystem* p = particles[i];
				p->draw(g);
			}		
		}
	};

}

#endif