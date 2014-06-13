#include "Game.h"
#include "DebugMemory.h"

int main() {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	char* a = new char[500];
	a;
	//a[-1] = 0;
	delete a;

	Game::setup();

	Core::Init("Game Demo", Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Game::update);
	Core::RegisterDrawFn(Game::draw);

	Core::GameLoop();

	Game::cleanup();

	return 0;
}