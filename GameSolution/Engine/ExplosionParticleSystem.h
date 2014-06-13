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
		bool radial;

		ExplosionParticleSystem(int s) : ParticleSystem(s) {
			isNew = true;
			delay = 0;
			radial = false;
		}

		virtual bool isDead() {
			//return particles->size() == 0;
			return false;
		}

		virtual void update(float dt) {
			if (delay <= 0) {
				if (isNew) {
					while (particles.size() < size) {
						Particle * p = createParticle();
						if (radial) {
							p->velocity = ( Matrix3::rotation(Math::random(0, 2 * Math::PI)) * p->velocity );
						} else {
						
						}	
					}
					isNew = false;
				}

				for (unsigned int i = 0; i < particles.size(); i++) {
					Particle* p = particles[i];
					p->update(dt);
					p->radius = (int)(p->radius + (sizeDelta * dt));
				}

				particles.erase(std::remove_if(particles.begin(), particles.end(), 
					[](Particle* p) {
						if (p->isDead()) {
							delete p;
							return true;
						}

						return false;
					}), particles.end());
			} else {
				delay -= dt;
			}
		}
	};

}

#endif