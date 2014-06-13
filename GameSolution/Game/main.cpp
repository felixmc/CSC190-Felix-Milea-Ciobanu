#include "Game.h"

int main() {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	Game::setup();

	Core::Init("Game Demo", Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Game::update);
	Core::RegisterDrawFn(Game::draw);

	Core::GameLoop();

	Game::cleanup();

	return 0;
}