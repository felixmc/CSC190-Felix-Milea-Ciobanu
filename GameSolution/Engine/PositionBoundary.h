#ifndef _POSITION_BOUNDARY_H_
#define _POSITION_BOUNDARY_H_

#include "Core.h"
#include "PositionManager.h"
#include "Shape.h"
#include <string>

namespace Engine {

	class PositionBoundary : public PositionManager {
		const Shape shape;
		inline void operator= (const PositionBoundary& other) const { other; }
	public:
		PositionBoundary(Shape& shp) : shape(shp) {}
		void reposition(GameObject& o, float df) {
			bool isIn = true;
			for (int i = 0; i < shape.size; i++) {
				Vector2 p1 = shape.points[i];
				Vector2 p2 = shape.points[(i + 1) % shape.size];
				Vector2 norm = (p2 - p1).perpCCW().normalize();
				float dp = (o.position - p1).dot(norm);
				if (dp <= 0 && !isReset) {
					o.position -= (o.velocity * df);
					o.velocity -= 2 * (o.velocity.dot(norm)) * norm;
				}
				
				isIn = isIn && (dp > 0 && isReset);
			}

			if (isIn) {
				isReset = false;
			}
		}

	};

}

#endif