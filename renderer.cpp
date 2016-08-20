#include <algorithm>
#include "renderer.h"

Renderer::Renderer(RtMidiOut *out, RtMidiIn *in) {
	this->out = out;
	this->in = in;

	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			lastFrame[y][x] = -1;
		}
	}
}


void Renderer::loop() {
	while (!done) {
	  vector<Event> events;
	  while (true) {
	  	Message message;
	    double stamp = in->getMessage(&message);
	    int nBytes = message.size();
	    if (nBytes == 0) break;

	    Event e = getEvent(message);
	    events.push_back(e);
	  }

	  Frame frame;
	  game->update(events);
	  game->render(frame);

	  smartRender(frame);

	  sleep(1.0 / 1000.0);
	}
}

void Renderer::setBuffering(int display, int update) {
  int val = (1 << 5) + (update << 2) + display;

  Message msg = {DOUBLE_BUF, 0, static_cast<unsigned char>(val)};
  out->sendMessage(&msg);
}

void Renderer::finish() {
	done = true;
}

void Renderer::smartRender(Frame &frame) {
	bool changed = false;
	vector<Message> messages;
	for (int y = 0; y < LEN; y++) {
	  for (int x = 0; x < LEN; x++) {
	    if (y == 0 && x == 8) continue;
	    if (lastFrame[y][x] == frame[y][x]) continue;
	    changed = true;

	    unsigned char ctrl, key, color;
	    if (y == 0) {
	      ctrl = CTRL_CHANGE;
	      key = 104 + x;
	    } else {
	      ctrl = NOTE_ON;
	      key = (16 * (y - 1)) + x;
	    }

	    color = static_cast<unsigned char>(frame[y][x]);

	    Message msg = {ctrl, key, color};
	    messages.push_back(msg);
	  }
	}

	random_shuffle(messages.begin(), messages.end());

	for (auto msg: messages) {
	  out->sendMessage(&msg);
	}

	lastFrame = frame;
}

Event Renderer::getEvent(Message &message) {
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
