#ifndef RENDERER_H
#define RENDERER_H

#include "RtMidi.h"
#include "Game.h"


#define CTRL_CHANGE 176
#define NOTE_ON 144
#define DOUBLE_BUF 176

typedef vector<unsigned char> Message;

class Renderer
{
public:
	Renderer(RtMidiOut *out, RtMidiIn *in);

	~Renderer();

	void loop();
	void finish();

	Game *game;

private:
	void smartRender(Frame &frame);
	Event getEvent(Message &m);
	void setBuffering(int display, int update);

	bool done = false;
	Frame lastFrame;

	RtMidiOut *out;
	RtMidiIn *in;
};

#endif