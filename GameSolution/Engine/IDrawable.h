#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "Core.h"

namespace Engine {

	struct IDrawable {
		void virtual draw(Core::Graphics&) = 0;
		void virtual update(float) {}
	};

}

#endif