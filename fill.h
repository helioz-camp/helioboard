#ifndef FILL_H
#define FILL_H

#include "game.h"

class FillState : public State {
public:
	FillState();
	~FillState() {};

	int colorI = 0;
	Frame filled;
	bool exploding = false;
	int explodingCount = 0;
	string text = "goodshitgoodshitthatssomegoodshitrightthererightthereifidosaysomyselfisaysothatswhatimtalkinga";
	int textCount = 0;
};

class Fill : public Game
{
public:
	Fill();
	~Fill();

	void render(Frame &frame);
	void update(vector<Event> events);

private:
	FillState *state;
};

#endif