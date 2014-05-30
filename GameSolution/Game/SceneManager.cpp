#include "SceneManager.h"

SceneManager::SceneManager() {
	scenes = new vector<Scene*>();
}

void SceneManager::add(Scene* scene) {
	scenes->push_back(scene);
}

void SceneManager::update(float dt) {
	for (unsigned int i = 0; i < scenes->size(); i++) {
		scenes->at(i)->update(dt);
	}
}

void SceneManager::draw(Engine::EnhancedGraphics& g) {
	for (unsigned int i = 0; i < scenes->size(); i++) {
		scenes->at(i)->draw(g);
	}
}