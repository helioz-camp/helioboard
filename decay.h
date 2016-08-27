#ifndef DECAY_H
#define DECAY_H

#include "game.h"

class DecayState : public State {
public:
	DecayState();
	~DecayState() {};

	array<array<int, LEN>, LEN> decayCounts;
};

class Decay : public Game
{
public:
	Decay();
	~Decay() {}

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	DecayState *state;
};

#endif