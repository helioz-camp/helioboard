#ifndef RENDERER_H
#define RENDERER_H

#include "RtMidi.h"
#include "game.h"

#define CTRL_CHANGE 176
#define NOTE_ON 144
#define DOUBLE_BUF 176

typedef vector<unsigned char> Message;

struct Board {
	RtMidiOut *out;
	RtMidiIn *in;
	bool ordered = false;
};

class Renderer
{
public:
	Renderer(vector<Board> boards);

	~Renderer();

	void loop();
	void finish();
	void clear();

	Game *game;

	vector<Game *> games;

	void setGame(int gameIndex);

private:
	void renderGame(Frame &gameFrame);
	void renderControl(ControlFrame &controlFrame);
	Event getEvent(Message &m, int boardIndex);
	Event getEventOld(Message &m);

	bool done = false;
	Frame lastFrame;
	ControlFrame lastControlFrame;

	vector<Board> boards;
};

#endif