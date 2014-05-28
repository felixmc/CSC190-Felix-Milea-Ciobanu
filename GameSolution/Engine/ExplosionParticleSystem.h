#ifndef _EXPLOSION_PARTICLE_SYSTEM_H_
#define _EXPLOSION_PARTICLE_SYSTEM_H_

#include "ParticleSystem.h"

namespace Engine {

	class ExplosionParticleSystem : public ParticleSystem {
	private:
		bool isNew;
		void operator=(ExplosionParticleSystem e) { e; }

	public:
		float delay;

		ExplosionParticleSystem(int s) : ParticleSystem(s) {
			isNew = true;
			delay = 0;
		}

		virtual bool isDead() {
			//return particles->size() == 0;
			return false;
		}

		virtual void update(float dt) {
			if (delay <= 0) {
				if (isNew) {
					while (particles->size() < size) {
						createParticle();
					}
					isNew = false;
				}

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
			} else {
				delay -= dt;
			}
		}
	};

}

#endif