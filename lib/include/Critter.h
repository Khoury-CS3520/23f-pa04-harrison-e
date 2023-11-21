#ifndef PREDORPREY_CRITTER_H
#define PREDORPREY_CRITTER_H
#include <string>
#include <random>
#include <vector>
#include <memory>
#include "Coordinate.h"
using std::string, std::vector, std::shared_ptr;

// forward declarations
class Cell;
using coord_t = coordinate;
using velocity_t = coordinate;  // velocity is represented as 2d vector (math kind of vector)

// alias for clarity
using Time = unsigned;

class Critter {
protected:
  bool moved; // has this critter moved this turn?
  unsigned curHP;
  unsigned maxHP;
  Cell* home;

public:
  // functions
  Critter(Cell& spawn, unsigned health);
  virtual ~Critter() = default;

  virtual unsigned move();
  void changeHome(Cell* newHome);
  void toggleMoved() { moved = !moved; }
  bool hasMoved() const { return moved; }
  Cell& calcDest(Cell& src, velocity_t v);
  virtual bool canMove(Cell& dest) = 0; // can i move to dest?
  virtual unsigned breed()  = 0;
  virtual string toString() = 0;

  // identifiers, false by default
  virtual bool isDoodle()   { return false; }
  virtual bool isAnt()      { return false; }
  virtual bool isQueen()    { return false; }
  virtual bool isWorker()   { return false; }
  virtual bool isMating()   { return false; }
  virtual bool shouldDie()  { return curHP == 0; }
  virtual bool canBreed()   { return false; }
};

#endif //PREDORPREY_CRITTER_H
