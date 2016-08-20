#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <array>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <unistd.h>
#include <signal.h>
#include "RtMidi.h"
#include "sounds.h"

#define LEN 9

#define OFF 0
#define RED 3
#define ORANGE 23
#define AMBER 51
#define GREEN 48

using namespace std;


typedef array< array<int, LEN>, LEN > Frame;
typedef array< array<bool, LEN>, LEN > BoolFrame;


class State {
public:
	State() {};
	~State() {};

	bool hz(string key, double perSecond);
	
private:
	unordered_map<string, chrono::time_point<chrono::system_clock>> hzRegistry;
};

class Event {
public:
	Event(int x, int y, bool on) {
		this->x = x;
		this->y = y;
		this->on = on;
	}
	int x;
	int y;
	bool on;
};

class Game {
public:
	Game() {};
	~Game() {};

	virtual void update(vector<Event> events) = 0;

	virtual void render(Frame &frame) = 0;

	void setColor(Frame &frame, int color);
	int getColor(int colorI);

	void printFrame(Frame &frame);

	void setCell(Frame &frame, int x, int y, int color);

	bool inBounds(int x, int y);
private:
	State *state;
};

#endif
