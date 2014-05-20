#ifndef _RECURSOR_H_
#define _RECURSOR_H_

#include "GameObject.h"

using namespace Engine;

struct Recursor : GameObject {
	static const float ROT_SPD;

	Recursor* parent, *child;
	Vector2 oldPos;

	Recursor(Vector2, int);

	void update(float);
	void draw(Core::Graphics&);
	int getLevel();
	Vector2 getDynamicPosition();
};

#endif