#ifndef _POSITION_WRAPPER_H_
#define _POSITION_WRAPPER_H_

#include "PositionManager.h"

namespace Engine {

	class PositionWrapper : public PositionManager {
		const int width, height;
		
		inline void operator= (const PositionWrapper& other) const { other; }
	public:
		PositionWrapper(int w, int h) : width(w), height(h) {}
		void reposition(GameObject& o, float df) {
			df;
			const Shape& shape = o.shape;

			// is offscreen left
			if (o.position.x < 0 - shape.getMostRight()) {
				o.position.x = width - shape.getMostLeft(); 
			} 
			// is offscreen right
			else if (o.position.x > width - shape.getMostLeft()) {
				o.position.x = -shape.getMostRight();
			}

			// is offscreen top
			if (o.position.y < 0 - shape.getMostDown()) {
				o.position.y = height - shape.getMostUp(); 
			} 
			// is offscreen bottom
			else if (o.position.y > height - shape.getMostUp()) {
				o.position.y = -shape.getMostDown();
			}
		}
	};

}

#endif