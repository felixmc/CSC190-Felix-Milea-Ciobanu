#ifndef _GAME_H_
#define _GAME_H_

#include "Core.h"
#include "ParticleManager.h"
#include "PlayerShip.h"
#include "EnemyManager.h"
#include "Profiler.h"

namespace Game {
	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;
	extern Engine::ParticleManager* particleManager;
	extern PlayerShip * player;
	extern EnemyManager * enemyManager;

	void setup();
	bool update(float);
	void draw(Core::Graphics&);
}

#endif