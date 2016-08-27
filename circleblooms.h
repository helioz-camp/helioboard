#ifndef CIRCLEBLOOMS_H
#define CIRCLEBLOOMS_H

#include "game.h"

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
};

class CircleBlooms : public Game
{
public:
	CircleBlooms();
	~CircleBlooms();

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	CircleBloomsState *state;
};

#endif