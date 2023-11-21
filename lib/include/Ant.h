#ifndef PREDORPREY_ANT_H
#define PREDORPREY_ANT_H
#include "Critter.h"

enum AntType {
  WORKER,
  MATING,
  QUEEN
};
using ant_t = AntType;

class Ant : public Critter {
protected:
  ant_t type;
public:
  Ant(Cell& init, ant_t type) : Critter(init, (type == QUEEN) ? 60 : 5), type {type} {}
  ~Ant() override = default;

  unsigned move() override;
  bool canMove(Cell& dest) override;
  unsigned breed() override { return 0; }
  string toString() override;

  // identifiers
  bool isAnt()     override { return true; }
  bool isQueen()   override { return type == QUEEN; }
  bool isWorker()  override { return type == WORKER; }
  bool isMating()  override { return type == MATING; }
};


#endif //PREDORPREY_ANT_H
