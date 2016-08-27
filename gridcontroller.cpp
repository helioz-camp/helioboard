#include "gridcontroller.h"


GridControllerState::GridControllerState(int numGames) {
	this->numGames = numGames;

	for (int i = 0; i < numGames; i++) {
		int offset = i * 2;
		int x = offset % 8;
		int y = 1 + 2 * (offset / 8);
		points.push_back({x, y});
	}
}

GridController::GridController(int numGames) : Controller(numGames) {
		state = new GridControllerState(numGames);
}

void GridController::render(ControlFrame &frame) {
	setAll(frame, 0);

	for (int i = 0; i < state->numGames; i++) {
		int x = get<0>(state->points[i]);
		int y = get<1>(state->points[i]);
		if (i == state->gameIndex) {
			frame[y][x] = state->flashOn ? GREEN : 0;
		} else {
			frame[y][x] = AMBER;
		}
	}
}

void GridController::update(vector<Event> events) {
	bool changed = false;
	for (Event &e : events) {
		if (e.on) {
			for (int i = 0; i < state->numGames; i++) {
				auto p = state->points[i];
				if (e.x == get<0>(p) && e.y == get<1>(p)) {
					state->gameIndex = i;
					changed = true;
				}
			}
		}
	}

	if (state->hz("flash", 2)) {
			state->flashOn = !state->flashOn;
	}

	if (changed) {
		renderer->setGame(state->gameIndex);
	}

	// if (changed) {
	// 	state->flashOn = true;
	// } else if (state->hz("flash", 2)) {
	// 	state->flashOn = !state->flashOn;
	// }
}