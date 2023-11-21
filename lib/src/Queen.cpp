#include "Queen.h"
#include "Cell.h"

unsigned Queen::move() {
  if (pregnant) {
    sinceBreeding++;
    curHP--;
  } else {
    Ant::move();
    curHP++;  // queens dont starve
    if (canMate()) {
      for (const auto &cell : home->neighbors8) {
        if (cell->hasMating())
          mate();
      }
    } else {
      sinceMating++;
    }
  }
  return 0;
}

void Queen::mate() {
  pregnant = true;
  sinceMating = 0;
}

unsigned Queen::breed() {
  // TODO spawn new dudes
  vector<shared_ptr<Cell>> spawnable;
  for (const auto &cell : home->neighbors16) {
    if (!cell->occupied() && cell->cellType() == HABITABLE)
      spawnable.push_back(cell);
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  unsigned toSpawn = std::min(10, (int) spawnable.size());
  unsigned spawned = 0;

  while (spawned < toSpawn) {
    std::uniform_int_distribution<std::mt19937::result_type> distEgg(0,spawnable.size() - 1);
    shared_ptr<Cell> rand = spawnable.at(distEgg(rng));
    rand->spawnAnt();
    ++spawned;
  }

  pregnant = false;
  sinceBreeding = 0;
  sinceMating = 0;
  curHP = maxHP;
  return spawned;
}
