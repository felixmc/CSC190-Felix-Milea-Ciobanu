#ifndef _SCENE_H_
#define _SCENE_H_

#include "GameObject.h"
//#include "Vector2.h"

using namespace Engine;

class Scene : GameObject {
	float width, height;
	
	static const float STAR_FREQ;

public:
	Scene(float,float);
};


#endif