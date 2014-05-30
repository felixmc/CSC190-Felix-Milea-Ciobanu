#ifndef _STAR_H_
#define _STAR_H_

#include "Vector2.h"
#include "Core.h"

using Engine::Vector2;

struct Star {
	Vector2 position;
	int state;
	int color;

	Star(Vector2 pos) : position(pos) {
		state = 0;
		color = RGB(255,255,255);
	}
};

#endif