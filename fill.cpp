#include <cstdlib>
#include <sstream>
#include "fill.h"

FillState::FillState() {	
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			filled[y][x] = OFF;
		}
	}
}


Fill::Fill() {
	state = new FillState();
}

void Fill::render(Frame &frame) {
	setColor(frame, OFF);

	frame = state->filled;
	if (state->exploding && state->hz("explodingRender", 5)) {
		for (int y = 0; y < LEN; y++) {
			for (int x = 0; x < LEN; x++) {
				setCell(frame, x, y, getColor(rand() % 4));
			}
		}
	}
}

void Fill::update(vector<Event> events) {
	for (Event &e : events) {
		if (e.on && state->filled[e.y][e.x] == OFF) {
			state->filled[e.y][e.x] = getColor(rand() % 4);
			ostringstream ss;
			// char letter = 'a' + (state->textCount++);
			char letter = state->text[state->textCount++];
			ss << "/Users/raphael/Downloads/foobaz/";
			ss << letter;
			ss << ".aif.wav";
			cout << ss.str();
			Player::play(ss.str());
		}
	}

	if (state->explodingCount >= 3) {
		state->exploding = false;
		state->explodingCount = 0;

		for (int y = 0; y < LEN; y++) {
			for (int x = 0; x < LEN; x++) {
				state->filled[y][x] = OFF;
			}
		}
	}

	if (state->exploding && state->hz("explodingSecs", 1)) {
		state->explodingCount++;
	}

	if (state->exploding) {
		return;
	}


	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			if (y == 0 && x == LEN - 1) continue;
			if (!state->filled[y][x]) {
				return;
			}
		}
	}


	int nEvents = events.size();

	if (nEvents > 0 && !events[nEvents - 1].on) {
		Player::play("/Users/raphael/Downloads/foobaz/creepy-distorto-explosion.wav");
		state->exploding = true;
		state->explodingCount = 0;
		state->textCount = 0;
	}


}