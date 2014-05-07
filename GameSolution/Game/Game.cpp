#include "Game.h"
#include "PlayerShip.h"
//#include "PositionManager.h"
#include "PositionWrapper.h"
#include <vector>

using Core::Input;

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	std::vector<GameObject>* gameObjects;
	PositionManager* posMan;

	const Vector2 * center;
	PlayerShip * player;

	void setup() {
		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		posMan = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		gameObjects = new std::vector<GameObject>;
		player = new PlayerShip(*center);
		
		gameObjects->push_back(*player);

		player->registerMoveLeft([](){ return Input::IsPressed(Input::KEY_LEFT); });
		player->registerMoveRight([](){ return Input::IsPressed(Input::KEY_RIGHT); });
		player->registerMoveUp([](){ return Input::IsPressed(Input::KEY_UP); });
		player->registerMoveDown([](){ return Input::IsPressed(Input::KEY_DOWN); });
		player->registerStopX([](){ return Input::IsPressed(Input::KEY_RIGHT) && Input::IsPressed(Input::KEY_LEFT); });
		player->registerStopY([](){ return Input::IsPressed(Input::KEY_UP) && Input::IsPressed(Input::KEY_DOWN); });
	}

	bool update(float dt) {
		player->update(dt);
		posMan->reposition(*player);
		//for(std::vector<GameObject>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
		//	
		//	//posMan->reposition(*it);
		//}

		return Input::IsPressed(Input::KEY_ESCAPE);
	}

	void draw(Core::Graphics& g) {
		g.SetColor(RGB(255,255,255));
		player->draw(g);
	}

}