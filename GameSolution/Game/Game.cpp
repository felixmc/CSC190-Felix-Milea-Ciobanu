#include "Game.h"
#include "PositionWrapper.h"
#include "PositionBouncer.h"
#include "PositionBoundary.h"
#include "Shape.h"
#include "SceneManager.h"
#include "Recursor.h"
#include "InverseFilter.h"
#include "DrawValue.h"
#include "NeutronEnemy.h"
#include "Logger.h"
#include <ctime>
#include <cmath>
#include "Assert.h"

using Core::Input;

Engine::Profiler Engine::Profiler::instance;

#if PROFILING_ON
#define PROFILER_START timer.interval();
#define	PROFILER_RECORD(cat) Engine::Profiler::getInstance().addEntry(cat,timer.intervalElapsed());
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

	GameMenu gameMenu;
	GameState gameState = Setup;
	EnhancedGraphics* eg;
	Timer timer;
	EventManager eventManager;

	ParticleManager * particleManager;
	EnemyManager * enemyManager;
	SceneManager * sceneManager;

	PlayerShip * player;
	Recursor* rec;

	int score = 0;

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

	void setupEvents() {
		eventManager.add(new TimeEvent(1, [](){ enemyManager->add(new NeutronEnemy(player,Vector2(200,200))); }));
	}

	void setup() {
		srand((int)time(0));

		PROFILER_INIT

		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

		eg = new EnhancedGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);

		particleManager = new ParticleManager();

		posManagers[0] = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[1] = new PositionBouncer(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[2] = new PositionBoundary(boundary);

		player = new PlayerShip(*center);
		player->color = Color::CYAN2;
		player->gun->color = Color::YELLOW;

		enemyManager = new EnemyManager();

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

		setupEvents();

		LOG(Info, "Game setup completed");
		gameState = Playing;
		timer.start();
	}

	Interpolation inter(0,360,5,Interpolation::easeInCirc);

	bool update(float dt) {

		PROFILER_FRAME

		inter.update(dt);

		PROFILER_START
		sceneManager->update(dt);
		rec->update(dt);
		PROFILER_RECORD("scene update")

		if (gameState == Playing) {
			PROFILER_START
			player->update(dt);
			posManagers[posManIndex]->reposition(*player, dt);
			PROFILER_RECORD("player update")

			PROFILER_START

			enemyManager->update(dt);
			PROFILER_RECORD("enemy update")
		}

		// TODO: decouple/abstract this
		if(Input::IsPressed(49)) posManIndex = 0; // wrap around
		if(Input::IsPressed(50)) posManIndex = 1; // bounce
		if(Input::IsPressed(51)) posManIndex = 2; // border

		int oldPos = posManIndex;
		if (oldPos != posManIndex) {
			posManagers[posManIndex]->reset();
		}

		if (Input::IsPressed(32)) {
			gameState = gameState == Paused ? Playing : Paused;
		}

		PROFILER_START
			particleManager->update(dt);
		PROFILER_RECORD("particles update")

		if (Input::IsPressed(Input::KEY_ESCAPE)) {
			LOG_SAVE
				PROFILER_SAVE
				return true;
		}

		PROFILER_START
		eventManager.update(dt);
		PROFILER_RECORD("game events")

		return false;
	}

	//static Vector2 enemyShape[] = {
	//	Vector2(0,-2),Vector2(1.2f,0),
	//	Vector2(0,.8f),Vector2(-1.2f,0)
	//};
	//static Vector2 enemyShape[] = {
	//	Vector2(0,-2.5),Vector2(1,0),Vector2(.5f,1.6f),Vector2(.08f,.4f),
	//	Vector2(-.08f,.4f),Vector2(-.5f,1.6f),Vector2(-1,0)
	//};


	static Vector2 eshape[] = {
		Vector2(0,-2.5),Vector2(1,0),Vector2(.5f,1.6f),Vector2(.08f,.4f),
		Vector2(-.08f,.4f),Vector2(-.5f,1.6f),Vector2(-1,0)
	};
	Shape enemyShape = *SHAPE(eshape);
	//Shape enemyShape = *Shape::generate(50,30);
	Vector2 enemyPos(200);

	void draw(Core::Graphics& g) {
		//int c = HSB((int)inter.getValue(),100,100);
		//eg->setColor(c);
		//Matrix3 trans = Matrix3::translation(enemyPos)*Matrix3::rotation(1)*Matrix3::scale(8);
		//for (int i = 0; i < enemyShape.size; i++) {
		//	Vector3 p1 = trans * Vector3(enemyShape.points[i]);
		//	Vector3 p2 = trans * Vector3(enemyShape.points[(i + 1) % enemyShape.size]);
		//	eg->drawLine(p1,p2);
		//}

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
			eg->draw(g);
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

			g.DrawString(SCREEN_WIDTH/2, 20, "score: ");
			drawValue(g, SCREEN_WIDTH/2 + 70, 20, score);

			drawInstuctions(g);
	}

}