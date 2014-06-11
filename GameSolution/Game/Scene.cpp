#include "Scene.h"
#include "Matrix3.h"
#include "EngineMath.h"
#include "Particle.h"

const float Scene::STAR_FREQ = 0.00015f;
const float Scene::SHINE_FREQ = 0.01f;

Scene::Scene(float w, float h) : WIDTH(w*1), HEIGHT(h*1), VIEW_WIDTH(w), VIEW_HEIGHT(w) {
	stars = new vector<Star>();
	for (float y = 0; y < HEIGHT; y++) {
		for (float x = 0; x < WIDTH; x++) {
			float prob = (float) (rand()) / (float) (RAND_MAX);
			if (prob < STAR_FREQ) {
				Star star(Vector2(x,y));
				prob = (float) (rand()) / (float) (RAND_MAX);
				if (prob <= .85f) {
					star.color = RGBA(255,255,200,80);
				} else if (prob <= .9f) {
					star.color = RGBA(255,255,0,0);
				} else if (prob <= .95f) {
					star.color = RGBA(0,188,255,0);				
				} else if (prob <= 1.0f) {
					star.color = RGBA(255,50,10,0);
				}
				stars->push_back(star);
			}
		}
	}
}

const int radius = 4;
const float ps = 2 * Engine::Math::PI * radius;
int * Scene::starBitmap = new int[(radius*2)*(radius*2)];

void Scene::init() {
	const int startColor = RGBA(255,255,0,150);
	const int endColor = RGBA(255,128,0,255);

	std::fill(starBitmap, starBitmap + ((radius*2)*(radius*2)), RGBA(0,0,0,255));
	for (int i = 0; i < radius; i++) {
		int color = Engine::Color::interpolate(startColor, endColor, (float)i / radius);
		for (int j = 0; j < ps; j++) {
			Vector2 p = Engine::Matrix3::rotation(j/ps*2*Engine::Math::PI) * Vector2(0,(float)i);
			int x = (int) p.x;
			int y = (int) p.y;
			int coor = ((y+radius) * radius*2) + (x+radius);

			int c = starBitmap[coor];

			float a = (255 - GetAValue(color)) / 255.0f;
			float na = 1 - a;

			starBitmap[coor] = RGBA(
				min((GetRValue(c) * na) + (GetRValue(color) * a),255),
				min((GetGValue(c) * na) + (GetGValue(color) * a),255),
				min((GetBValue(c) * na) + (GetBValue(color) * a),255),
				max(min( 255 - ((255-GetAValue(c)) + (255-GetAValue(color))) ,255), 0)
			);
		}
	}
}

void Scene::update(float dt) {
	offset += velocity * dt;
	for (unsigned int i = 0; i < stars->size(); i++) {
		float prob = (float) (rand()) / (float) (RAND_MAX);
		if (prob < .03f) {
			stars->at(i).state = (stars->at(i).state + 1) % 50;
		}
	}
}

void Scene::draw(Engine::EnhancedGraphics& g) {
	for (unsigned int i = 0; i < stars->size(); i++) {

		Vector2 p = stars->at(i).position + offset;
		while (p.x < 0) { p.x += WIDTH; }
		while (p.y < 0) { p.y += HEIGHT; }
		while (p.x > WIDTH) { p.x -= WIDTH; }
		while (p.y > HEIGHT) { p.y -= HEIGHT; }

		if (stars->at(i).state == 12) {
			g.drawBitmap(Vector2(p.x - radius,p.y - radius), radius*2, radius*2, starBitmap);
		} else {
			/*int radius = 2;
			int dim = (radius*2)+1;
			float* map = Engine::Particle::particleMap(radius);

			for (int yi = 0; yi < dim; yi++) {
				for (int xi = 0; xi < dim; xi++) {
					float mu = map[(yi * dim) + (xi)];
					g.setColor(Engine::Color::interpolate(stars->at(i).color,RGBA(0,0,0,255),mu));
					g.drawPoint(Vector2(xi + p.x - (radius), yi+p.y - (radius)));
				}
			}*/

			g.setColor(stars->at(i).color);
			g.drawPoint(p);		
		}
	}	
}