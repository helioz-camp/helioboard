#include <cstdlib>
#include <sstream>
#include "decay.h"

#define STEPS 1000

DecayState::DecayState() {	
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			decayCounts[y][x] = STEPS;
		}
	}
}

Decay::Decay() {
	state = new DecayState();
}

void Decay::render(Frame &frame) {
	setAll(frame, OFF);

	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			int decay = state->decayCounts[y][x];
			if (decay < STEPS) {
				double dist = abs(-1 * x + y) / sqrt(2);
				double hue = 255 * (dist / 17.0);
				int brightness = 255 - (0.25 * decay);
				frame[y][x] = Color(hue, brightness);
			} else {
				frame[y][x] = OFF;
			}
		}
	}

}

void Decay::update(vector<Event> events) {
	if (state->hz("decay", 100)) {
		for (int y = 0; y < LEN; y++) {
			for (int x = 0; x < LEN; x++) {
				state->decayCounts[y][x] = min(STEPS, state->decayCounts[y][x] + 1);
			}
		}
	}

	for (Event &e : events) {
		if (e.on) {
			// Player::drone(e.x, e.y);
			state->decayCounts[e.y][e.x] = 0;
		}
	}
}