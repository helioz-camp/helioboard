#include "blooms.h"

BloomsState::BloomsState() {
	colorI = 0;
}


Blooms::Blooms() {
	state = new BloomsState();
}

vector<pair<int, int>> Bloom::getPoints() {
	vector<pair<int, int>> points;

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < width; x++) {
			if (y == 0 || y == width - 1 || x == 0 || x == width - 1) {
				points.push_back({this->x + x, this->y + y});
			}
		}
	}

	return points;
}

void Blooms::render(Frame &frame) {
	setColor(frame, OFF);

	for (Bloom &b: state->blooms) {
		for (auto &p : b.getPoints()) {
			setCell(frame, get<0>(p), get<1>(p), getColor(b.colorI));
		}
	}

}

void Blooms::update(vector<Event> events) {
	if (state->hz("bloom", 10)){
		int i = 0;
		for (Bloom &b: state->blooms) {
			Player::play("/Users/raphael/Downloads/foobaz/66-rim-03.wav");
			b.x--;
			b.y--;
			b.width += 2;

			int allOver = true;

			for (auto &p : b.getPoints()) {
				int x = get<0>(p);
				int y = get<1>(p);

				if (inBounds(x, y)) {
					allOver = false;
				}
			}

			cout << "PLAYING " << state->blooms.size() << " " << allOver << endl;

			if (allOver) {
				state->blooms.erase(state->blooms.begin() + i);
			} else {
				i++;
			}
		}
	}

	int nEvents = events.size();
	if (nEvents == 0) return;

	for (Event &e : events) {
		if (e.on) {
			Player::play("/Users/raphael/Downloads/foobaz/66-per-08.wav");

			Bloom b;
			b.x = e.x;
			b.y = e.y;
			b.width = 1;
			b.colorI = state->colorI;
			state->colorI = (state->colorI + 1) % 4; 
			state->blooms.push_back(b);
		}
	}
}







