#include <cstdlib>
#include <sstream>
#include "canvas.h"

CanvasState::CanvasState() {	
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			filled[y][x] = OFF;
		}
	}
}

Canvas::Canvas() {
	state = new CanvasState();
}

void Canvas::render(Frame &frame) {
	setAll(frame, OFF);

	frame = state->filled;
}

void Canvas::update(vector<Event> events) {
	for (Event &e : events) {
		if (e.on) {
			if (state->filled[e.y][e.x] == OFF) {
				state->filled[e.y][e.x] = Color(rand() % 255, 255);
			} else {
				state->filled[e.y][e.x] = OFF;
			}
		}
	}
}