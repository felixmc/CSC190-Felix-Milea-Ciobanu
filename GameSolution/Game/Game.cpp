#include "Game.h"
#include "PlayerShip.h"
#include "LerpEnemy.h"
#include "PositionWrapper.h"
#include "PositionBouncer.h"
#include "PositionBoundary.h"
#include "Shape.h"
#include "DrawValue.h"
#include "Recursor.h"
#include "ParticleSystem.h"
#include <ctime>
#include <cmath>

using Core::Input;

namespace Game {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const float STAR_FREQ = 0.0005f;
	const float SHINE_FREQ = 0.01f;

	bool stars[SCREEN_HEIGHT][SCREEN_WIDTH];

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
	ParticleSystem * ps;

	void drawCircle(EnhancedGraphics& g, Vector2 center) {
		g;

		const int radius = 13;
		//const Vector2 center(300,300);
		const float PI = 3.14159265358979323846f;

		for (int i = 0; i < radius; i++) {
			int a = 230;//min(100+(int)(((float)i/radius)*255),255);
			g.setColor(RGBA(0,255-min(0+(int)(((float)i/radius)*255),255),255,a));
			float ps = 2 * PI * radius;
			for (int j = 0; j < ps; j++) {
				Vector2 p = Matrix3::rotation(j/ps*2*PI) * Vector2(0,(float)i);
				g.drawPoint(center+p);
			}
		}


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

	}

	void setupStars() {
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				float prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				stars[y][x] = prob < STAR_FREQ;
			}
		}
	}

	void drawStars(EnhancedGraphics& g) {
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				if (stars[y][x]) {
					float prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					if (prob < SHINE_FREQ/4.0f) {
						g.setColor(RGB(255,255,0));
						g.drawLine(Vector2((float)x-1,(float)y-1),Vector2((float)x+2,(float)y+2));
						g.drawLine(Vector2((float)x-1,(float)y+2),Vector2((float)x+2,(float)y-1));
					} else {
						prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						int c = prob < SHINE_FREQ ? 220 + (rand() * 35) : 255;
						g.setColor(RGB(c,c,c));
						g.drawLine(Vector2((float)x,(float)y),Vector2((float)x+1,(float)y+1));
					}
				}
			}
		}
	}

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
		srand (static_cast <unsigned> (time(0)));

		ps = new ParticleSystem(40);
		ps->position = Vector2(200,200);
		ps->minPositionOffset = Vector2(-5,-5);
		ps->maxPositionOffset = Vector2(5,5);
		ps->minVelocity = Vector2(-3,-3);
		ps->maxVelocity = Vector2(3,3);
		ps->minLifeTime = 1;
		ps->maxLifeTime  = 2;
		ps->minRadius = 8;
		ps->maxRadius = 15;
		ps->startColor = RGBA(0,255,255,230);
		ps->endColor = RGBA(0,0,255,230);

		eg = new EnhancedGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);

		center = new Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		posManagers[0] = new PositionWrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[1] = new PositionBouncer(SCREEN_WIDTH, SCREEN_HEIGHT);
		posManagers[2] = new PositionBoundary(boundary);

		player = new PlayerShip(*center);
		player->color = RGBA(0,200,220,220);
		player->gun->color = Color::YELLOW;

		lerper = new LerpEnemy(*SHAPE(lerpPoints));
		lerper->color = Color::MAGENTA;

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

		setupStars();
	}

	bool update(float dt) {
		lerper->update(dt);
		rec->update(dt);
		player->update(dt);
		posManagers[posManIndex]->reposition(*player, dt);

		ps->update(dt);

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
		drawStars(*eg);
		rec->draw(*eg);

		//for(int i = 0; i < 30; i++) {
		//	drawCircle(*eg, Vector2(300.0f+(rand()%35),300.0f+(rand()%35)));
		//}

		ps->draw(*eg);

		player->draw(*eg);
		lerper->draw(*eg);

		for (int i = 0; i < 40; i++) {
			eg->setColor(RGBA(255,255,0,255-i*(255/40)));
			eg->drawLine(Vector2(615.0f+i, 350),Vector2(615.0f+i,400));
		}

		for (int i = 0; i < 40; i++) {
			eg->setColor(RGBA(255,0,0,(i + 1)*(255/40)));
			eg->drawLine(Vector2(635.0f+i, 370),Vector2(635.0f+i,420));
		}

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

		eg->draw(g);

		g;
	}

}