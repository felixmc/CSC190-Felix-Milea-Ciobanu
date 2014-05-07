#include "Game.h"
#include "PlayerShip.h"

using Core::Input;

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Vector2 * pos;
	PlayerShip * player;

	void setup() {
		pos = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		player = new PlayerShip(*pos);

		player->registerMoveLeft([](){ return Input::IsPressed(Input::KEY_LEFT); });
		player->registerMoveRight([](){ return Input::IsPressed(Input::KEY_RIGHT); });
		player->registerMoveUp([](){ return Input::IsPressed(Input::KEY_UP); });
		player->registerMoveDown([](){ return Input::IsPressed(Input::KEY_DOWN); });
		player->registerStopX([](){ return Input::IsPressed(Input::KEY_RIGHT) && Input::IsPressed(Input::KEY_LEFT); });
		player->registerStopY([](){ return Input::IsPressed(Input::KEY_UP) && Input::IsPressed(Input::KEY_DOWN); });
	}

	bool update(float dt) {
		dt;
		player->update(dt);
		return Input::IsPressed(Input::KEY_ESCAPE);
	}

	void draw(Core::Graphics& g) {
		g.SetColor(RGB(255,255,255));
		player->draw(g);
	}

}