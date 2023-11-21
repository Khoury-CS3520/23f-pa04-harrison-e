#ifndef PREDORPREY_DOODLEBUG_H
#define PREDORPREY_DOODLEBUG_H
#include "Critter.h"

const unsigned DOODLEBUG_HP = 10;

class Doodlebug : public Critter {
protected:
  unsigned sinceBreeding;

public:
  explicit Doodlebug(Cell& init) : Critter(init, 10), sinceBreeding {0} {}
  ~Doodlebug() override = default;

  unsigned move() override;
  bool canMove(Cell& dest) override;
  unsigned breed() override;
  string toString() override { return "\033[1;31mD"; }

  // identifiers
  bool isDoodle() override { return true; }
  bool canBreed() override { return sinceBreeding >= 10; }
};


#endif //PREDORPREY_DOODLEBUG_H
