#include <math.h>
#include <set>
#include <utility>
#include <algorithm>
#include <random>
#include <ctime>
#include "circleblooms.h"

CircleBloomsState::CircleBloomsState() {
	randomizeColors();
}

void CircleBloomsState::randomizeColors() {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			colors[y][x] = Color(rand() % 255, 255);
		}
	}
}

int myrandom (int i) { return rand()%i;}

void CircleBlooms::assignSounds() {
	srand ( unsigned ( time(0) ) );
	random_shuffle(player->soundz.begin(), player->soundz.end(), myrandom);

	int counter = 0;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			if (isCorner(x, y)) continue;
			state->keyToSound[{x, y}] = player->soundz[counter++];
			if (state->keyToSound[{x, y}] == player->bombSound) {
				printf("BOMB IS AT: %d | %d\n", x, y);
			}
		}
	}
}


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

	if (state->exploding) {
		for (int y = 0; y < LEN; y++) {
			for (int x = 0; x < LEN; x++) {
				frame[y][x] = state->colors[y][x];
			}
		}
	} else {
		for (CircleBloom &b: state->blooms) {
			for (auto &p : b.getPoints()) {
				setCell(frame, get<0>(p), get<1>(p), b.color);
			}
		}
	}
}

void CircleBlooms::update(vector<Event> events) {
	if (!state->assigned) {
		assignSounds();
		state->assigned = true;
	}

	if (state->exploding && state->hz("exploding", 1)) {
		state->explodingSeconds++;
		if (state->explodingSeconds > 2) {
			state->exploding = false;
			state->explodingSeconds = -1;
		}
	}

	if (state->exploding) {
		if (state->hz("flash", 10)) {
			state->randomizeColors();
		}
		return;
	}

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
			string sound = state->keyToSound[{e.x, e.y}];

			player->play(sound);

			if (sound == player->bombSound) {
				state->blooms.clear();
				state->exploding = true;
				assignSounds();
			} else {
				CircleBloom b;
				b.originX = e.x;
				b.originY = e.y;
				b.radius = 0;
				b.color = state->randomColor();
				state->blooms.push_back(b);
			}
		}
	}
}

/*
#ifndef CELLSTROBE_H
#define CELLSTROBE_H

#include "game.h"

class CellStrobeState : public State {
public:
	CellStrobeState();
	~CellStrobeState() {};

	Frame colors;
};

class CellStrobe : public Game
{
public:
	CellStrobe();
	~CellStrobe() {}

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	CellStrobeState *state;
};

#endif

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
*/
