#ifndef BLOOMS_H
#define BLOOMS_H

#include "game.h"

class Bloom
{
public:
	int x;
	int y;
	int width;
	int colorI;

	vector<pair<int, int>> getPoints();
};

class BloomsState : public State {
public:
	BloomsState();
	~BloomsState() {};

	vector<Bloom> blooms;
	int colorI;
};

class Blooms : public Game
{
public:
	Blooms();
	~Blooms();

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	BloomsState *state;
};

#endif