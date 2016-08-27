#include <math.h>
#include <set>
#include <utility>
#include "circleblooms.h"

CircleBloomsState::CircleBloomsState() {}


CircleBlooms::CircleBlooms() {
	state = new CircleBloomsState();
}

Color CircleBloomsState::randomColor() {
	int test = rand() % 255;
	while (true) {
		if (abs(test - lastColor) > 50) {
			lastColor = test;
			return Color(test, 255);
		} else {
			test = rand() % 255;
		}
	}
}

vector<pair<int, int>> CircleBloom::getPoints() {
	if (radius == 0) {
		return {{originX, originY}};
	}
	vector<pair<int, int>> points;


	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			int xDist = originX - x;
			int yDist = originY - y;
			double dist = sqrt(pow(xDist, 2) + pow(yDist, 2));
			if (dist <= radius) {
				points.push_back({x, y});
			}
		}
	}

	return points;
}

void CircleBlooms::render(Frame &frame) {
	setAll(frame, OFF);

	for (CircleBloom &b: state->blooms) {
		for (auto &p : b.getPoints()) {
			setCell(frame, get<0>(p), get<1>(p), b.color);
		}
	}
}

void CircleBlooms::update(vector<Event> events) {
	if (state->hz("bloom", 8)){
		int doneCount = 0;
		int lastDone = -1;
		for (int i = 0; i < state->blooms.size(); i++) {
			CircleBloom &b = state->blooms[i];
			b.radius = min(25, b.radius + 1);

			if (b.radius >= 25) {
				doneCount++;
				lastDone = i;
			}

		}

		if (doneCount >= 2) {
			vector<CircleBloom> filtered;
			for (int i = 0; i < state->blooms.size(); i++) {
				CircleBloom b = state->blooms[i];
				if (b.radius < 25 || i == lastDone) {
					filtered.push_back(b);
				}
			}
			state->blooms = filtered;
		}
	}

	int nEvents = events.size();
	if (nEvents == 0) return;

	for (Event &e : events) {
		if (e.on) {
			// Player::play("/Users/raphael/Downloads/foobaz/66-per-08.wav");

			CircleBloom b;
			b.originX = e.x;
			b.originY = e.y;
			b.radius = 0;
			b.color = state->randomColor();
			state->blooms.push_back(b);
		}
	}
}
