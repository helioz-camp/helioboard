#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include <utility>
#include "game.h"
#include "renderer.h"

using namespace std;

class GridControllerState : public State {
public:
	GridControllerState(int numGames);
	~GridControllerState() {};

	int gameIndex = 0;
	bool flashOn = true;
	vector<pair<int, int>> points;
	int numGames = 0;
};

class GridController : public Controller
{
public:
	GridController(int numGames);
	~GridController() {}

	void render(ControlFrame &frame);
	void update(vector<Event> events);

private:
	GridControllerState *state;
};


#endif