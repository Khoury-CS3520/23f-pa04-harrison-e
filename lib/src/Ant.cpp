#include "Ant.h"
#include "Cell.h"

unsigned Ant::move() {
  coord_t start = home->getPos();
  Critter::move();
  if (home->getPos() == start)
    curHP--;  // starvation
  return 0;
}

bool Ant::canMove(Cell& dest) {
  return home == &dest || !dest.occupied();
}

string Ant::toString() {
  switch (type) {
    case WORKER:
      return "\033[1;34mx";
    case MATING:
      return "\033[1;36my";
    case QUEEN:
      return "\033[1;33mQ";
  }
}
