#include "StarScene.h"
#include "EngineMath.h"
#include "Matrix3.h"

const float StarScene::STAR_FREQ = 0.00015f;
const float StarScene::SHINE_FREQ = 0.01f;

StarScene::StarScene(int w, int h) : WIDTH(w*1), HEIGHT(h*1), VIEW_WIDTH(w), VIEW_HEIGHT(w) {
	starCanvas = new bool[WIDTH * HEIGHT];
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			starCanvas[(y*WIDTH) + x] = prob < STAR_FREQ;
		}
	}
}

void StarScene::update(float dt) {
	offset += velocity * dt;
	while (offset.x < 0) { offset.x += WIDTH; }
	while (offset.y < 0) { offset.y += HEIGHT; }
	offset.x = (float)((int)offset.x % WIDTH);
	offset.y = (float)((int)offset.y % HEIGHT);
}

const int radius = 5;

int * StarScene::starBitmap = new int[(radius*2)*(radius*2)];

void StarScene::init() {
	const int startColor = RGBA(255,170,0,150);
	const int endColor = RGBA(255,0,0,255);

	std::fill(starBitmap, starBitmap + ((radius*2)*(radius*2)), RGBA(0,0,0,255));
	for (int i = 0; i < radius; i++) {
		int color = Color::interpolate(startColor, endColor, (float)i / radius);
		float ps = 2 * Engine::Math::PI * radius;
		for (int j = 0; j < ps; j++) {
			Vector2 p = Matrix3::rotation(j/ps*2*Engine::Math::PI) * Vector2(0,(float)i);
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

void StarScene::draw(EnhancedGraphics& g) {
	for (int y = 0; y < VIEW_HEIGHT; y++) {
		for (int x = 0; x < VIEW_WIDTH; x++) {
			int nx = x + (int)offset.x;
			int ny = y + (int)offset.y;
			while (nx < 0) { nx += WIDTH; }
			while (ny < 0) { ny += HEIGHT; }
			nx = nx % WIDTH;
			ny = ny % HEIGHT;

			int c = (ny * WIDTH) + nx;

			if (starCanvas[c]) {
				float prob = (float) (rand()) / (float) (RAND_MAX);
				if (prob < SHINE_FREQ/2.0f) {
					g.drawBitmap(Vector2((float)x - radius,(float)y - radius), radius*2, radius*2, starBitmap);
				} else {
					prob = (float) (rand()) / (float) (RAND_MAX);
					int c = prob < SHINE_FREQ ? 180 + (int)((rand()) / (float) (RAND_MAX) * 75) : 220;
					g.setColor(RGB(c,c,c-50));
					g.drawPoint((Vector2((float)x,(float)y)));
				}
			}
		}
	}
}