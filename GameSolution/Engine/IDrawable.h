#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "EnhancedGraphics.h"

namespace Engine {

	struct IDrawable {
		void virtual draw(EnhancedGraphics&) = 0;
		void virtual update(float) {}
	};

}

#endif