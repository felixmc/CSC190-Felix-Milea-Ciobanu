#include "Game.h"
//#include "Assert.h"

int main() {

	ASSERTM(true, "something terrible happened!");

	Game::setup();

	Core::Init("Game Demo", Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Game::update);
	Core::RegisterDrawFn(Game::draw);

	Core::GameLoop();

	return 0;
}