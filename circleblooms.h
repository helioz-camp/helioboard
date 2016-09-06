#ifndef CIRCLEBLOOMS_H
#define CIRCLEBLOOMS_H

#include "game.h"
#include <map>

class CircleBloom
{
public:
	int originX;
	int originY;
	int radius;
	Color color;

	vector<pair<int, int>> getPoints();
};

class CircleBloomsState : public State {
public:
	CircleBloomsState();
	~CircleBloomsState() {};

	vector<CircleBloom> blooms;
	int lastColor = -500;

	Color randomColor();

	map<pair<int, int>, string> keyToSound;
	bool assigned = false;

	Frame colors;
	bool exploding = false;
	int explodingSeconds = -1;
	void randomizeColors();

};

class CircleBlooms : public Game
{
public:
	CircleBlooms();
	~CircleBlooms();

	void render(Frame &frame);
	void update(vector<Event> events);
	void assignSounds();

private:
	CircleBloomsState *state;
};

#endif