#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include "RtMidi.h"
#include "circleblooms.h"
#include "renderer.h"

using namespace std;


Renderer *renderer = NULL;

void finish(int sig) {
  renderer->finish();
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage is: ./helioboard [audiomixserver address] [full path to folder containing sounds]" << endl;
    return 0;
  }

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

    cout << name << endl;

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

  if (boards.size() != 4) {
    cout << "Must connect to exactly 4 boards" << endl;
    return false;
  }

  cout << "Touch each square board clockwise." << endl;


  Message message;
  while (true) {
    bool done = true;

    for (auto &b: boards) {
      if (b.ordered) continue;
      done = false;

      Message message;
      b.in->getMessage(&message);

      if (message.size() > 0) {
        cout << "DONE" << endl;
        b.ordered = true;
        orderedBoards.push_back(b);
      }

    }

    if (done) break;
  }
 
  renderer = new Renderer(orderedBoards);

  Game *blooms = new CircleBlooms();

  renderer->game = blooms;

  blooms->player = new Player(argv[1], argv[2]);

  
  cout << "Reading MIDI from port ... quit with Ctrl-C.\n";

  (void) signal(SIGINT, finish);

  renderer->loop();

}