#ifndef _RECURSOR_H_
#define _RECURSOR_H_

#include "GameObject.h"

using namespace Engine;

struct Recursor : GameObject {
	static const float ROT_SPD;

	Recursor* parent, *child;
	int level;

	Recursor(Vector2, int, Recursor*);

	void update(float);
	void draw(Core::Graphics&);
};

#endif