#include <cstdlib>
#include <sstream>
#include "cellstrobe.h"

CellStrobeState::CellStrobeState() {
}

CellStrobe::CellStrobe() {
	state = new CellStrobeState();
}

void CellStrobe::render(Frame &frame) {
	setAll(frame, OFF);

	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			frame[y][x] = state->colors[y][x];
		}
	}
}

void CellStrobe::update(vector<Event> events) {
	if (state->hz("flash", 10)) {
		for (int y = 0; y < LEN; y++) {
			for (int x = 0; x < LEN; x++) {
				state->colors[y][x] = Color(rand() % 255, 255);
			}
		}
	}
}