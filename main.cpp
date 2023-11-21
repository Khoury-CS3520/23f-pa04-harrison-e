#include "Simulation.h"

int main(int argc, char* argv[]) {
  Simulation s = Simulation(20, 2, 4, 10, 2);
  s.run();

  return 0;
}