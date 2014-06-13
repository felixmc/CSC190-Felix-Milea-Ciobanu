#ifndef _GAME_H_
#define _GAME_H_

#include "Core.h"
#include "ParticleManager.h"
#include "PlayerShip.h"
#include "EnemyManager.h"
#include "Profiler.h"
#include "GameMenu.h"
#include "EventManager.h"

namespace Game {
	enum GameState { Loading, Playing, Paused, Ended };

	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;
	extern Engine::ParticleManager particleManager;
	extern PlayerShip player;
	extern EnemyManager enemyManager;
	extern Timer timer;
	extern GameState gameState;
	extern GameMenu gameMenu;
	extern EventManager eventManager;
	extern int score;

	void setup();
	void cleanup();
	bool update(float);
	void draw(Core::Graphics&);
}

#endif