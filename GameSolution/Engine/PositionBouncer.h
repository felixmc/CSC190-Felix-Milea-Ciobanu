#ifndef _POSITION_BOUNCER_H_
#define _POSITION_BOUNCER_H_

#include "PositionManager.h"
#include <cmath>

namespace Engine {

	class PositionBouncer : public PositionManager {
		const int width, height;
		
		inline void operator= (const PositionBouncer& other) const { other; }
	public:
		PositionBouncer(int w, int h) : width(w), height(h) {}
		void reposition(GameObject& o, float df) {
			df;
			const Shape& shape = o.shape;

			// going offscreen left
			if (o.position.x < 0 - shape.getMostLeft()) {
				o.position.x = 0 - shape.getMostLeft();
				o.velocity.x *= -1;
			}
			// going offscreen right
			else if (o.position.x > width - shape.getMostRight()) {
				o.position.x = width - shape.getMostRight();
				o.velocity.x *= -1;
			}

			// going offscreen top
			if (o.position.y < 0 - shape.getMostUp()) {
				o.position.y = 0 - shape.getMostUp();
				o.velocity.y *= -1; 
			} 
			// going offscreen bottom
			else if (o.position.y > height - shape.getMostDown()) {
				o.position.y = height - shape.getMostDown();
				o.velocity.y *= -1;
			}
		}
	};

}

#endif