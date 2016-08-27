#ifndef CELLSTROBE_H
#define CELLSTROBE_H

#include "game.h"

class CellStrobeState : public State {
public:
	CellStrobeState();
	~CellStrobeState() {};

	Frame colors;
};

class CellStrobe : public Game
{
public:
	CellStrobe();
	~CellStrobe() {}

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	CellStrobeState *state;
};

#endif