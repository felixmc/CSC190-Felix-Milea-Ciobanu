#include "Game.h"
#include "PlayerShip.h"
#include "LerpEnemy.h"
#include "PositionWrapper.h"
#include "PositionBouncer.h"
#include "PositionBoundary.h"
#include "Shape.h"
#include "DrawValue.h"
//#include <vector>

using Core::Input;

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	Vector2 boundaryPoints[] = {
		Vector2(SCREEN_WIDTH/2.f,0),
		Vector2(SCREEN_WIDTH/1.f,SCREEN_HEIGHT/2.f),
		Vector2(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/1.f),
		Vector2(0,SCREEN_HEIGHT/2.f)
	};

	Vector2 lerpPoints[] = {
		Vector2(50), Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100),
		Vector2(SCREEN_WIDTH - 130, SCREEN_HEIGHT/2),
		Vector2(SCREEN_WIDTH - 200, 67), Vector2(90, SCREEN_HEIGHT - 70)
	};

	Shape& boundary = *SHAPE(boundaryPoints);

	//std::vector<GameObject>* gameObjects;
	PositionManager* posManagers[3];
	int posManIndex = 0;

	const Vector2 * center;
	PlayerShip * player;
	LerpEnemy * lerper;

	void drawInstuctions(Core::Graphics& g) {
		g.SetColor(RGB(255,255,255));
		int x = 40;
		g.DrawString(x, 20, "Press 1, 2, or 3 to change borders.");
		g.DrawString(x, 60, "Ship position:");
		Engine::drawValue(g, x, 80, player->position);
	}

	void setup() {
		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		posManagers[0] = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[1] = new PositionBouncer(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[2] = new PositionBoundary(boundary);
		//gameObjects = new std::vector<GameObject>;
		player = new PlayerShip(*center);
		lerper = new LerpEnemy(*SHAPE(lerpPoints));
		
		//gameObjects->push_back(*player);

		player->registerRotateLeft([](){ return Input::IsPressed(Input::KEY_LEFT); });
		player->registerRotateRight([](){ return Input::IsPressed(Input::KEY_RIGHT); });
		player->registerMoveUp([](){ return Input::IsPressed(Input::KEY_UP); });
		player->registerMoveDown([](){ return Input::IsPressed(Input::KEY_DOWN); });
	}

	bool update(float dt) {
		lerper->update(dt);
		player->update(dt);
		posManagers[posManIndex]->reposition(*player, dt);

		int oldPos = posManIndex;

		// TODO: decouple/abstract this
		if(Input::IsPressed(49)) posManIndex = 0; // wrap around
		if(Input::IsPressed(50)) posManIndex = 1; // bounce
		if(Input::IsPressed(51)) posManIndex = 2; // border

		if (oldPos != posManIndex) {
			posManagers[posManIndex]->reset();
		}

		return Input::IsPressed(Input::KEY_ESCAPE);
	}

	void draw(Core::Graphics& g) {
		g.SetColor(RGB(0,255,0));
		player->draw(g);

		g.SetColor(RGB(255,48,0));
		lerper->draw(g);

		// TODO: decouple/abstract this
		if(posManIndex == 2) { // position manager set to border
			g.SetColor(RGB(255,255,0));
			for (int i = 0; i < boundary.size; i++) {
				Vector2 p1 = boundary.points[i];
				Vector2 p2 = boundary.points[(i + 1) % boundary.size];
				g.DrawLine(p1.x, p1.y, p2.x, p2.y);
			}
		}

		drawInstuctions(g);
	}

}