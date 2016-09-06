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

void Game::setAll(Frame &frame, Color color) {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			frame[y][x] = color;
		}
	}
}

bool Game::inBounds(int x, int y) {
	return x >= 0 && y >= 0 && x < LEN && y < LEN;
}

bool Game::isCorner(int x, int y) {
	return (x == 0 || x == LEN - 1) && (y == 0 || y == LEN - 1);
}

void Game::setCell(Frame &frame, int x, int y, Color color) {
	if (!inBounds(x, y)) return;
	frame[y][x] = color;
}