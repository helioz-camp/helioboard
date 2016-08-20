#include "game.h"

bool State::hz(string key, double perSecond) {
	auto it = hzRegistry.find(key);
	chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();	
	if (it == hzRegistry.end()) {
		hzRegistry[key] = now;
		return true;
	}
	double elapsed = chrono::duration_cast<chrono::milliseconds>(now - it->second).count();
	if (elapsed > (1000. / perSecond)) {
		hzRegistry[key] = now;
		return true;
	}

	return false;
}

void Game::setColor(Frame &frame, int color) {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			frame[y][x] = color;
		}
	}
}

int Game::getColor(int colorI) {
	int colors[] = {
		RED,
		ORANGE,
		AMBER,
		GREEN
	};

	return colors[colorI];
}

void Game::printFrame(Frame &frame) {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			char c;
			switch (frame[y][x]) {
			case OFF:
				c = 'X';
				break;
			case RED:
				c = 'R';
				break;
			case ORANGE:
				c = 'O';
				break;
			case AMBER:
				c = 'A';
				break;
			case GREEN:
				c = 'G';
				break;
			default:
				c = 'U';
				break;
			}
			cout << c;
		}
		cout << endl;
	}
}

bool Game::inBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < LEN && y < LEN;
}

void Game::setCell(Frame &frame, int x, int y, int color) {
	if (!inBounds(x, y)) return;
	frame[y][x] = color;
}