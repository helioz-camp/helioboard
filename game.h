#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <array>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <unistd.h>
#include <signal.h>
#include "RtMidi.h"
#include "sounds.h"
#include "color.h"

using namespace std;


#define LEN 18
#define BOARD_LEN 9

typedef array< array<Color, LEN>, LEN > Frame;
typedef array< array<int, BOARD_LEN>, BOARD_LEN > ControlFrame;
typedef array< array<bool, LEN>, LEN > BoolFrame;


class State {
public:
    State() {};
    ~State() {};

    bool hz(string key, double perSecond);
    
private:
    unordered_map<string, chrono::time_point<chrono::system_clock>> hzRegistry;
};

class Event {
public:
    Event(int x, int y, bool on) {
        this->x = x;
        this->y = y;
        this->on = on;
    }
    int x;
    int y;
    bool on;
};

class Game {
public:
    Game() {};
    ~Game() {};

    virtual void update(vector<Event> events) = 0;

    virtual void render(Frame &frame) = 0;

    void setAll(Frame &frame, Color color);

    void setCell(Frame &frame, int x, int y, Color color);

    bool inBounds(int x, int y);
    bool isCorner(int x, int y);

private:
    State *state;
};

class Renderer;

class Controller {
public:
    Controller(int numGames) {};
    ~Controller() {};

    virtual void update(vector<Event> events) = 0;

    virtual void render(ControlFrame &frame) = 0;

    void setAll(ControlFrame &frame, int color);

    void setCell(ControlFrame &frame, int x, int y, int color);

    bool inBounds(int x, int y);
    bool isCorner(int x, int y);

    Renderer *renderer;

private:
    State *state;
};

#endif
