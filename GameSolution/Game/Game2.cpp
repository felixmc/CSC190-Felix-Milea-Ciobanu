#include "Game.h"
#include "Vector2.h"
#include <ctime>
#include <cmath>
#include "EnhancedGraphics.h"

using Core::Input;

using namespace Engine;

namespace Game2 {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	EnhancedGraphics* eg;

	void setup() {
		eg = new EnhancedGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	bool update(float dt) {
		dt;

		return Input::IsPressed(Input::KEY_ESCAPE);
	}

	Vector2 start = Vector2(100,100);
	Vector2 end = start + Vector2(122,95);
	Vector2 dist = Vector2(0, 10);

	void draw(Core::Graphics& g) {


		g.DrawLine(start.x, start.y, end.x, end.y);

		eg->drawLine(start+dist, end+dist);


		eg->draw(g);
	}

}