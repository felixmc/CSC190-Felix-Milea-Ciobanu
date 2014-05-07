#ifndef _POSITION_MANAGER_H_
#define _POSITION_MANAGER_H_

#include "GameObject.h"

namespace Engine {

	class PositionManager {

		inline void operator= (const PositionManager& other) const { other; }
	
	public:
		virtual void reposition(GameObject&) = 0;
	};

}

#endif