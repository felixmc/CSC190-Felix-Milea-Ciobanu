#include "Core.h"
#include "Game.h"
#include "Profiler.h"

int main() {
	Game::setup();

	Core::Init("Game Demo", Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Game::update);
	Core::RegisterDrawFn(Game::draw);

	Core::GameLoop();

	return 0;
}