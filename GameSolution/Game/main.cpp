#include "Core.h"
#include "Game.h"
#include "Game2.h"

int main() {
	Game2::setup();

	Core::Init("Game Demo", Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Game2::update);
	Core::RegisterDrawFn(Game2::draw);

	Core::GameLoop();

	return 0;
}