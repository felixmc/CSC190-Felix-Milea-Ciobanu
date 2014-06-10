#ifndef _GAME_EVENT_H
#define _GAME_EVENT_H

typedef bool (*UpdateMethod)(float);
typedef void (*RunMethod)();

struct GameEvent {
	bool hasRun;

	GameEvent() {
		hasRun = false;
	}

	virtual void run() {
		hasRun = true;
	}

	virtual bool isDead() {
		return hasRun;
	}

	virtual bool update(float) = 0;

};

struct ScoreEvent : public GameEvent {
	int score;
	RunMethod runMethod;

	ScoreEvent(int,RunMethod);

	bool update(float);
	void run();
};

struct TimeEvent : public GameEvent {
	float time;
	RunMethod runMethod;

	TimeEvent(float,RunMethod);

	bool update(float);
	void run();
};

#endif