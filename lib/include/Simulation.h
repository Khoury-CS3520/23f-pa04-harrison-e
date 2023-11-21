#ifndef PREDORPREY_SIMULATION_H
#define PREDORPREY_SIMULATION_H
#include "Grid.h"

// maximum amount of time the simulation can run for
const Time MAX_RUNTIME = 120; // todo test value
// time in seconds between each iteration of run loop
const unsigned TICK_SPEED = 1;

class Simulation {
protected:
  unsigned antCount;
  unsigned doodleCount;
  Grid grid;

public:
  Simulation(string filename);    // todo
  Simulation(unsigned size, unsigned ants, unsigned doods);
  Simulation(unsigned size, unsigned q, unsigned m, unsigned w, unsigned d);

  void display();
  void run();
};


#endif //PREDORPREY_SIMULATION_H
