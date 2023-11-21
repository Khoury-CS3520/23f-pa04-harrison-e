#include "Simulation.h"

int main(int argc, char* argv[]) {
  Simulation s = Simulation(20, 20, 4);
  s.run();

  return 0;
}