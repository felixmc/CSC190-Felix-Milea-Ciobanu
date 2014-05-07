#ifndef _GAME_H_
#define _GAME_H_

#include "Core.h"

namespace Game {
	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;

	void setup();
	bool update(float);
	void draw(Core::Graphics&);
}

#endif