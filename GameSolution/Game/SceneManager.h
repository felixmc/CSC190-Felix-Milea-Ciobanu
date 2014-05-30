#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Scene.h"
#include <vector>

class SceneManager {
	vector<Scene*> * scenes;

public:
	SceneManager();
	void add(Scene*);
	void update(float);
	void draw(Engine::EnhancedGraphics&);
};

#endif