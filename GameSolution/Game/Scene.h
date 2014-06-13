#ifndef _SCENE_H_
#define _SCENE_H_

#include "Star.h"
#include "EnhancedGraphics.h"
#include <vector>

using std::vector;

class Scene {
	static const float STAR_FREQ;
	static const float SHINE_FREQ;
	static int* starBitmap;
	const float WIDTH, HEIGHT, VIEW_WIDTH, VIEW_HEIGHT;
	vector<Star> * stars;
	int color;

	void operator=(Scene e) { e; }

public:
	Vector2 offset, velocity;

	Scene(float,float);
	~Scene();
	void update(float);
	void draw(Engine::EnhancedGraphics&);

	static void init();
};

#endif