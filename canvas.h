#ifndef CANVAS_H
#define CANVAS_H

#include "game.h"

class CanvasState : public State {
public:
	CanvasState();
	~CanvasState() {};

	Frame filled;
};

class Canvas : public Game
{
public:
	Canvas();
	~Canvas() {}

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	CanvasState *state;
};

#endif