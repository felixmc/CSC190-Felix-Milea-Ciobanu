#include "Game.h"
#include "PlayerShip.h"
#include "LerpEnemy.h"
#include "PositionWrapper.h"
#include "PositionBouncer.h"
#include "PositionBoundary.h"
#include "Shape.h"
#include "DrawValue.h"
#include "SceneManager.h"
#include "Recursor.h"
#include "StarScene.h"
#include "InverseFilter.h"
#include <ctime>
#include <cmath>

using Core::Input;

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	ParticleManager* particleManager;

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

	EnhancedGraphics* eg;

	//std::vector<GameObject>* gameObjects;
	PositionManager* posManagers[3];
	int posManIndex = 0;

	const Vector2 * center;
	PlayerShip * player;
	Recursor* rec;
	LerpEnemy * lerper;
	SceneManager * sceneManager;

	//const int sides = 10;
	//const int size = 5;

	//for (int s = size; s > 0; s--) {
	//	Vector2 shape[sides];
	//
	//	for (int i = 0; i < sides; i++) {
	//		float angle = (3.14f * 2 / sides) * i;
	//		shape[i] = Vector2(cos(angle)*s, sin(angle)*s);
	//	}
	//	
	//	circles[size - s] = new GameObject(Vector2(100,150), *SHAPE(shape));
	//	float color = ((255.0f/size) * s);
	//	circles[size - s]->color = RGBA(255,0,0,color);
	//	circles[size - s]->draw(g);
	//	//drawValue(g,20,20*s,s - size);
	//	circles;
	//	g;
	//}

	void drawInstuctions(Core::Graphics& g) {
		int x2 = 20;
		int x = 150;
		int x3 = SCREEN_WIDTH - 280;
		g.SetTextBackgroundMode(Core::Graphics::TEXTBKGMODE::Transparent);

		g.SetColor(Color::WHITE);
		g.DrawString(x, 20, "[ ] [ ] [ ]");
		g.DrawString(x, 40, "[ ] [ ] [ ] [ ]");
		//g.DrawString(x, 60, "[ ]");

		g.SetColor(Color::CYAN);
		g.DrawString(x, 20, " 1   2   3");
		g.DrawString(x, 40, " w   a   s   d");
		//g.DrawString(x, 60, " 4");

		g.SetColor(Color::YELLOW);
		g.DrawString(x2, 20, "Change borders");
		g.DrawString(x2, 40, "Control ship");
		//g.DrawString(x2, 60, "Toggle stars");
		g.DrawString(x2, 120, "Use cursor to aim and left click to fire.");

		//g.SetColor(RGB(128,128,128));
		//g.DrawString(x2, 90, "[stars are experimental and may cause lag]");

		g.SetColor(RGB(255,128,0));
		g.DrawString(x2, 140, "Fire at lerper for explosions.");

		g.SetColor(Color::GREEN);
		Matrix3 trans = Matrix3::translation(player->position)*Matrix3::rotation(player->rotation);
		Engine::drawValue(g, x3, 20, trans);
	}

	void setup() {
		srand((int)time(0));
		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

		eg = new EnhancedGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);

		particleManager = new ParticleManager();

		posManagers[0] = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[1] = new PositionBouncer(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[2] = new PositionBoundary(boundary);

		lerper = new LerpEnemy(*SHAPE(lerpPoints));
		lerper->color = Color::MAGENTA;

		player = new PlayerShip(*center);
		player->color = Color::CYAN2;
		player->gun->color = Color::YELLOW;
		player->registerTarget(lerper);

		Scene::init();

		sceneManager = new SceneManager();
		Scene *scene1 = new Scene((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		scene1->velocity = Vector2(15,10);
		sceneManager->add(scene1);

		Scene *scene2 = new Scene((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		scene2->velocity = Vector2(-5,-15);
		sceneManager->add(scene2);

		rec = new Recursor(Vector2((float)SCREEN_WIDTH - 250, (float)SCREEN_HEIGHT-150.0f), 3);
		rec->color = Color::YELLOW;
		rec->child->color = Color::ORANGE;
		rec->child->child->color = Color::RED;
		rec->child->child->child->color = Color::MAGENTA;

		player->registerRotateLeft([](){ return Input::IsPressed(65); });
		player->registerRotateRight([](){ return Input::IsPressed(68); });
		player->registerMoveUp([](){ return Input::IsPressed(87); });
		player->registerMoveDown([](){ return Input::IsPressed(83); });
		player->registerFire([](){ return Input::IsPressed(Input::BUTTON_LEFT); });
	}

	bool update(float dt) {
		sceneManager->update(dt);

		lerper->update(dt);
		rec->update(dt);
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

		particleManager->update(dt);

		return Input::IsPressed(Input::KEY_ESCAPE);
	}

	InverseFilter filter;

	void draw(Core::Graphics& g) {
		particleManager->draw(*eg);

		sceneManager->draw(*eg);

		rec->draw(*eg);

		player->draw(*eg);
		lerper->draw(*eg);

		eg->draw(g, filter);

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