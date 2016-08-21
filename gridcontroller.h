#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "game.h"

class GridControllerState : public State {
public:
	GridControllerState() {};
	~GridControllerState() {};

	int gameIndex = 0;
	bool flashOn = true;
};

class GridController : public Controller
{
public:
	GridController(int numGames) : Controller(numGames) {
		state = new GridControllerState();
	}
	~GridController() {}

	void render(ControlFrame &frame);
	void update(vector<Event> events);

private:
	GridControllerState *state;
};


#endif