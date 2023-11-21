#include "Cell.h"
#include "Critter.h"
#include <iostream>

Cell& Cell::operator=(const Cell &that) {
  if (this != &that) {
    this->pos.x = that.pos.x;
    this->pos.y = that.pos.y;
    this->type = that.type;
    this->occupant = nullptr;
  }
  return *this;
}


////// print
string Cell::toString() const {
  const string EMPTY   = "\033[1;30mo";
  const string V_EDGE_ = "\033[1;37m║";
  const string H_EDGE_ = "\033[1;37m═";
  const string CORNER_ = "\033[1;37m╬";
  const string END     = "\033[0m";

  stringstream c;
  switch (type) {
    case HABITABLE:
      if (occupied())
        c << occupant->toString();
      else
        c << EMPTY;
      break;
    case V_EDGE:
      c << V_EDGE_;
      break;
    case H_EDGE:
      c << H_EDGE_;
      break;
    case CORNER:
      c << CORNER_;
      break;
  }

  c << END;
  return c.str();
}


////// spawn
void Cell::spawnQueenAnt() {
  occupant = make_unique<Queen>(*this);
}

void Cell::spawnMatingAnt() {
  occupant = make_unique<Ant>(*this, MATING);
}

void Cell::spawnWorkerAnt() {
  occupant = make_unique<Ant>(*this, WORKER);
}

ant_t Cell::randomAntType() {
  // make a random # from 1-200
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::mt19937::result_type> dist200(1,200);
  auto n = dist200(rng);

  if (n <= 160)
    return WORKER;
    // if n <= 199 (~20%), mate
  else if (n <= 199)
    return MATING;
    // if n == 200 (.5%), queen
  else
    return QUEEN;
}

void Cell::spawnAnt() {
  ant_t t = randomAntType();
  if (t == QUEEN)
    occupant = make_unique<Queen>(*this);
  else
    occupant = make_unique<Ant>(*this, t);
}

void Cell::spawnDoodle() {
  occupant = make_unique<Doodlebug>(*this);
}

////// move
unsigned Cell::tryMoveOccupant() {
  if (occupied() && !occupant->hasMoved()) {
    occupant->toggleMoved();
    return occupant->move();
  }
  return 0;
}

// this takes src's occ
// return 1 if kill occupant, 0 else
unsigned Cell::takeCell(Cell& toTake) {
  int status = 0;
  if (this != &toTake) {
    if (toTake.occupied())
      ++status;
    toTake.occupant = std::move(occupant);
    toTake.occupant->changeHome(&toTake);
  }
  return status;
}


////// kill
unsigned Cell::tryKillOccupant() {
  if (shouldDie()) {
    occupant.reset(nullptr);
    return 1;
  }
  return 0;
}


////// breed
unsigned Cell::tryBreedOccupant() {
  if (occupied())
    occupant->toggleMoved();  // also reset move (so critters dont move twice)
  if (canBreed())
    return occupant->breed();
  return 0;
}