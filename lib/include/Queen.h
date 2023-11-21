#ifndef PREDORPREY_QUEEN_H
#define PREDORPREY_QUEEN_H
#include "Ant.h"

const Time PREGNANCY_DURATION = 30;
const Time MATING_COOLDOWN = 15;

class Queen : public Ant {
protected:
  bool pregnant;
  Time sinceBreeding;
  Time sinceMating;

public:
  explicit Queen(Cell& spawn) : Ant(spawn, QUEEN), pregnant {false},
    sinceBreeding {0}, sinceMating {0} {}
  ~Queen() override = default;

  unsigned move() override;
  void mate();
  unsigned breed() override;

  bool canMate() const { return sinceBreeding >= MATING_COOLDOWN; }
  bool canBreed() override { return sinceMating >= PREGNANCY_DURATION; }
};

#endif //PREDORPREY_QUEEN_H
