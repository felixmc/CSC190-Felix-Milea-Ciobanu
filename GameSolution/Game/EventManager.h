#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include "EnhancedGraphics.h"
#include "GameEvent.h"
#include <vector>

using std::vector;

struct EventManager {
	vector<GameEvent*> * events;

	EventManager() {
		events = new vector<GameEvent*>();
	}

	~EventManager() {
		events->erase(std::remove_if(events->begin(), events->end(), 
		[](GameEvent* p) {
			delete p;
			return true;
		}), events->end());

		delete events;
	}

	void add(GameEvent * ps) {
		events->push_back(ps);
	}

	void update(float dt) {
		events->erase(std::remove_if(events->begin(), events->end(), 
			[&](GameEvent* p) {
				if (p->isDead()) {
					delete p;
					return true;
				} else {
					if (p->update(dt)) {
						p->run();
					}

					return false;
				}
		}), events->end());
	}

};

#endif