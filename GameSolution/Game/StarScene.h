#ifndef _STAR_SCENE_H_
#define _STAR_SCENE_H_

#include "EnhancedGraphics.h"
#include "Vector2.h"
#include "Game.h"

using namespace Engine;

struct StarScene {
	Vector2 offset, velocity;

	StarScene(int,int);

	void update(float);
	void draw(EnhancedGraphics&);

	static void init();

private:
	static const float STAR_FREQ;
	static const float SHINE_FREQ;
	static int* starBitmap;
	const int WIDTH, HEIGHT, VIEW_WIDTH, VIEW_HEIGHT;
	int color;
	bool * starCanvas;

	void operator=(StarScene e) { e; }
	int coord(Vector2);
	int coord(int,int);
};

#endif