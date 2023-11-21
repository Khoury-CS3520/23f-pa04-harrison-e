#ifndef PREDORPREY_SIMULATION_H
#define PREDORPREY_SIMULATION_H
#include "Grid.h"

// maximum amount of time the simulation can run for
const Time MAX_RUNTIME = 300;
// time in seconds between each iteration of run loop
const unsigned TICK_SPEED = 1;
// do we clear the screen after each tick?
const bool CLEAR_SCREEN = true;

class Simulation {
protected:
  unsigned antCount;
  unsigned doodleCount;
  Grid grid;

public:
  Simulation(unsigned size, unsigned ants, unsigned doods);
  Simulation(unsigned size, unsigned q, unsigned m, unsigned w, unsigned d);

  void display();
  void run();
};


#endif //PREDORPREY_SIMULATION_H
