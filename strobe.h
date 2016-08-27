#ifndef STROBE_H
#define STROBE_H

#include "game.h"

class StrobeState : public State {
public:
	StrobeState();
	~StrobeState() {};

	Color color;
};

class Strobe : public Game
{
public:
	Strobe();
	~Strobe() {}

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	StrobeState *state;
};

#endif