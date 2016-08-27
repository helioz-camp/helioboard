#include <cstdlib>
#include <sstream>
#include "strobe.h"

StrobeState::StrobeState() {
}

Strobe::Strobe() {
	state = new StrobeState();
}

void Strobe::render(Frame &frame) {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			frame[y][x] = state->color;
		}
	}
}

void Strobe::update(vector<Event> events) {
	if (state->hz("flash", 10)) {
		state->color = Color(rand() % 255, 255);
	}
}