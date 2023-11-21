#include "Doodlebug.h"
#include "Cell.h"

unsigned Doodlebug::move() {
  // check for edible neighbors
  for (auto &cell : home->neighbors8) {
    if (cell->hasAnt()) {
      curHP = maxHP;
      return home->takeCell(*cell);
    }
  }
  curHP--;
  sinceBreeding++;
  return Critter::move();
}

bool Doodlebug::canMove(Cell& dest) {
  return home == &dest || !dest.occupied() || dest.hasAnt();
}

unsigned Doodlebug::breed() {
  vector<shared_ptr<Cell>> spawnable;
  for (const auto &cell : home->neighbors8) {
    if (!cell->occupied() && cell->cellType() == HABITABLE)
      spawnable.push_back(cell);
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  unsigned toSpawn = std::min(2, (int) spawnable.size());
  unsigned spawned = 0;

  while (spawned < toSpawn) {
    std::uniform_int_distribution<std::mt19937::result_type> distEgg(0,spawnable.size() - 1);
    shared_ptr<Cell> rand = spawnable.at(distEgg(rng));
    rand->spawnDoodle();
    ++spawned;
  }

  sinceBreeding = 0;
  return spawned;
}