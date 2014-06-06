#include "Game.h"
#include "PositionWrapper.h"
#include "PositionBouncer.h"
#include "PositionBoundary.h"
#include "Shape.h"
#include "SceneManager.h"
#include "Recursor.h"
#include "StarScene.h"
#include "InverseFilter.h"
#include "DrawValue.h"
#include <ctime>
#include <cmath>

using Core::Input;

Engine::Profiler Engine::Profiler::instance;

#if PROFILING_ON
#define PROFILER_START timer.start();
#define	PROFILER_RECORD(cat) Engine::Profiler::getInstance().addEntry(cat,timer.elapsed());
#else
#define PROFILER_START
#define PROFILER_RECORD(cat)
#endif

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const Vector2 * center;

	Vector2 boundaryPoints[] = {
		Vector2(SCREEN_WIDTH/2.f,0),
		Vector2(SCREEN_WIDTH/1.f,SCREEN_HEIGHT/2.f),
		Vector2(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/1.f),
		Vector2(0,SCREEN_HEIGHT/2.f)
	};

	Shape& boundary = *SHAPE(boundaryPoints);
	PositionManager* posManagers[3];
	int posManIndex = 0;

	EnhancedGraphics* eg;
	Timer timer;

	ParticleManager* particleManager;
	EnemyManager * enemyManager;
	SceneManager * sceneManager;

	PlayerShip * player;
	Recursor* rec;

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

		g.SetColor(Color::CYAN);
		g.DrawString(x, 20, " 1   2   3");
		g.DrawString(x, 40, " w   a   s   d");

		g.SetColor(Color::YELLOW);
		g.DrawString(x2, 20, "Change borders");
		g.DrawString(x2, 40, "Control ship");
		g.DrawString(x2, 70, "Use cursor to aim and left click to fire.");

		g.SetColor(Color::GREEN);
		Matrix3 trans = Matrix3::translation(player->position)*Matrix3::rotation(player->rotation);
		Engine::drawValue(g, x3, 20, trans);
	}

	void setup() {
		srand((int)time(0));

		PROFILER.initialize("profiler");

		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

		eg = new EnhancedGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);

		particleManager = new ParticleManager();

		posManagers[0] = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[1] = new PositionBouncer(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[2] = new PositionBoundary(boundary);

		player = new PlayerShip(*center);
		player->color = Color::CYAN2;
		player->gun->color = Color::YELLOW;

		enemyManager = new EnemyManager(2);

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
		PROFILER.newFrame();


		PROFILER_START
		sceneManager->update(dt);
		rec->update(dt);
		PROFILER_RECORD("scene update")

		PROFILER_START
		player->update(dt);
		posManagers[posManIndex]->reposition(*player, dt);
		PROFILER_RECORD("player update")


		int oldPos = posManIndex;

		PROFILER_START
		float spRand = Math::random(0,1);

		if (spRand < .25) {
			enemyManager->spawnPosition = rec->position;
			enemyManager->baseColor = rec->color;
		} else if (spRand < .5) {
			enemyManager->spawnPosition = rec->child->position;
			enemyManager->baseColor = rec->child->color;
		} else if (spRand < .75) {
			enemyManager->spawnPosition = rec->child->child->position;
			enemyManager->baseColor = rec->child->child->color;
		} else {
			enemyManager->spawnPosition = rec->child->child->child->position;
			enemyManager->baseColor = rec->child->child->child->color;
		}

		enemyManager->update(dt);
		PROFILER_RECORD("enemy update")

		// TODO: decouple/abstract this
		if(Input::IsPressed(49)) posManIndex = 0; // wrap around
		if(Input::IsPressed(50)) posManIndex = 1; // bounce
		if(Input::IsPressed(51)) posManIndex = 2; // border

		if (oldPos != posManIndex) {
			posManagers[posManIndex]->reset();
		}

		PROFILER_START
		particleManager->update(dt);
		PROFILER_RECORD("particles update")

		if (Input::IsPressed(Input::KEY_ESCAPE)) {
			PROFILER.shutdown();
			return true;
		}

		return false;
	}

	InverseFilter filter;

	void draw(Core::Graphics& g) {
		PROFILER_START
		particleManager->draw(*eg);
		PROFILER_RECORD("particles draw")
		
		PROFILER_START
		sceneManager->draw(*eg);
		rec->draw(*eg);
		PROFILER_RECORD("scene draw")

		PROFILER_START
		player->draw(*eg);
		PROFILER_RECORD("player draw")

		PROFILER_START
		enemyManager->draw(*eg);
		PROFILER_RECORD("enemies draw")

		PROFILER_START
		eg->draw(g, filter);
		PROFILER_RECORD("frame draw")

		// TODO: decouple/abstract this
		if(posManIndex == 2) { // position manager set to border
			g.SetColor(RGB(255,255,0));
			for (int i = 0; i < boundary.size; i++) {
				Vector2 p1 = boundary.points[i];
				Vector2 p2 = boundary.points[(i + 1) % boundary.size];
				g.DrawLine(p1.x, p1.y, p2.x, p2.y);
			}
		}

		//g.SetColor(RGB(255,255,255));
		//EnemyMinionShip ems = (EnemyMinionShip) /*enemyManager->enemies->at(0)*/;
		//drawValue(g,100,200,enemyManager->enemies->at(0)->position);

		drawInstuctions(g);
	}

}