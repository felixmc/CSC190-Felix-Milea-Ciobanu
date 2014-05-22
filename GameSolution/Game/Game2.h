#ifndef _GAME2_H_
#define _GAME2_H_

#include "Core.h"

namespace Game2 {
	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;

	void setup();
	bool update(float);
	void draw(Core::Graphics&);
}

#endif