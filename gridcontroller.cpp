#include "gridcontroller.h"

using namespace std;

void GridController::render(ControlFrame &frame) {
	setAll(frame, 0);

	for (int i = 0; i < numGames; i++) {
		int offset = i * 2;
		int x = offset % 8;
		int y = 1 + (offset / 8);
		if (i == state->gameIndex) {
			frame[y][x] = state->flashOn ? GREEN : 0;
		} else {
			frame[y][x] = AMBER;
		}
	}
}

void GridController::update(vector<Event> events) {
	for (Event &e : events) {
		if (e.on) {

		}
	}

	if (state->hz("flash", 1)) {
		state->flashOn = !state->flashOn;
	}
}