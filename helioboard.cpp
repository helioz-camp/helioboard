#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include "RtMidi.h"
#include "blooms.h"
#include "fill.h"
#include "canvas.h"
#include "renderer.h"
#include "gridcontroller.h"

using namespace std;


Renderer *renderer = NULL;

void finish(int sig) {
  renderer->finish();
}

int main() {
  vector<Board> boards;
  vector<Board> orderedBoards;

  RtMidiIn *explorer = new RtMidiIn();

  unsigned int nPorts = explorer->getPortCount();

  if (nPorts == 0) {
    cout << "No ports available!\n";
    return false;
  }

  for (int i = 0; i < nPorts; i++) {
    string name = explorer->getPortName(i);

    if (name.find("Launchpad") != string::npos) {
      Board b;
      b.in = new RtMidiIn();
      b.out = new RtMidiOut();


      b.in->openPort(i);
      b.out->openPort(i);

      b.in->ignoreTypes(false, false, false);

      boards.push_back(b);
    }
  }

  if (boards.size() != 5) {
    cout << "Must connect to exactly 4 boards";
    return false;
  }

  cout << "Touch each square board, clockwise starting from top left. Then, the control board." << endl;


  Message message;
  while (true) {
    bool done = true;

    for (auto &b: boards) {
      if (b.ordered) continue;
      done = false;

      Message message;
      b.in->getMessage(&message);

      if (message.size() > 0) {
        b.ordered = true;
        orderedBoards.push_back(b);
      }

    }

    if (done) break;
  }
 
  renderer = new Renderer(orderedBoards);
  renderer->game = new Blooms();
  renderer->controller = new GridController(2);

  
  cout << "Reading MIDI from port ... quit with Ctrl-C.\n";

  (void) signal(SIGINT, finish);

  renderer->loop();

}