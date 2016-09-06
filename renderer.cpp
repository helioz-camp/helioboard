#include <algorithm>
#include <cmath>
#include "renderer.h"

using namespace std;

Renderer::Renderer(vector<Board> boards) {
	this->boards = boards;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			lastFrame[y][x] = BAD;
		}
	}

}


void Renderer::clear() {
	Message msg = {240, 0, 32, 41, 2, 24, 14, 0, 247};
	for (int i = 0; i < 4; i++) {
		boards[i].out->sendMessage(&msg);
	}

}


void Renderer::loop() {
	while (!done) {
	  vector<Event> events;
	  vector<Event> controlEvents;
	  for (int i = 0; i < boards.size(); i++) {
		while (true) {
			Message message;
		  	boards[i].in->getMessage(&message);
			int nBytes = message.size();
		  	if (nBytes == 0) break;

			Event e = getEvent(message, i);
			if (i == 4) {
				controlEvents.push_back(e);
			} else {
				events.push_back(e);
			}
		}
	  }

	  Frame frame;
	  game->update(events);
	  game->render(frame);

	  renderGame(frame);

	  sleep(1.0 / 10000.0);
	}
}


void Renderer::finish() {
	done = true;
}

void rotate(int &x, int &y, int boardIndex, bool fromBoard) {
	int rotX = 0;
	int rotY = 0;
	if (fromBoard) {
		switch (boardIndex) {
		case 0:
			rotX = y;
			rotY = 8 - x;
			break;
		case 1:
			rotX = x;
			rotY = y;
			break;
		case 2:
			rotX = 8 - y;
			rotY = x;
			break;
		case 3:
			rotX = 8 - x;
			rotY = 8 - y;
			break;
		}
	} else {
		switch (boardIndex) {
		case 0:
			rotX = 8 - y;
			rotY = x;
			break;
		case 1:
			rotX = x;
			rotY = y;
			break;
		case 2:
			rotX = y;
			rotY = 8 - x;
			break;
		case 3:
			rotX = 8 - x;
			rotY = 8 - y;
			break;
		}
	}
	x = rotX;
	y = rotY;
}

void translate(int &x, int &y, int boardIndex, bool fromBoard) {
	if (fromBoard) {
		switch (boardIndex) {
		case 0:
			break;
		case 1:
			x += BOARD_LEN;
			break;
		case 2:
			x += BOARD_LEN;
			y += BOARD_LEN;
			break;
		case 3:
			y += BOARD_LEN;
			break;
		}
	} else {
		switch (boardIndex) {
		case 0:
			break;
		case 1:
			x -= BOARD_LEN;
			break;
		case 2:
			x -= BOARD_LEN;
			y -= BOARD_LEN;
			break;
		case 3:
			y -= BOARD_LEN;
			break;
		}
	}
}

int getBoardIndex(int x, int y) {
	if (x < BOARD_LEN) {
		return y < BOARD_LEN ? 0 : 3;
	} else {
		return y < BOARD_LEN ? 1 : 2;
	}
}

void Renderer::renderGame(Frame &frame) {
	bool changed = false;
	vector<Message> messages;
	for (int y = 0; y < LEN; y++) {
	  for (int x = 0; x < LEN; x++) {
		if (game->isCorner(x, y)) continue;
		if (lastFrame[y][x] == frame[y][x]) continue;
		changed = true;

		Color c = frame[y][x];

		int boardIndex = getBoardIndex(x, y);
		int boardX = x;
		int boardY = y;
		translate(boardX, boardY, boardIndex, false);
		rotate(boardX, boardY, boardIndex, false);

		unsigned char key;
		if (boardY == 0) {
		  key = 104 + boardX;
		} else {
		  key = (-10 * (boardY - 9)) + boardX + 1;
		}

		unsigned char r = static_cast<unsigned char>(c.r / 4);
		unsigned char g = static_cast<unsigned char>(c.g / 4);
		unsigned char b = static_cast<unsigned char>(c.b / 4);

		// Message msg = {ctrl, key, color};
		Message msg = {240, 0, 32, 41, 2, 24, 11, key, r, g, b, 247};
		boards[boardIndex].out->sendMessage(&msg);
	  }
	}

	lastFrame = frame;
}

void Renderer::renderControl(ControlFrame &controlFrame) {
	for (int y = 0; y < BOARD_LEN; y++) {
	  for (int x = 0; x < BOARD_LEN; x++) {
	    if (game->isCorner(x, y)) continue;
	    if (lastControlFrame[y][x] == controlFrame[y][x]) continue;

	    unsigned char ctrl, key, color;
	    if (y == 0) {
	      ctrl = CTRL_CHANGE;
	      key = 104 + x;
	    } else {
	      ctrl = NOTE_ON;
	      key = (16 * (y - 1)) + x;
	    }

	    color = static_cast<unsigned char>(controlFrame[y][x]);

	    Message msg = {ctrl, key, color};
	    boards[4].out->sendMessage(&msg);
	  }
	}

	lastControlFrame = controlFrame;
}


Event Renderer::getEventOld(Message &message) {
	bool top = message[0] == CTRL_CHANGE;
	int key = message[1];
	int x, y;

	if (top) {
		x = key - 104;
		y = 0;
	} else {
		x = key % 16;
		y = 1 + (key / 16);
	}

	bool on = message[2] != 0;

	return Event(x, y, on);
}

Event Renderer::getEvent(Message &message, int boardIndex) {
	if (boardIndex == 4) {
		return getEventOld(message);
	}
	bool on = message[2] != 0;
	bool top = message[0] == CTRL_CHANGE;
	int key = message[1];
	int x, y;

	if (top) {
		x = key - 104;
		y = 0;
	} else {
		x = (key % 10 - 1);
		y = -1 * ((key / 10) - 9);
	}


	rotate(x, y, boardIndex, true);
	translate(x, y, boardIndex, true);



	return Event(x, y, on);
}

void Renderer::setGame(int gameIndex) {
	game = games[gameIndex];
}




