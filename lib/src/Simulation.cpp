#include "Simulation.h"
#include <unistd.h>
#include <iostream>

Simulation::Simulation(unsigned int size, unsigned int ants, unsigned int doods)
: grid {Grid(size)}, antCount {ants}, doodleCount {doods}
{
  unsigned antsSpawned {};
  unsigned doodlesSpawned {};

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::mt19937::result_type> distInhabitable(1,size-2);

  // first ant is always a queen
  if (antCount >= 1) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    grid.at(rPos)->spawnQueenAnt();
    antsSpawned++;
  }

  while (antsSpawned < antCount) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    if (!grid.at(rPos)->occupied()) {
      grid.at(rPos)->spawnAnt();
      antsSpawned++;
    }
  }

  while (doodlesSpawned < doodleCount) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    if (!grid.at(rPos)->occupied()) {
      grid.at(rPos)->spawnDoodle();
      doodlesSpawned++;
    }
  }
}

Simulation::Simulation(unsigned int size, unsigned q, unsigned m, unsigned w, unsigned d)
        : grid {Grid(size)}, antCount {q + m + w}, doodleCount {d}
{
  unsigned queensSpawned {};
  unsigned matesSpawned {};
  unsigned workersSpawned {};
  unsigned doodlesSpawned {};

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::mt19937::result_type> distInhabitable(1,size-2);

  while (queensSpawned < q) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    grid.at(rPos)->spawnQueenAnt();
    queensSpawned++;
  }

  while (matesSpawned < m) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    if (!grid.at(rPos)->occupied()) {
      grid.at(rPos)->spawnMatingAnt();
      matesSpawned++;
    }
  }

  while (workersSpawned < w) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    if (!grid.at(rPos)->occupied()) {
      grid.at(rPos)->spawnWorkerAnt();
      workersSpawned++;
    }
  }

  while (doodlesSpawned < doodleCount) {
    coord_t rPos {int (distInhabitable(rng)),
                  int (distInhabitable(rng))};
    if (!grid.at(rPos)->occupied()) {
      grid.at(rPos)->spawnDoodle();
      doodlesSpawned++;
    }
  }
}


void Simulation::display() {
  system("clear");
  std::cout << grid.print();
  std::cout << "ants: " << antCount << '\n';
  std::cout << "doods: " << doodleCount << '\n';
}

void Simulation::run() {
  // show initial world
  display();
  sleep(TICK_SPEED);

  // begin incrementing time steps and updating world
  Time T = 1;
  while (doodleCount > 0 && antCount > 0 && T < MAX_RUNTIME) {
    antCount -= grid.moveDoodlebugs();
    grid.moveAnts();

    doodleCount -= grid.killDoodlebugs();
    antCount -= grid.killAnts();

    doodleCount += grid.breedDoodlebugs();
    antCount += grid.breedAnts();

    display();
    sleep(TICK_SPEED);
    T++;
  }
  system("clear");
  if (!doodleCount) {
    std::cout << "\033[1;33mAnts Win!\033[0m\n";
  } else if (!antCount) {
    std::cout << "\033[1;31mDoodlebugs Win!\033[0m\n";
  } else {
    std::cout << "Draw...\n";
  }
}
