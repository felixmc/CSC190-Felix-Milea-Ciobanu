#include "GameEvent.h"
#include "Game.h"

ScoreEvent::ScoreEvent(int s, RunMethod runM) : runMethod(runM), score(s) { }

bool ScoreEvent::update(float dt) {
	dt;
	return Game::score >= score;
}

inline void ScoreEvent::run() {
	GameEvent::run();
	runMethod();
}

TimeEvent::TimeEvent(float time, RunMethod runM) : runMethod(runM), time(time) { }

bool TimeEvent::update(float dt) {
	dt;
	return Game::timer.elapsed() >= time;
}

inline void TimeEvent::run() {
	GameEvent::run();
	runMethod();
}