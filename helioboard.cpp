#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include "RtMidi.h"
#include "blooms.h"
#include "fill.h"
#include "renderer.h"


using namespace std;

bool init(RtMidi *midi) {
  bool found = false;
  unsigned int nPorts = midi->getPortCount();
  if (nPorts == 0) {
    cout << "No ports available!\n";
    Player::play("/Users/raphael/Downloads/foobaz/66-rim-03.wav");
    return false;
  }
  for (int i = 0; i < nPorts; i++) {
    string name = midi->getPortName(i);
    if (name == "Launchpad") {
      midi->openPort( 0 );
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "Launchpad not found!\n";
    return false;
  }
  return true;

}

Renderer *renderer = NULL;

void finish(int sig) {
  renderer->finish();
}

int main() {
  RtMidiIn *in = new RtMidiIn();
  RtMidiOut *out = new RtMidiOut();

  renderer = new Renderer(out, in);
  renderer->game = new Blooms();

  if (!init(in) || !init(out)) {
    goto cleanup;
  }

  in->ignoreTypes(false, false, false);
  
  cout << "Reading MIDI from port ... quit with Ctrl-C.\n";

  (void) signal(SIGINT, finish);

  renderer->loop();

 cleanup:
  delete in;
  delete out;
  return 0;
}