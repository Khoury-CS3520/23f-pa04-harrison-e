#include "Critter.h"
#include "Cell.h"
#include <iostream>

Critter::Critter(Cell& spawn, unsigned health)
: home {&spawn}, curHP {health}, maxHP {health}, moved {false} {}

// picks a random 8n, moves if possible
unsigned Critter::move() {
  vector<shared_ptr<Cell>> habitable;
  for (const auto &cell : home->neighbors8) {
    if (!cell->occupied())
      habitable.push_back(cell);
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  while (!habitable.empty()) {
    // make a random # from 1 - hab.size
    std::uniform_int_distribution<std::mt19937::result_type> distH(0,habitable.size() - 1);
    shared_ptr<Cell> rand = habitable.at(distH(rng));
    velocity_t v_to_d = rand->getPos() - home->getPos();
    Cell& dest = calcDest(*home, v_to_d);

    if (canMove(dest))
      return home->takeCell(dest);
  }
  // pick random habitable as dest
  // if dest is edge & can bounce off dest, move to dest
  // if no available cells, return 0
  return 0;
}

Cell& Critter::calcDest(Cell& src, velocity_t v) {
  coord_t destPos = src.getPos() + v;
  shared_ptr<Cell> dest {nullptr};
  // find dest in neighbors
  for (auto &cell : src.neighbors8) {
    if (cell->getPos() == destPos)
      dest = cell;
  }

  velocity_t v_ = {v.x, v.y};

  switch (dest->cellType()) {
    case HABITABLE:
      return *dest;
    case V_EDGE:
      v_ = {v.x * -1, v.y};
      return calcDest(*dest, v_);
    case H_EDGE:
      v_ = {v.x, v.y * -1};
      return calcDest(*dest, v_);
    case CORNER:
      return src;
  }
}

void Critter::changeHome(Cell* newHome) {
  home = newHome;
}